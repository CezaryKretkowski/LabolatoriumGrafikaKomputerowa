#include "Object.h"

Object::Object(std::vector<glm::vec3> posytion,
               std::vector<glm::vec2> textCords,
               std::vector<glm::vec3> normals)
{
    this->posytion = posytion;
    this->textCords = textCords;
    this->normals = normals;
    model = glm::mat4(1.0);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, posytion.size() * sizeof(glm::vec3), &posytion[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, textCords.size() * sizeof(glm::vec2), &textCords[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
}

Object::~Object()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &normalBuffer);
}
void Object::upDateMatrix(GLFWwindow *window)
{
    computeMatricesFromInputs(window);
    view = getViewMatrix();
    project = getProjectionMatrix();
}
void Object::drawObject(GLFWwindow *window, GLuint mvpID)
{
    upDateMatrix(window);
    glBindVertexArray(vao);
    glm::mat4 mvp = project * view * model;
    glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, posytion.size());
}
void Object::drawSkyBox(GLFWwindow *window, GLuint mvpID)
{
    upDateMatrix(window);

    glm::mat4 modelMat = glm::translate(glm::mat4(1), getPosition());
    modelMat = glm::scale(modelMat, glm::vec3(10, 10, 10));
    glBindVertexArray(vao);
    glm::mat4 mvp = project * view * modelMat;
    glDepthMask(GL_FALSE);
    glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, posytion.size());
    glDepthMask(GL_TRUE);
}
void Object::drawObject(GLFWwindow *window, GLuint M, GLuint V, GLuint P)
{
    upDateMatrix(window);
    glBindVertexArray(vao);
    glUniformMatrix4fv(M, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(V, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(P, 1, GL_FALSE, &project[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, posytion.size());
}
void Object::rotate(glm::vec3 vector, float angle)
{
    model = glm::rotate(model, glm::radians(angle), vector);
}
void Object::scale(glm::vec3 vector)
{
    model = glm::scale(model, vector);
}
void Object::translate(glm::vec3 vector)
{
    model = glm::translate(model, vector);
}
void activateTexture(GLint textureID, GLint texture, int number)
{
    glUniform1i(textureID, 0);
    if (number == 1)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
    else
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
}
