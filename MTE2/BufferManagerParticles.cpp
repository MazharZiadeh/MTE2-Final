// BufferManagerParticles.cpp

// Include the header file for this module
#include "BufferManagerParticles.h"

// Define the namespace for this module
namespace BufferManagerParticles {

	// Constructor for ParticlesEBO class
	ParticlesEBO::ParticlesEBO(GLuint* indicesParticles, GLsizeiptr size) {
		// Generate a buffer object
		glGenBuffers(1, &ID);

		// Bind the buffer to the GL_ELEMENT_ARRAY_BUFFER target
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

		// Allocate storage and fill it with data
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indicesParticles, GL_STATIC_DRAW);
	}

	// Bind the Element Buffer Object (EBO)
	void ParticlesEBO::ParticlesBind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	// Unbind the Element Buffer Object (EBO)
	void ParticlesEBO::ParticlesUnbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	// Delete the Element Buffer Object (EBO)
	void ParticlesEBO::ParticlesDelete() {
		glDeleteBuffers(1, &ID);
	}

	// Constructor for ParticlesVAO class
	ParticlesVAO::ParticlesVAO() {
		// Generate a vertex array object
		glGenVertexArrays(1, &ID);
	}

	// Link attribute pointers for a VBO to the VAO
	void ParticlesVAO::LinkAttrib(ParticlesVBO& ParticlesVBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
		// Bind the VBO
		ParticlesVBO.ParticlesBind();

		// Define an attribute pointer
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);

		// Enable the attribute
		glEnableVertexAttribArray(layout);

		// Unbind the VBO
		ParticlesVBO.ParticlesUnbind();
	}

	// Bind the Vertex Array Object (VAO)
	void ParticlesVAO::ParticlesBind() {
		glBindVertexArray(ID);
	}

	// Unbind the Vertex Array Object (VAO)
	void ParticlesVAO::ParticlesUnbind() {
		glBindVertexArray(0);
	}

	// Delete the Vertex Array Object (VAO)
	void ParticlesVAO::ParticlesDelete() {
		glDeleteVertexArrays(1, &ID);
	}

	// Constructor for ParticlesVBO class
	ParticlesVBO::ParticlesVBO(GLfloat* sphereVerticesParticles, GLsizeiptr size) {
		// Generate a buffer object
		glGenBuffers(1, &ID);

		// Bind the buffer to the GL_ARRAY_BUFFER target
		glBindBuffer(GL_ARRAY_BUFFER, ID);

		// Allocate storage and fill it with data
		glBufferData(GL_ARRAY_BUFFER, size, sphereVerticesParticles, GL_STATIC_DRAW);
	}

	// Bind the Vertex Buffer Object (VBO)
	void ParticlesVBO::ParticlesBind() {
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	// Unbind the Vertex Buffer Object (VBO)
	void ParticlesVBO::ParticlesUnbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// Delete the Vertex Buffer Object (VBO)
	void ParticlesVBO::ParticlesDelete() {
		glDeleteBuffers(1, &ID);
	}

} // namespace BufferManagerParticles
