#ifndef OBJECT_H
#define OBJECT_H
#include "../dependeces/Common/Initialize.h"
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "../dependeces/Common/controls.hpp"
#include <glm/gtc/matrix_transform.hpp>
class Object
{
private:
    std::vector<glm::vec3> posytion;
    std::vector<glm::vec2> textCords;
    std::vector<glm::vec3> normals;
    glm::mat4 model, view, project, MVP;
    GLuint vertexbuffer;
    GLuint normalBuffer;
    GLuint uvBuffer;
    unsigned int vao;

    void upDateMatrix(GLFWwindow *window);

public:
    void drawObject(GLFWwindow *window, GLuint mvpID, GLuint modelMat);
    void drawObject(GLFWwindow *window, GLuint mvpID);
    Object(std::vector<glm::vec3> posytion,
           std::vector<glm::vec2> textCords,
           std::vector<glm::vec3> normals);
    ~Object();

    void translate(glm::vec3 vector);
    void scale(glm::vec3 vector);
    void rotate(glm::vec3 vector, float angle);
    void setModelMatrix(glm::mat4 model)
    {
        this->model = model;
    }
};
void activateTexture(GLint textureID, GLint texture, int number);
#endif;