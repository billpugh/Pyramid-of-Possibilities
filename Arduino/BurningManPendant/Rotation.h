/* Rotation */


float prevAngle;
float currentAngle;
float avgAngle;
float avgSpeed;
float avgSpeed2;
float avgActivity;
float longAvgActivity;
float veryLongAvgActivity;
float activity;
float prevX, prevY, prevZ;


unsigned long lastMillis;
const float fractionOld = 0.9;
const unsigned long updateInterval = 50;
const float twoPi = 6.2831853072;

const float pi = 3.1415926536;
const float halfPi = 1.5707963268;

void setupRotation() {
  lastMillis = millis();
  avgSpeed = 0.0;
  avgSpeed2 = 0.0;
  avgActivity = 0.0;
  longAvgActivity = 0.0;
  veryLongAvgActivity = 0.0;
  prevX = prevY = prevZ = 0.0;
}

float fractionalRotation(float a) {
  float b = a;
  while (a > pi)
    a -= twoPi;
  while (a < -pi)
    a += twoPi;
  return a;
}

void updateRotation() {

  float x = CircuitPlayground.motionX();
  float y = CircuitPlayground.motionY();
  float z = CircuitPlayground.motionZ();
  activity = (x - prevX) * (x - prevX)
             + (y - prevY) * (y - prevY)
             + (z - prevZ) * (z - prevZ);
  prevX = x;
  prevY = y;
  prevZ = z;

  float a = atan2(y, x);
  currentAngle = a;
  avgActivity = 0.95 * avgActivity + 0.05 * activity;
  longAvgActivity = 0.97 * longAvgActivity + 0.03 * avgActivity;
  veryLongAvgActivity = 0.999 * veryLongAvgActivity + 0.001*longAvgActivity;
  float diff = fractionalRotation(a - avgAngle);
  avgAngle = fractionalRotation(avgAngle + (1 - fractionOld) * diff);

  unsigned long now = millis();
  if (now > lastMillis) {
    float speed = fractionalRotation(avgAngle - prevAngle);
    speed = speed * 1000.0 / (now - lastMillis);
    avgSpeed = fractionOld * avgSpeed + (1 - fractionOld) * speed;
    avgSpeed2 = fractionOld * avgSpeed2 + (1 - fractionOld) * avgSpeed;

  }
  prevAngle = avgAngle;
  lastMillis = now;
}
