#ifndef TASK1_H
#define TASK1_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "dependeces/Common/Initialize.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
#include "dependeces/Common/shader.hpp"
#include "dependeces/Common/controls.hpp"
#include "dependeces/Common/objloader.hpp"
#include "src/objLoader.h"
#include "src/Object.h"

class Task1
{
private:
    /* data */
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uv;

public:
    Task1(/* args */);
    ~Task1();
    void run()
    {
        GLFWwindow *window = initGLFW(1024, 768, "Teksturowanie", NULL, NULL);

        if (window)
            initGLEW();

        glfwSwapInterval(1);
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        OBJLoad("../../resource/spit.obj", vertices, normals, uv);
        //}

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // wczytywanie shaderów{
        GLuint programid = LoadShaders("../../shaders/lightningVertShader.glsl", "../../shaders/lightningFragShader.glsl");

        GLuint mvpID = glGetUniformLocation(programid, "MVP");
        GLuint colorID = glGetUniformLocation(programid, "inputColor");
        GLuint isTextured = glGetUniformLocation(programid, "isTextured");
        // GLuint blackWhiteFlag = glGetUniformLocation(programid, "whiteblack");
        // GLuint cell_Shading = glGetUniformLocation(programid, "cel_Shading");

        Object cube0(vertices, uv, normals);
        vertices.clear();
        uv.clear();
        normals.clear();
        loadOBJ("../../resource/floor.obj", vertices, uv, normals);
        Object floor(vertices, uv, normals);

        floor.translate(glm::vec3(0.0f, -1.0f, 0.0f));
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        GLint out[2];
        GLint out1[2];

        loadTexture(programid, "../../resource/uvmap.png", "myTextureSampler", out);
        loadTexture(programid, "../../resource/floorWood.png", "myTextureSampler", out1);

        do
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glUseProgram(programid);
            glUniform1i(out[0], 0);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, out[1]);

            glUniform1i(isTextured, GL_TRUE);

            cube0.drawObject(window, mvpID);

            glUniform1i(out1[0], 0);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, out1[1]);
            floor.drawSkyBox(window, mvpID);

            glFinish();
            glfwSwapBuffers(window);
            glfwPollEvents();

        } // Check if the ESC key was pressed or the window was closed
        while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
               glfwWindowShouldClose(window) == 0);

        glDeleteShader(programid);
        glfwTerminate();
    }
};

Task1::Task1(/* args */)
{
}

Task1::~Task1()
{
}

#endif;