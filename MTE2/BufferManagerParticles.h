// BufferManagerParticles.h
#include <glad/glad.h>

#pragma once

namespace BufferManagerParticles {

	class ParticlesEBO {
	public:
		GLuint ID;

		ParticlesEBO(GLuint* indicesParticles, GLsizeiptr size);

		void ParticlesBind();
		void ParticlesUnbind();
		void ParticlesDelete();
	};

	class ParticlesVAO {
	public:
		GLuint ID;
		ParticlesVAO();
		void LinkAttrib(class ParticlesVBO& ParticlesVBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
		void ParticlesBind();
		void ParticlesUnbind();
		void ParticlesDelete();
	};

	class ParticlesVBO {
	public:
		GLuint ID;

		ParticlesVBO(GLfloat* verticesParticles, GLsizeiptr size);

		void ParticlesBind();
		void ParticlesUnbind();
		void ParticlesDelete();
	};

} // namespace BufferManagerParticles
