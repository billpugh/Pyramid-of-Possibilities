#include "Arduino.h"

#include <GLFW/glfw3.h>

unsigned long millis() {
    double timeSeconds = glfwGetTime();
    return (long) (timeSeconds * 1000.0);
}
