// Include guards to prevent multiple inclusion of the header file
#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

// OpenGL and image loading library includes
#include <glad/glad.h>
#include <stb/stb_image.h>

// Include the custom shader class header file
#include "MyShader.h"

// Texture class declaration
class Texture
{
public:
    // Texture properties
    GLuint ID;        // Texture ID in OpenGL
    GLenum type;      // Type of texture (e.g., GL_TEXTURE_2D)

    // Constructor that takes parameters for texture initialization
    Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

    // Method to bind the texture to a specific texture unit in a shader
    void texUnit(Shader& shader, const char* uniform, GLuint unit);

    // Method to bind the texture
    void Bind();

    // Method to unbind the texture
    void Unbind();

    // Method to delete the texture
    void Delete();
};

// End of include guard
#endif
