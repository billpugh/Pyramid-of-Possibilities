/* 
 * File:   FPSControlsHandler.hpp
 * Author: antoine
 *
 * Created on June 15, 2014, 9:30 PM
 */

#ifndef FPSCONTROLSHANDLER_HPP
#define	FPSCONTROLSHANDLER_HPP

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <list>

class FPSControlsHandler {
public:
    FPSControlsHandler();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(double x, double y);
    
    glm::mat4 getModel();
    glm::mat4 getView();
    glm::mat4 getProjection();
    
    virtual ~FPSControlsHandler();
private:
    glm::mat4 projection;
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 right;
    glm::vec3 up;
    
    float horizontalAngle;
    float verticalAngle;
    float fov;
    
    glm::mat4 view;
    glm::mat4 model;
    
    float speed;
    float mouseSpeed;
    
    std::list<int> keyPressedList;
};

#endif	/* FPSCONTROLSHANDLER_HPP */

