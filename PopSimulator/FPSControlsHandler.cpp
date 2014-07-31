/* 
 * File:   FPSControlsHandler.cpp
 * Author: antoine
 * 
 * Created on June 15, 2014, 9:30 PM
 */

#include "FPSControlsHandler.hpp"

#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

using namespace glm;

FPSControlsHandler::FPSControlsHandler() {
    projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    position = glm::vec3(0, 0, 20);
    direction = glm::vec3(0, 0, -1);
    right = glm::vec3(1, 0, 0);
    up = glm::vec3(0, 1, 0);

    horizontalAngle = 3.14159;
    verticalAngle = 0;
    fov = 45;

    view = glm::lookAt(position, direction, up);
    model = glm::mat4(1);

    speed = 5.f;
    mouseSpeed = .001f;
}

FPSControlsHandler::~FPSControlsHandler() {
}

glm::mat4 FPSControlsHandler::getModel() {
    return model;
}

glm::mat4 FPSControlsHandler::getView() {
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);
    lastTime = currentTime;

    for (std::list<int>::iterator it = keyPressedList.begin();
            it != keyPressedList.end(); it++) {
        int key = *it;
        switch (key) {
            case GLFW_KEY_UP:
            case GLFW_KEY_W:
                position += direction * deltaTime * speed;
                break;
            case GLFW_KEY_DOWN:
            case GLFW_KEY_S:
                position -= direction * deltaTime * speed;
                break;
            case GLFW_KEY_LEFT:
            case GLFW_KEY_A:
                position -= right * deltaTime * speed;
                break;
            case GLFW_KEY_RIGHT:
            case GLFW_KEY_D:
                position += right * deltaTime * speed;
                break;
        }
    }
    return glm::lookAt(position, position + direction, up);
}

glm::mat4 FPSControlsHandler::getProjection() {
    return projection;
}

void FPSControlsHandler::keyPressed(int key) {
    keyPressedList.push_front(key);
}

void FPSControlsHandler::keyReleased(int key) {
    keyPressedList.remove(key);
}

void FPSControlsHandler::mouseMoved(double x, double y) {

    horizontalAngle -= x * mouseSpeed;
    verticalAngle -= y * mouseSpeed;

    direction = glm::vec3(
            glm::cos(verticalAngle) * glm::sin(horizontalAngle),
            glm::sin(verticalAngle),
            glm::cos(verticalAngle) * glm::cos(horizontalAngle));

    right = glm::vec3(
            glm::sin(horizontalAngle - glm::pi<float>() / 2.f),
            0,
            glm::cos(horizontalAngle - glm::pi<float>() / 2.f));

    up = glm::cross(right, direction);
}
