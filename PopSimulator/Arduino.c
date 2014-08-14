#include "Arduino.h"

#include <cstdlib>

#include <GLFW/glfw3.h>

unsigned long millis() {
    double timeSeconds = glfwGetTime();
    return (unsigned long) (timeSeconds * 1000.0);
}

unsigned long micros() {
    double timeSeconds = glfwGetTime();
    return (unsigned long) (timeSeconds * 1000000.0);
}

int random(int max) {
    return rand() % max;
}
