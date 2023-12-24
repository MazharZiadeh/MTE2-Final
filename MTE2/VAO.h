// Include guards to prevent multiple inclusion of the header
#ifndef VAO_CLASS_H
#define VAO_CLASS_H

// Include necessary OpenGL and custom header files
#include <glad/glad.h>
#include "VBO.h"

// VAO (Vertex Array Object) class definition
class VAO
{
public:
    // GLuint to store the VAO ID
    GLuint ID;

    // Constructor to initialize the VAO
    VAO();

    // Function to link a VBO to a VAO attribute
    void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

    // Function to bind the VAO
    void Bind();

    // Function to unbind the VAO
    void Unbind();

    // Function to delete the VAO
    void Delete();
};

// End of include guard
#endif
