#ifndef TASK2_H
#define TASK2_H
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
#include "dependeces/Common/objLoader.hpp"
#include "resource/Squere.h"
#include "src/Object.h"
#include "Task1.h"

class Task2
{
private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uv;
    GLuint Textur0;
    GLuint Textur1;

    void bindTexture(GLint out[2])
    {
        glUniform1i(Textur0, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, out[0]);
        glUniform1i(Textur1, 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, out[1]);
    }

    /* data */
public:
    void run()
    {
        GLFWwindow *window = initGLFW(1024, 768, "Teksturowanie", NULL, NULL);

        if (window)
            initGLEW();

        glfwSwapInterval(1);
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        std::vector<glm::vec3> vertices1;
        std::vector<glm::vec3> normals1;
        std::vector<glm::vec2> uv1;

        loadOBJ("../../resource/cube.obj", vertices, uv, normals);

        loadOBJ("../../resource/suzanne.obj", vertices1, uv1, normals1);
        //}

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        // wczytywanie shaderów{
        GLuint programid = LoadShaders("../../shaders/verShader.glsl", "../../shaders/fragShadersDouble.glsl");

        GLuint colorId = glGetUniformLocation(programid, "inputColor");

        GLuint mvpID = glGetUniformLocation(programid, "MVP");

        GLuint isTextured = glGetUniformLocation(programid, "isTextured");

        Textur0 = glGetUniformLocation(programid, "myTextureSampler0");
        Textur1 = glGetUniformLocation(programid, "myTextureSampler1");

        Object cube1(vertices1, uv1, normals1);

        cube1.translate(glm::vec3(0.0f, 0.0f, 0.0f));

        GLint out1[2];

        out1[0] = loadTexture("../../resource/uvmap.png", 1);
        out1[1] = loadTexture("../../resource/texture1.png", 1);

        // loadTexture(programid, "../../resource/uvmap.png", "myTextureSampler0", out2, 3);

        do
        {

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glUseProgram(programid);
            glUniform1i(isTextured, GL_TRUE);
            bindTexture(out1);
            cube1.drawObject(window, mvpID);
            glfwSwapBuffers(window);
            glfwPollEvents();

        } // Check if the ESC key was pressed or the window was closed
        while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
               glfwWindowShouldClose(window) == 0);

        glDeleteShader(programid);
        glfwTerminate();
    }
    Task2(/* args */);
    ~Task2();
};

Task2::Task2(/* args */)
{
}

Task2::~Task2()
{
}

#endif;