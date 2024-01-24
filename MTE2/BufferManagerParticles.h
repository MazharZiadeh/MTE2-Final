// BufferManagerParticles.h
#include <glad/glad.h>

#pragma once
 
namespace BufferManagerParticles { // Define the namespace for this module

	class ParticlesEBO { // Define the class for the Element Buffer Object (EBO)
	public:
		GLuint ID;

		ParticlesEBO(GLuint* indicesParticles, GLsizeiptr size);

		void ParticlesBind();
		void ParticlesUnbind();
		void ParticlesDelete();
	};

	class ParticlesVAO { // Define the class for the Vertex Array Object (VAO)
	public:
		GLuint ID;
		ParticlesVAO();
		void LinkAttrib(class ParticlesVBO& ParticlesVBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
		void ParticlesBind();
		void ParticlesUnbind();
		void ParticlesDelete();
	};

	class ParticlesVBO {	// Define the class for the Vertex Buffer Object (VBO)
	public:
		GLuint ID;

		ParticlesVBO(GLfloat* sphereVerticesParticles, GLsizeiptr size);

		void ParticlesBind();
		void ParticlesUnbind();
		void ParticlesDelete();
	};

} // namespace BufferManagerParticles
