#ifndef OBJLOADER_H
#define OBJLOADER_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "dependeces/Common/OBJ_Loader.h"
#include "../dependeces/Common/stb_image.h"
bool OBJLoad(std::string path, std::vector<glm::vec3> &vert, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &uv)
{
    objl::Loader loader;

    if (!loader.LoadFile(path))
        return false;

    for (int i = 0; i < loader.LoadedMeshes.size(); i++)
    {
        objl::Mesh curMesh = loader.LoadedMeshes[i];
        for (int j = 0; j < curMesh.Vertices.size(); j++)
        {
            vert.push_back(glm::vec3(curMesh.Vertices[j].Position.X, curMesh.Vertices[j].Position.Y, curMesh.Vertices[j].Position.Z));
            normals.push_back(glm::vec3(curMesh.Vertices[j].Normal.X, curMesh.Vertices[j].Normal.Y, curMesh.Vertices[j].Normal.Z));
            uv.push_back(glm::vec2(curMesh.Vertices[j].TextureCoordinate.X, curMesh.Vertices[j].TextureCoordinate.Y));
        }
    }

    return true;
}
void repetLineryMode()
{

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
void repetMirrorLineryMode()
{

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
}
void toBorderLineryMode()
{
    // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    float color[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
}
void toEdgeLineryMode()
{

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
bool loadTexture(GLuint shederID, std::string texturePath, GLchar *name, GLint out[2])
{
    GLuint textureId, texture;
    textureId = glGetUniformLocation(shederID, name);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int width, height, nchan;
    unsigned char *dt = stbi_load(texturePath.c_str(), &width, &height, &nchan, 0);
    if (!dt)
    {
        puts("Cannot load Texture");
        return false;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dt);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(dt);
    out[0] = textureId;
    out[1] = texture;
    return true;
}
GLint loadTexture(std::string texturePath, int mode)
{
    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int width, height, nchan;
    unsigned char *dt = stbi_load(texturePath.c_str(), &width, &height, &nchan, 0);
    if (!dt)
    {
        puts("Cannot load Texture");
        return 0;
    }
    switch (mode)
    {
    case 1:
        repetMirrorLineryMode();
        break;
    case 2:
        toBorderLineryMode();
        break;
    case 3:
        toEdgeLineryMode();
        break;

    default:
        repetLineryMode();
        break;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dt);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(dt);

    return texture;
}
bool loadTexture(GLuint shederID, std::string texturePath, GLchar *name, GLint out[2], int mode)
{
    GLuint textureId, texture;
    textureId = glGetUniformLocation(shederID, name);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int width, height, nchan;
    float color[] = {1.0f, 0.0f, 0.0f, 1.0f};
    unsigned char *dt = stbi_load(texturePath.c_str(), &width, &height, &nchan, 0);
    if (!dt)
    {
        puts("Cannot load Texture");
        return false;
    }
    switch (mode)
    {
    case 1:
        repetMirrorLineryMode();
        break;
    case 2:

        toBorderLineryMode();
        puts("2");
        break;
    case 3:
        // puts("3");
        toEdgeLineryMode();
        break;

    default:
        // puts("0");
        repetLineryMode();
        break;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dt);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(dt);
    out[0] = textureId;
    out[1] = texture;
    return true;
}

#endif