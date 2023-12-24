#include "VBO.h"

// Constructor for the VBO class
VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
    // Generate a single buffer and store its ID in the variable 'ID'
    glGenBuffers(1, &ID);

    // Bind the buffer with the specified ID as an array buffer
    glBindBuffer(GL_ARRAY_BUFFER, ID);

    // Allocate memory for the buffer and copy vertex data to the GPU
    // GL_STATIC_DRAW indicates that the data will not change frequently
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// Function to bind the VBO for use
void VBO::Bind()
{
    // Bind the buffer with the specified ID as an array buffer
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Function to unbind the VBO
void VBO::Unbind()
{
    // Unbind the currently bound array buffer by binding buffer ID 0
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Function to delete the VBO and release associated resources
void VBO::Delete()
{
    // Delete the buffer with the specified ID
    glDeleteBuffers(1, &ID);
}
