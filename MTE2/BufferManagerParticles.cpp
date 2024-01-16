// BufferManagerParticles.cpp

#include "BufferManagerParticles.h"

namespace BufferManagerParticles {

	ParticleEBO::ParticleEBO(GLuint* indicesParticle, GLsizeiptr size) {
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indicesParticle, GL_STATIC_DRAW);
	}

	void ParticleEBO::Bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	void ParticleEBO::Unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void ParticleEBO::Delete() {
		glDeleteBuffers(1, &ID);
	}

	ParticleVAO::ParticleVAO() {
		glGenVertexArrays(1, &ID);
	}

	void ParticleVAO::LinkAttrib(ParticleVBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
		VBO.Bind();
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
		VBO.Unbind();
	}

	void ParticleVAO::Bind() {
		glBindVertexArray(ID);
	}

	void ParticleVAO::Unbind() {
		glBindVertexArray(0);
	}

	void ParticleVAO::Delete() {
		glDeleteVertexArrays(1, &ID);
	}

	ParticleVBO::ParticleVBO(GLfloat* verticesParticle, GLsizeiptr size) {
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, size, verticesParticle, GL_STATIC_DRAW);
	}

	void ParticleVBO::Bind() {
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void ParticleVBO::Unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void ParticleVBO::Delete() {
		glDeleteBuffers(1, &ID);
	}

} // namespace BufferManagerParticles
