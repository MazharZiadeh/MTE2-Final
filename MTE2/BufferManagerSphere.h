// BufferManagerSphere.h
#include <glad/glad.h>

#pragma once

namespace BufferManagerSphere { // Define the namespace for this module

	class SphereEBO { // Define the class for the Element Buffer Object (EBO)
	public:
		GLuint ID;

		SphereEBO(GLuint* indicesSphere, GLsizeiptr size);

		void SphereBind();
		void SphereUnbind();
		void SphereDelete();
	};

	class SphereVAO { // Define the class for the Vertex Array Object (VAO)
	public:
		GLuint ID;
		SphereVAO();
		void LinkAttrib(class SphereVBO& SphereVBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
		void SphereBind();
		void SphereUnbind();
		void SphereDelete();
	};

	class SphereVBO { // Define the class for the Vertex Buffer Object (VBO)
	public:
		GLuint ID;

		SphereVBO(GLfloat* sphereVerticesSphere, GLsizeiptr size);

		void SphereBind();
		void SphereUnbind();
		void SphereDelete();
	};

} // namespace BufferManagerSphere
