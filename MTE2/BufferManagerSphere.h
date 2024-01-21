// BufferManagerSphere.h
#include <glad/glad.h>

#pragma once

namespace BufferManagerSphere {

	class SphereEBO {
	public:
		GLuint ID;

		SphereEBO(GLuint* indicesSphere, GLsizeiptr size);

		void SphereBind();
		void SphereUnbind();
		void SphereDelete();
	};

	class SphereVAO {
	public:
		GLuint ID;
		SphereVAO();
		void LinkAttrib(class SphereVBO& SphereVBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
		void SphereBind();
		void SphereUnbind();
		void SphereDelete();
	};

	class SphereVBO {
	public:
		GLuint ID;

		SphereVBO(GLfloat* sphereVerticesSphere, GLsizeiptr size);

		void SphereBind();
		void SphereUnbind();
		void SphereDelete();
	};

} // namespace BufferManagerSphere
