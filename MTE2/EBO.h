// Ensure that the header file is included only once to prevent multiple definitions
#ifndef EBO_CLASS_H
#define EBO_CLASS_H

// Include the necessary OpenGL header
#include <glad/glad.h>

// Class definition for Element Buffer Object (EBO)
class EBO
{
public:
    // ID representing the EBO in OpenGL
    GLuint ID;

    // Constructor for EBO, takes an array of indices and the size of the array
    EBO(GLuint* indices, GLsizeiptr size);

    // Bind the EBO to the OpenGL context
    void Bind();

    // Unbind the EBO from the OpenGL context
    void Unbind();

    // Delete the EBO, freeing up resources in OpenGL
    void Delete();
};

#endif
