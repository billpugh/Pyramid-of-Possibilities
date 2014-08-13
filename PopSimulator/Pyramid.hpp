/* 
 * File:   Pyramid.hpp
 * Author: antoine
 *
 * Created on June 14, 2014, 10:07 AM
 */

#ifndef PYRAMID_HPP
#define	PYRAMID_HPP

#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class Pyramid {
public:
    Pyramid();
    virtual ~Pyramid();

    void render(glm::mat4 model, glm::mat4 view, glm::mat4 projection);

    void setLedColor(int platform, int led, float r, float g, float b);

private:
    glm::vec3 lightPos;
    glm::vec3 lightColor;
    GLfloat lightPower;
    glm::vec3 ambientColor;
    glm::vec3 specularColor;

    GLuint programId;
    GLuint matrixId;
    GLuint modelMatrixId;
    GLuint viewMatrixId;
    GLuint vertexPosition_modelspaceID;
    GLuint vertexColorID;
    GLuint LightID;
    GLuint LightColorID;
    GLuint LightPowerID;
    GLuint AmbientColorID;
    GLuint SpecularColorID;
    GLuint vertexNormal_modelspaceID;
    
    GLuint ledsProgramId;
    GLuint ledsMatrixId;
    GLuint ledsVertexPosition_modelspaceID;
    GLuint ledsVertexColorID;

    int g_vertex_buffer_data_length;
    GLfloat* g_vertex_buffer_data;
    GLuint vertexbuffer;

    GLfloat* g_color_buffer_data;
    GLuint colorbuffer;

    GLfloat* g_normal_buffer_data;
    GLuint normalbuffer;

    int g_leds_buffer_data_length;
    GLfloat* g_leds_buffer_data;
    GLuint ledsbuffer;

    GLfloat* g_leds_color_buffer_data;
    GLuint ledscolorbuffer;

    void loadBuffers();
};

#endif	/* PYRAMID_HPP */

