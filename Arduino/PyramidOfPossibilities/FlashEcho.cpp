//
//  FlashEcho.cpp
//
//  Created by Danny on 8/10/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "FlashEcho.h"
#include "Constants.h"

void FlashEcho::paint(RNLights & lights) {

    bool isTap = false;
	float activity = info.getLocalActivity();

	info.printf("Activity = %.3f. tapEligible = %s\n", activity, tapEligible ? "YES":"NO" );

	if ( tapEligible ) {
		if ( activity > parameters.maxActivityThreshold ) {
			isTap = true;
			tapEligible = false;
			lastTapTimestamp = info.getGlobalMillis();
		}
	} else {
		if ( activity < parameters.minActivityThreshold ) {
			tapEligible = true;
		}
	}

	fade();

	if ( replayMode ) {

		// REPLAY MODE

		if ( isTap ) {
			setIsReplaying(0);
		} else {
			playHistory();
		}

	} else {

		// USER IS TAPPING MODE

		if ( isTap ) {
			flash();
			recordFlash();
		}
		
		// info.getGlobalMillis() - lastTapTimestamp is time since last tap. We must use our own version based off lastTapTimestamp rather than info.lastTapTimestamp since we define taps differently.
		if ( info.getGlobalMillis() - lastTapTimestamp > parameters.lullDuration ) {
			setIsReplaying(1);
		}

	}

	// detect overflow (more taps than our buffer can hold) and make the lights blueish.
	bool overflow = (!replayMode && historyWriteHead >= historySize-1);

	// set lights!


	uint8_t r,g,b;

	if ( overflow ) {

		r = brightness;
		g = brightness;
		b = brightness;

	} else {

		RNGradient *gradientToUse = replayMode ? &(parameters.playbackGradient) : &(parameters.recordingGradient);

		gradientToUse->getColor(brightness, r, g, b);
		lights.setAllPixelColors(r,g,b);

	}
	lights.setAllPixelColors(r,g,b);
	lights.setBrightness(brightness);
}

void FlashEcho::playHistory() {

	int shouldFlash = 0;
	int newReadHead = historyReadHead;

	unsigned long timeSinceModeSwitch = info.getGlobalMillis() - lastModeSwitchTimestamp;
    // avoid divide by zero errors
    if (recordingDuration < 1)
        recordingDuration = 1;
	unsigned long offsetIntoPlayback = timeSinceModeSwitch % recordingDuration;

	unsigned long loopCountNow = timeSinceModeSwitch / recordingDuration;

	// detect when loopCount changes so we can reset historyReadHead
	if ( loopCountNow != loopCount ) {
		loopCount = loopCountNow;
		historyReadHead = 0;
		newReadHead = 0;
	}
	// info.printf("Loop = %lu.  offsetIntoPlayback = %lu.  Next: %d = %lu\n", loopCount, offsetIntoPlayback, historyReadHead, tapHistory[historyReadHead]);

	for ( int i = historyReadHead; i < historyWriteHead; i++ ) {

		unsigned long t = tapHistory[i];

		if ( offsetIntoPlayback > t ) {
			shouldFlash = 1;
			newReadHead = i + 1;
			// info.printf("Flashing due to index %d (value=%lu)\n", i, t);
		} else {
			break;
		}
	}


	if ( shouldFlash ) {
		// info.printf("Replaying a flash. timeSinceModeSwitch = %lu.  timeSinceModeSwitch = %lu\n", timeSinceModeSwitch, offsetIntoPlayback);
		flash();
	}
	historyReadHead = newReadHead;
}

void FlashEcho::recordFlash() {
	unsigned long timediff = info.getGlobalMillis() - lastModeSwitchTimestamp;
	tapHistory[historyWriteHead] = timediff;

    info.printf("Recording flash[%d] @ %lu.\n", historyWriteHead, timediff);

	historyWriteHead++;
	if ( historyWriteHead >= historySize ) {
		// overflow situation.	overwrite the last value.
		historyWriteHead = historySize - 1;	
	}	
}

void FlashEcho::setIsReplaying(bool replaying) {

	if ( replaying == replayMode ) {
		return;
	}

	unsigned long previousSwitchTimestamp = lastModeSwitchTimestamp;

	replayMode = replaying;
	lastModeSwitchTimestamp = info.getGlobalMillis();


	// info.printf("Switching modes%s\n", replayMode ? "Replay":"Record");

	if ( replaying ) {

		recordingDuration = lastModeSwitchTimestamp - previousSwitchTimestamp;

		// subtract off the kLullDuration so it loops cleanly. add a small (10 ms) padding so that the last tap will get correctly played back.
		if ( recordingDuration < parameters.lullDuration - 10 ) {
			recordingDuration = 0;
		} else {
			recordingDuration = recordingDuration - parameters.lullDuration + 10;
		}

		historyReadHead = 0;

		// info.printf("Replay History has %d items. Recording duration = %lu ms.\n", historyWriteHead - 1, recordingDuration);

	} else {

		clearHistory();
	}
}


void FlashEcho::clearHistory() {
	memset(&tapHistory, sizeof(unsigned long) * historySize, 0x00);
	historyWriteHead = 0;
	recordingDuration = 0;
	loopCount = 0;
}

void FlashEcho::flash() {
	brightness = parameters.maxBrightness;	
}

void FlashEcho::fade() {
	brightness-=parameters.fadeFactor;
	if ( brightness < parameters.minBrightness ) {
		brightness = parameters.minBrightness;
	}
}

const char * FlashEcho:: name() {
    return "FlashEcho";
}

