#pragma once

#include <glad/glad.h>

namespace BufferManager {

	class EBO {
	public:
		GLuint ID; // Unique identifier for the Element Buffer Object (EBO)
		EBO(GLuint* indices, GLsizeiptr size); // Constructor for EBO, takes an array of indices and size as parameters
		void Bind(); // Binds the EBO
		void Unbind(); // Unbinds the EBO
		void Delete(); // Deletes the EBO
	};

	class VAO {
	public:
		GLuint ID; // Unique identifier for the Vertex Array Object (VAO)
		VAO(); // Constructor for VAO
		void LinkAttrib(class VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset); // Links a Vertex Buffer Object (VBO) to the VAO
		void Bind(); // Binds the VAO
		void Unbind(); // Unbinds the VAO
		void Delete(); // Deletes the VAO
	};

	class VBO {
	public:
		GLuint ID; // Unique identifier for the Vertex Buffer Object (VBO)
		VBO(GLfloat* vertices, GLsizeiptr size); // Constructor for VBO, takes an array of vertices and size as parameters
		void Bind(); // Binds the VBO
		void Unbind(); // Unbinds the VBO
		void Delete(); // Deletes the VBO
	};

} // namespace BufferManager
