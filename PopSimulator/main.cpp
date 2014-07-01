/* 
 * File:   main.cpp
 * Author: antoine
 *
 * Created on June 14, 2014, 8:36 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "Pyramid.hpp"
#include "FPSControlsHandler.hpp"
#include "PyramidArchitecture.hpp"

Pyramid* pyramid = NULL;
FPSControlsHandler* controlsHandler = NULL;

static void key_callback(GLFWwindow* window, int key, int scancode, int action,
        int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }
    if (controlsHandler != NULL) {
        if (action == GLFW_PRESS) {
            controlsHandler->keyPressed(key);

            if (key == GLFW_KEY_0) {
                for (int i = 0; i < 84; i++) {
                    for (int j = 0; j < 219; j++) {
                        pyramid->setLedColor(i, j, 0, 0, 0);
                    }
                }
            }

        } else if (action == GLFW_RELEASE) {
            controlsHandler->keyReleased(key);
        }
    }
}

static void cursorPos_callback(GLFWwindow* window, double xpos, double ypos) {
    static int width = 0;
    static int height = 0;
    if (width == 0 || height == 0) {
        glfwGetWindowSize(window, &width, &height);
        glfwSetCursorPos(window, width / 2., height / 2.);
        return;
    }

    if (controlsHandler != NULL) {
        controlsHandler->mouseMoved(xpos - width / 2., ypos - height / 2.);
        glfwSetCursorPos(window, width / 2., height / 2.);
    }
}

static void animate() {
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);
    if (deltaTime < 0.1) {
        return;
    }
    lastTime = currentTime;

    static float direction = -0.1f;
    static float factor = 1.0f;

    factor += direction;
    if (factor < 0) {
        direction = -direction;
        factor = direction;
    } else if (factor > 1) {
        direction = -direction;
        factor = 1 + direction;
    }

    for (int i = 0; i < 84; i++) {
        short t = PyramidArchitecture::getTierOfPlatform(i);
        short r = (short) (t & 1);
        short g = (short) ((t & 2) >> 1);
        short b = (short) ((t & 4) >> 2);
        for (int j = 0; j < 219; j++) {
            pyramid->setLedColor(i, j, r * factor, g * factor, b * factor);
        }
    }
}

int main(void) {
    // Initialise GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    //    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(800, 600,
            "Pyramid of Possibilities Simulator", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursorPos_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    pyramid = new Pyramid();
    controlsHandler = new FPSControlsHandler();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        pyramid->render(controlsHandler->getMVP());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        animate();
    }

    delete pyramid;
    delete controlsHandler;

    glfwTerminate();
    return 0;
}
