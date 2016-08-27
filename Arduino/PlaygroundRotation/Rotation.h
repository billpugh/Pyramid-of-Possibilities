/* Rotation */


float prevAngle;
float avgAngle;
float avgSpeed;
float avgSpeed2;


unsigned long lastMillis;
const float fractionOld = 0.9;
const unsigned long updateInterval = 50;
const float pi = 3.1415926536;
const float halfPi = 1.5707963268;

void setupRotation() {
  lastMillis = millis();
  avgSpeed = 0.0;
  avgSpeed2 = 0.0;
}

float getAngle() {
 float x = CircuitPlayground.motionX();
 float y = CircuitPlayground.motionY();
 float z = CircuitPlayground.motionZ();

 float a = atan2(y, x);
 return a;
}

float fractionalRotation(float a) {
  float b = a;
  while (a > halfPi)
   a -= pi;
  while (a < -halfPi)
   a += pi;
   if (a > halfPi || a < -halfPi) {
    Serial.print(b);
    Serial.print("  ");
    Serial.println(a);
   }
  return a;
}

void updateRotation() {
  float a = getAngle();
  float diff = fractionalRotation(a - avgAngle);
  avgAngle = fractionalRotation(avgAngle + (1-fractionOld) * diff);

  unsigned long now = millis();
  if (now > lastMillis) {
    float speed = fractionalRotation(avgAngle - prevAngle);
  speed = speed * 1000.0 / (now - lastMillis);
  avgSpeed = fractionOld * avgSpeed + (1-fractionOld) * speed;
   avgSpeed2 = fractionOld * avgSpeed2 + (1-fractionOld) * avgSpeed;
 
  }
  prevAngle = avgAngle;
  lastMillis = now;
}
