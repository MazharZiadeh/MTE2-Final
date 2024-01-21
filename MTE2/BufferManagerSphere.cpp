// BufferManagerSphere.cpp

#include "BufferManagerSphere.h"

namespace BufferManagerSphere {

	SphereEBO::SphereEBO(GLuint* indicesSphere, GLsizeiptr size) {
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indicesSphere, GL_STATIC_DRAW);
	}

	void SphereEBO::SphereBind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	void SphereEBO::SphereUnbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void SphereEBO::SphereDelete() {
		glDeleteBuffers(1, &ID);
	}

	SphereVAO::SphereVAO() {
		glGenVertexArrays(1, &ID);
	}

	void SphereVAO::LinkAttrib(SphereVBO& SphereVBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
		SphereVBO.SphereBind();
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
		SphereVBO.SphereUnbind();
	}

	void SphereVAO::SphereBind() {
		glBindVertexArray(ID);
	}

	void SphereVAO::SphereUnbind() {
		glBindVertexArray(0);
	}

	void SphereVAO::SphereDelete() {
		glDeleteVertexArrays(1, &ID);
	}

	SphereVBO::SphereVBO(GLfloat* sphereVerticesSphere, GLsizeiptr size) {
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, size, sphereVerticesSphere, GL_STATIC_DRAW);
	}

	void SphereVBO::SphereBind() {
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void SphereVBO::SphereUnbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SphereVBO::SphereDelete() {
		glDeleteBuffers(1, &ID);
	}

} // namespace BufferManagerSphere
