#include "Arduino.h"

#include <cstdlib>

#include <GLFW/glfw3.h>

unsigned long millis() {
    double timeSeconds = glfwGetTime();
    return (long) (timeSeconds * 1000.0);
}

int random(int max) {
    return rand() % max;
}
