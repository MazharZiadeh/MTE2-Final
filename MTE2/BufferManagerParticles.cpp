// BufferManagerParticles.cpp

#include "BufferManagerParticles.h"

namespace BufferManagerParticles {

	ParticlesEBO::ParticlesEBO(GLuint* indicesParticles, GLsizeiptr size) {
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indicesParticles, GL_STATIC_DRAW);
	}

	void ParticlesEBO::ParticlesBind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	void ParticlesEBO::ParticlesUnbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void ParticlesEBO::ParticlesDelete() {
		glDeleteBuffers(1, &ID);
	}

	ParticlesVAO::ParticlesVAO() {
		glGenVertexArrays(1, &ID);
	}

	void ParticlesVAO::LinkAttrib(ParticlesVBO& ParticlesVBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
		ParticlesVBO.ParticlesBind();
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
		ParticlesVBO.ParticlesUnbind();
	}

	void ParticlesVAO::ParticlesBind() {
		glBindVertexArray(ID);
	}

	void ParticlesVAO::ParticlesUnbind() {
		glBindVertexArray(0);
	}

	void ParticlesVAO::ParticlesDelete() {
		glDeleteVertexArrays(1, &ID);
	}

	ParticlesVBO::ParticlesVBO(GLfloat* sphereVerticesParticles, GLsizeiptr size) {
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, size, sphereVerticesParticles, GL_STATIC_DRAW);
	}

	void ParticlesVBO::ParticlesBind() {
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void ParticlesVBO::ParticlesUnbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void ParticlesVBO::ParticlesDelete() {
		glDeleteBuffers(1, &ID);
	}

} // namespace BufferManagerParticles
