// BufferManager.h
#include <glad/glad.h>

#pragma once

namespace BufferManager {

	class EBO {
	public:
		GLuint ID;

		EBO(GLuint* indices, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();
	};

	class VAO {
	public:
		GLuint ID;
		VAO();
		void LinkAttrib(class VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
		void Bind();
		void Unbind();
		void Delete();
	};

	class VBO {
	public:
		GLuint ID;

		VBO(GLfloat* vertices, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();
	};

} // namespace BufferManager
