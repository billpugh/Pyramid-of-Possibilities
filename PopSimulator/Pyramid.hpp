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

    void render(glm::mat4 MVP);

    void setLedColor(int platform, int led, float r, float g, float b);

private:
    GLuint programId;
    GLuint matrixId;
    GLuint vertexPosition_modelspaceID;
    GLuint vertexColorID;

    int g_vertex_buffer_data_length;
    GLfloat* g_vertex_buffer_data;
    GLuint vertexbuffer;

    GLfloat* g_color_buffer_data;
    GLuint colorbuffer;

    int g_leds_buffer_data_length;
    GLfloat* g_leds_buffer_data;
    GLuint ledsbuffer;

    GLfloat* g_leds_color_buffer_data;
    GLuint ledscolorbuffer;

    void loadBuffers();
};

#endif	/* PYRAMID_HPP */

