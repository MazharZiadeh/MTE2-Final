// BufferManagerParticles.h
#include <glad/glad.h>

#pragma once

namespace BufferManagerParticles {

	class ParticleEBO {
	public:
		GLuint ID;

		ParticleEBO(GLuint* indicesParticle, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();
	};

	class ParticleVAO {
	public:
		GLuint ID;

		ParticleVAO();

		void LinkAttrib(class ParticleVBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
		void Bind();
		void Unbind();
		void Delete();
	};

	class ParticleVBO {
	public:
		GLuint ID;

		ParticleVBO(GLfloat* verticesParticle, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();
	};

} // namespace BufferManagerParticles
