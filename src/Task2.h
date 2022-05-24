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
    unsigned int texture;
    bool initSkybox()
    {
        GLuint TexCubicID[] = {
            GL_TEXTURE_CUBE_MAP_POSITIVE_X, // Prawo
            GL_TEXTURE_CUBE_MAP_NEGATIVE_X, // Lewo
            GL_TEXTURE_CUBE_MAP_POSITIVE_Y, // Góra
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, // Dół
            GL_TEXTURE_CUBE_MAP_POSITIVE_Z, // Przód
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Z  // Tył
        };
        const char *TexFileNames[] = {
            // "../../resource/skyBoxTexture/stormydays_rt.png",
            // "../../resource/skyBoxTexture/stormydays_lf.png",
            // "../../resource/skyBoxTexture/stormydays_up.png",
            // "../../resource/skyBoxTexture/stormydays_dn.png",
            // "../../resource/skyBoxTexture/stormydays_bk.png",
            // "../../resource/skyBoxTexture/stormydays_ft.png",

            // "../../resource/clouds/2.bmp",
            // "../../resource/clouds/6.bmp",
            // "../../resource/clouds/5.bmp",
            // "../../resource/clouds/1.bmp",
            // "../../resource/clouds/3.bmp",
            // "../../resource/clouds/4.bmp",

            "../../resource/sandSkybox/5.jpg",
            "../../resource/sandSkybox/6.jpg",
            "../../resource/sandSkybox/1.jpg",
            "../../resource/sandSkybox/3.jpg",
            "../../resource/sandSkybox/4.jpg",
            "../../resource/sandSkybox/2.jpg",

        };

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

        for (int i = 0; i < 6; i++)
        {
            int width, height, nchan;
            unsigned char *dt = stbi_load(TexFileNames[i], &width, &height, &nchan, 0);
            if (!dt)
            {
                puts("error!!!");
                return false;
            }
            puts("Succes");
            glTexImage2D(TexCubicID[i], 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dt);
            stbi_image_free(dt);
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        return true;
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

        loadOBJ("../../resource/cube.obj", vertices, uv, normals);

        //}
        initSkybox();
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        // wczytywanie shaderów{
        GLuint programid = LoadShaders("../../shaders/skybox.glsl", "../../shaders/fragShaders.glsl");
        GLuint boxID = LoadShaders("../../shaders/boxReflectionVert.glsl", "../../shaders/boxReflectionFrag.glsl");

        GLuint colorId = glGetUniformLocation(programid, "inputColor");

        GLuint mvpID = glGetUniformLocation(programid, "MVP");
        GLuint M = glGetUniformLocation(boxID, "M");
        GLuint V = glGetUniformLocation(boxID, "V");
        GLuint P = glGetUniformLocation(boxID, "P");
        GLuint camerPos = glGetUniformLocation(boxID, "viewPos");

        GLuint isTextured = glGetUniformLocation(programid, "isTextured");

        Object cube1(vertices, uv, normals);
        vertices.clear();
        uv.clear();
        normals.clear();
        OBJLoad("../../resource/spit.obj", vertices, normals, uv);
        Object cube2(vertices, uv, normals);

        Textur0 = glGetUniformLocation(programid, "myTextureSampler");

        cube2.translate(glm::vec3(0.0f, 0.0f, 3.0f));

        GLint out1[2];

        loadTexture(programid, "../../resource/uvmap.png", "myTextureSampler", out1);

        do
        {
            glm::vec3 camera = getPosition();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glUseProgram(programid);
            glUniform1i(isTextured, GL_TRUE);
            glUniform1i(Textur0, 0);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

            cube1.drawSkyBox(window, mvpID);
            glUseProgram(boxID);
            glUniform3f(camerPos, camera[0], camera[1], camera[2]);
            cube2.drawObject(window, M, V, P);
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