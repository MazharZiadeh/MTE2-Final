#include "EBO.h"

// Constructor for the EBO class
EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	// Generate a buffer object and store its ID in the 'ID' member variable
	glGenBuffers(1, &ID);

	// Bind the buffer object to the GL_ELEMENT_ARRAY_BUFFER target
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

	// Fill the buffer with data, specifying GL_STATIC_DRAW as usage hint
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

// Bind method to bind the EBO to the GL_ELEMENT_ARRAY_BUFFER target
void EBO::Bind()
{
	// Bind the buffer with the stored ID to the GL_ELEMENT_ARRAY_BUFFER target
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbind method to unbind the current GL_ELEMENT_ARRAY_BUFFER target
void EBO::Unbind()
{
	// Bind the GL_ELEMENT_ARRAY_BUFFER target to 0, unbinding the buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Delete method to delete the EBO and free up resources
void EBO::Delete()
{
	// Delete the buffer object with the stored ID
	glDeleteBuffers(1, &ID);
}
