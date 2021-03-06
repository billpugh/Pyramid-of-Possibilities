// This is the example sketch that gets loaded on every BlinkyTape during production!
#include <EEPROM.h>
#include <FastLED.h>

#include "BlinkyTape.h"
#include "ColorLoop.h"
#include "ColorWheel.h"
#include "SerialLoop.h"
#include "Shimmer.h"
#include "Scanner.h"
#include "Flashlight.h"

struct CRGB leds[LED_COUNT];

#define BRIGHT_STEP_COUNT 8
#define STARTING_BRIGHTNESS 4
volatile uint8_t brightnesSteps[BRIGHT_STEP_COUNT] = {5,15,40,70,93, 70, 40, 15};

uint8_t brightness = STARTING_BRIGHTNESS;
uint8_t lastBrightness = STARTING_BRIGHTNESS;


// For fading in a new sketch
long lastTime;

float fadeIndex;
#define FADE_STEPS 50

// Button interrupt variables and Interrupt Service Routine
uint8_t buttonState = 0;
bool buttonDebounced;
long buttonDownTime = 0;
long buttonPressTime = 0;

unsigned long nextAutoAdvance;
const unsigned long autoAdvanceDelay = 300000L; /// 5 minutes


#define BUTTON_BRIGHTNESS_SWITCH_TIME  1     // Time to hold the button down to switch brightness
#define BUTTON_PATTERN_SWITCH_TIME    1000   // Time to hold the button down to switch patterns


#define EEPROM_START_ADDRESS  0
#define EEPROM_MAGIG_BYTE_0   0x12
#define EEPROM_MAGIC_BYTE_1   0x34
#define PATTERN_EEPROM_ADDRESS EEPROM_START_ADDRESS + 2

uint8_t currentPattern = 0;
uint8_t patternCount = 0;
#define MAX_PATTERNS 10
Pattern* patterns[MAX_PATTERNS];


// Register a pattern
void registerPattern(Pattern* newPattern) {
  // If there is space for this pattern
  if(MAX_PATTERNS <= patternCount) {
    return;
  }
  
  patterns[patternCount] = newPattern;
  patternCount++;
}

// Change the current pattern
void initializePattern(uint8_t newPattern) {
  // Check if this is a valid pattern
  if(newPattern >= MAX_PATTERNS) {
    return;
  }
  
  EEPROM.write(PATTERN_EEPROM_ADDRESS, newPattern);
  
  currentPattern = newPattern;
  patterns[currentPattern]->reset();
  
  lastTime = millis();
  fadeIndex = 0;
}

void advancePattern() {
    initializePattern((currentPattern+1)%patternCount);
}

// Run one step of the current pattern
void runPattern() {
  patterns[currentPattern]->draw(leds);
}


// Called when the button is both pressed and released.
ISR(PCINT0_vect){
  buttonState = !(PINB & (1 << PINB6)); // Reading state of the PB6 (remember that HIGH == released)
  
  if(buttonState) {
    // On button down, record the time so we can convert this into a gesture later
    buttonDownTime = millis();
    buttonDebounced = false;
    
    // And configure and start timer4 interrupt.
    TCCR4B = 0x0F; // Slowest prescaler
    TCCR4D = _BV(WGM41) | _BV(WGM40);  // Fast PWM mode
    OCR4C = 0x10;        // some random percentage of the clock
    TCNT4 = 0;  // Reset the counter
    TIMSK4 = _BV(TOV4);  // turn on the interrupt
    
  }
  else {
    TIMSK4 = 0;  // turn off the interrupt
  }
}

// This is called every xx ms while the button is being held down; it counts down then displays a
// visual cue and changes the pattern.
ISR(TIMER4_OVF_vect) {
  // If the user is still holding down the button after the first cycle, they were serious about it.
  if(buttonDebounced == false) {
    buttonDebounced = true;
    lastBrightness = brightness;
    brightness = (brightness + 1) % BRIGHT_STEP_COUNT;
    LEDS.setBrightness(brightnesSteps[brightness]);
  }
  
  // If we've waited long enough, switch the pattern
  // TODO: visual indicator
  buttonPressTime = millis() - buttonDownTime;
  if(buttonPressTime > BUTTON_PATTERN_SWITCH_TIME) {
    // first unroll the brightness!
    brightness = lastBrightness;
    LEDS.setBrightness(brightnesSteps[brightness]);
    
    advancePattern();
    
    nextAutoAdvance = 0xffffffff;
    
    // Finally, reset the button down time, so we don't advance again too quickly
    buttonDownTime = millis();
  }
}

ColorLoop originalRainbow(1,1,1);
ColorLoop blueRainbow(.2,1,1);
Shimmer shimmer0(0);
Shimmer shimmer2(2);
ColorWheel cwheel(0);

void setup()
{  
  nextAutoAdvance = millis() + autoAdvanceDelay;
 
  Serial.begin(57600);
  LEDS.addLeds<WS2811, LED_OUT, RGB>(leds, LED_COUNT);
  brightness = STARTING_BRIGHTNESS;
  LEDS.setBrightness(brightnesSteps[brightness]);
  LEDS.show();
  

  pinMode(BUTTON_IN, INPUT_PULLUP);
  pinMode(ANALOG_INPUT, INPUT_PULLUP);
  pinMode(EXTRA_PIN_A, INPUT_PULLUP);
  pinMode(EXTRA_PIN_B, INPUT_PULLUP);
  
  // Interrupt set-up; see Atmega32u4 datasheet section 11
  PCIFR  |= (1 << PCIF0);  // Just in case, clear interrupt flag
  PCMSK0 |= (1 << PCINT6); // Set interrupt mask to the button pin (PCINT6)
  PCICR  |= (1 << PCIE0);  // Enable interrupt
  
  registerPattern(&originalRainbow);
  registerPattern(&shimmer0);
  registerPattern(&blueRainbow);
  registerPattern(&shimmer2);
  registerPattern(&cwheel);
  

  // Attempt to read in the last used pattern; if it's an invalid
  // number, initialize it to 0 instead.
  int m0 = EEPROM.read(EEPROM_START_ADDRESS);
  int m1 = EEPROM.read(EEPROM_START_ADDRESS+1);
  if(m0 == EEPROM_MAGIG_BYTE_0
     && m1 == EEPROM_MAGIC_BYTE_1 && false) {
    currentPattern = EEPROM.read(PATTERN_EEPROM_ADDRESS);
    if(currentPattern >= patternCount) {
      currentPattern = 0;
    }
  }
  else {
    EEPROM.write(EEPROM_START_ADDRESS, EEPROM_MAGIG_BYTE_0);
    EEPROM.write(EEPROM_START_ADDRESS+1, EEPROM_MAGIC_BYTE_1);
    currentPattern = 0;
  }
     
  
  initializePattern(currentPattern);
}

void loop()
{
  // If'n we get some data, switch to passthrough mode
  if(Serial.available() > 0) {
    serialLoop(leds);
  }

  if (millis() > nextAutoAdvance) {
    advancePattern();
    nextAutoAdvance = millis() + autoAdvanceDelay;
  }

  // Draw the current pattern
  runPattern();

  if((millis() - lastTime > 15) && fadeIndex < FADE_STEPS) {
    lastTime = millis();
    fadeIndex++;
    
    LEDS.setBrightness(brightnesSteps[brightness]*(fadeIndex/FADE_STEPS));
  }
    

  LEDS.show();
}

