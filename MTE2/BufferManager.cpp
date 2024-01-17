#include "BufferManager.h"

namespace BufferManager {

	/**
	 * @brief The BufferManager namespace provides classes for managing OpenGL buffers and vertex arrays.
	 */
	EBO::EBO(GLuint* indicesCube, GLsizeiptr size)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indicesCube, GL_STATIC_DRAW);
	}


	/**
	 * @brief Binds the element buffer object (EBO).
	 */
	void EBO::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	/**
	 * @brief Unbinds the element buffer object (EBO).
	 */
	void EBO::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	/**
	 * @brief Deletes the element buffer object (EBO).
	 */
	void EBO::Delete()
	{
		glDeleteBuffers(1, &ID);
	}

	/**
	 * @brief Constructs a new vertex array object (VAO).
	 */
	VAO::VAO()
	{
		glGenVertexArrays(1, &ID);
	}

	/**
	 * @brief Links a vertex buffer object (VBO) to the vertex array object (VAO).
	 * @param VBO The vertex buffer object to link.
	 * @param layout The attribute layout location.
	 * @param numComponents The number of components per attribute.
	 * @param type The data type of the attribute.
	 * @param stride The stride between consecutive attributes.
	 * @param offset The offset of the attribute data.
	 */
	void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
	{
		VBO.Bind();
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
		VBO.Unbind();
	}

	/**
	 * @brief Binds the vertex array object (VAO).
	 */
	void VAO::Bind()
	{
		glBindVertexArray(ID);
	}

	/**
	 * @brief Unbinds the vertex array object (VAO).
	 */
	void VAO::Unbind()
	{
		glBindVertexArray(0);
	}

	/**
	 * @brief Deletes the vertex array object (VAO).
	 */
	void VAO::Delete()
	{
		glDeleteVertexArrays(1, &ID);
	}

	/**
	 * @brief Constructs a new vertex buffer object (VBO).
	 * @param vertices The vertex data.
	 * @param size The size of the vertex data.
	 */
	VBO::VBO(GLfloat* vertices, GLsizeiptr size)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	/**
	 * @brief Binds the vertex buffer object (VBO).
	 */
	void VBO::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	/**
	 * @brief Unbinds the vertex buffer object (VBO).
	 */
	void VBO::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/**
	 * @brief Deletes the vertex buffer object (VBO).
	 */
	void VBO::Delete()
	{
		glDeleteBuffers(1, &ID);
	}

} // namespace BufferManager
