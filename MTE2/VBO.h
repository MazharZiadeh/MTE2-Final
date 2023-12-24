// Ensure that the header file is included only once during compilation
#ifndef VBO_CLASS_H
#define VBO_CLASS_H

// Include the necessary OpenGL library header
#include <glad/glad.h>

// Class definition for Vertex Buffer Object (VBO)
class VBO
{
public:
    // ID of the VBO
    GLuint ID;

    // Constructor that takes an array of vertices and its size
    VBO(GLfloat* vertices, GLsizeiptr size);

    // Function to bind the VBO
    void Bind();

    // Function to unbind the VBO
    void Unbind();

    // Function to delete the VBO
    void Delete();
};

#endif
