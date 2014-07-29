/* 
 * File:   Pyramid.cpp
 * Author: antoine
 * 
 * Created on June 14, 2014, 10:07 AM
 */

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "ShaderLoader.hpp"
#include "PyramidArchitecture.hpp"
#include "Pyramid.hpp"

Pyramid::Pyramid() {
    // Set constants
    lightPos = glm::vec3(0, 15, 0);
    lightColor = glm::vec3(1, 1, 1);
    lightPower = 100.0f;
    ambientColor = glm::vec3(0.5, 0.5, 0.5);
    specularColor = glm::vec3(0.3, 0.3, 0.3);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glPointSize(2);

    programId = LoadShaders("TransformVertexShader.shader",
            "ColorFragmentShader.shader");
    matrixId = glGetUniformLocation(programId, "MVP");
    viewMatrixId = glGetUniformLocation(programId, "V");
    modelMatrixId = glGetUniformLocation(programId, "M");
    LightID = glGetUniformLocation(programId, "LightPosition_worldspace");
    LightColorID = glGetUniformLocation(programId, "LightColor");
    LightPowerID = glGetUniformLocation(programId, "LightPower");
    AmbientColorID = glGetUniformLocation(programId, "AmbientColor");
    SpecularColorID = glGetUniformLocation(programId, "SpecularColor");

    vertexPosition_modelspaceID = glGetAttribLocation(
            programId, "vertexPosition_modelspace");
    vertexColorID = glGetAttribLocation(programId, "vertexColor");
    vertexNormal_modelspaceID = glGetAttribLocation(
            programId, "vertexNormal_modelspace");

    this->loadBuffers();

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof (GL_FLOAT) * g_vertex_buffer_data_length,
            g_vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof (GL_FLOAT) * g_vertex_buffer_data_length,
            g_color_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof (GL_FLOAT) * g_vertex_buffer_data_length,
            g_normal_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &ledsbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, ledsbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof (GL_FLOAT) * g_leds_buffer_data_length,
            g_leds_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &ledscolorbuffer);
}

void Pyramid::loadBuffers() {
    g_vertex_buffer_data_length = PyramidArchitecture::getNumVertices() * 3;
    g_vertex_buffer_data = new GLfloat[g_vertex_buffer_data_length];
    float factor = 0.001f;
    float * popVerts;
    PyramidArchitecture::getVertices(popVerts);
    for (int i = 0; i < g_vertex_buffer_data_length; i += 3) {
        float x = ((popVerts[i] - 8970) / 1.0775f + 20) * factor;
        float y = (popVerts[i + 1] / 1.0775f + 89.5f - 5000) * factor;
        float z = ((-9502 - popVerts[i + 2]) / 1.0775f - 40) * factor;
        g_vertex_buffer_data[i] = x;
        g_vertex_buffer_data[i + 1] = y;
        g_vertex_buffer_data[i + 2] = z;
    }

    g_color_buffer_data = new GLfloat[g_vertex_buffer_data_length];
    for (int i = 0; i < g_vertex_buffer_data_length; i += 3) {
        g_color_buffer_data[i] = 0.5f;
        g_color_buffer_data[i + 1] = 0.2f;
        g_color_buffer_data[i + 2] = 0.1f;
    }

    g_normal_buffer_data = new GLfloat[g_vertex_buffer_data_length];
    float * popNormals;
    PyramidArchitecture::getVertices(popNormals);
    for (int i = 0; i < g_vertex_buffer_data_length; i += 3) {
        g_normal_buffer_data[i] = popNormals[i];
        g_normal_buffer_data[i + 1] = popNormals[i + 1];
        g_normal_buffer_data[i + 2] = popNormals[i + 2];
    }

    int nbPlatforms = PyramidArchitecture::nbPlatforms;
    int nbLedsPerPlatform = PyramidArchitecture::nbLedsPerPlatform;
    int ledsBufferSize = nbPlatforms * nbLedsPerPlatform * 3;
    g_leds_buffer_data_length = ledsBufferSize;
    g_leds_buffer_data = new GLfloat[ledsBufferSize];
    g_leds_color_buffer_data = new GLfloat[ledsBufferSize];
    int k = 0;
    for (int i = 0; i < nbPlatforms; i++) {
        short* platformPosition;
        PyramidArchitecture::getLocationOfPlatform(i, platformPosition);
        short x = platformPosition[0];
        short y = platformPosition[1];
        short z = (short) (platformPosition[2] + 50);
        short t = PyramidArchitecture::getTierOfPlatform(i);
        short r = (short) (t & 1);
        short g = (short) ((t & 2) >> 1);
        short b = (short) ((t & 4) >> 2);
        for (int j = 0; j < nbLedsPerPlatform; j++) {
            short* ledPosition;
            PyramidArchitecture::getLedPosition(j, ledPosition);
            g_leds_buffer_data[k] = (x + 1.05f * ledPosition[1]) * factor;
            g_leds_buffer_data[k + 1] = (z - 5000) * factor;
            g_leds_buffer_data[k + 2] = (y + 1.05f * ledPosition[0]) * factor;
            g_leds_color_buffer_data[k] = r;
            g_leds_color_buffer_data[k + 1] = g;
            g_leds_color_buffer_data[k + 2] = b;
            k += 3;
        }
    }
}

void Pyramid::render(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
    glm::mat4 MVP = projection * view * model;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(programId);

    glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(viewMatrixId, 1, GL_FALSE, &view[0][0]);

    glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(LightColorID, lightColor.x, lightColor.y, lightColor.z);
    glUniform1f(LightPowerID, lightPower);
    glUniform3f(AmbientColorID, ambientColor.x, ambientColor.y, ambientColor.z);
    glUniform3f(SpecularColorID, specularColor.x, specularColor.y, specularColor.z);

    // Draw platforms
    glEnableVertexAttribArray(vertexPosition_modelspaceID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(vertexPosition_modelspaceID, 3, GL_FLOAT, GL_FALSE, 0,
            (void*) 0);

    glEnableVertexAttribArray(vertexColorID);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(vertexColorID, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glEnableVertexAttribArray(vertexNormal_modelspaceID);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glVertexAttribPointer(
            vertexNormal_modelspaceID, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glDrawArrays(GL_TRIANGLES, 0, g_vertex_buffer_data_length);
    glDisableVertexAttribArray(vertexNormal_modelspaceID);

    // Draw leds
    glBindBuffer(GL_ARRAY_BUFFER, ledsbuffer);
    glVertexAttribPointer(vertexPosition_modelspaceID, 3, GL_FLOAT, GL_FALSE,
            0, (void*) 0);

    glBindBuffer(GL_ARRAY_BUFFER, ledscolorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof (GL_FLOAT) * g_leds_buffer_data_length,
            g_leds_color_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexColorID, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glDrawArrays(GL_POINTS, 0, g_leds_buffer_data_length);

    glDisableVertexAttribArray(vertexPosition_modelspaceID);
    glDisableVertexAttribArray(vertexColorID);
}

void Pyramid::setLedColor(int platform, int led, float r, float g, float b) {
    int nbLedsPerPlatform = PyramidArchitecture::nbLedsPerPlatform;
    int ledsBufferSize = PyramidArchitecture::nbPlatforms * nbLedsPerPlatform * 3;

    int index = (platform * nbLedsPerPlatform + led) * 3;
    if (index >= ledsBufferSize) {
        return;
    }
    g_leds_color_buffer_data[index] = r;
    g_leds_color_buffer_data[index + 1] = g;
    g_leds_color_buffer_data[index + 2] = b;
}

Pyramid::~Pyramid() {
    delete g_vertex_buffer_data;
    delete g_color_buffer_data;
    delete g_normal_buffer_data;
    delete g_leds_buffer_data;
    delete g_leds_color_buffer_data;
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &colorbuffer);
    glDeleteBuffers(1, &normalbuffer);
    glDeleteBuffers(1, &ledsbuffer);
    glDeleteBuffers(1, &ledscolorbuffer);
    glDeleteProgram(programId);
}

