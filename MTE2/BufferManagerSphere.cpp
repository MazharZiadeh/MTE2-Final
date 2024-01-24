// BufferManagerSphere.cpp

// Including the header file for this implementation.
#include "BufferManagerSphere.h"

// Namespace declaration for encapsulating the classes and functions.
namespace BufferManagerSphere {

    // Implementation of SphereEBO constructor.
    SphereEBO::SphereEBO(GLuint* indicesSphere, GLsizeiptr size) {
        // Generate a buffer object.
        glGenBuffers(1, &ID);

        // Bind the buffer object to the GL_ELEMENT_ARRAY_BUFFER target.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

        // Copy the index data to the buffer.
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indicesSphere, GL_STATIC_DRAW);
    }

    // Function to bind the Element Buffer Object (EBO).
    void SphereEBO::SphereBind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    }

    // Function to unbind the Element Buffer Object (EBO).
    void SphereEBO::SphereUnbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    // Function to delete the Element Buffer Object (EBO).
    void SphereEBO::SphereDelete() {
        glDeleteBuffers(1, &ID);
    }

    // Implementation of SphereVAO constructor.
    SphereVAO::SphereVAO() {
        // Generate a vertex array object.
        glGenVertexArrays(1, &ID);
    }

    // Function to link attributes for the Vertex Array Object (VAO).
    void SphereVAO::LinkAttrib(SphereVBO& SphereVBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
        // Bind the associated Vertex Buffer Object (VBO).
        SphereVBO.SphereBind();

        // Specify the data format for the attribute at the given layout index.
        glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);

        // Enable the specified attribute layout.
        glEnableVertexAttribArray(layout);

        // Unbind the associated Vertex Buffer Object (VBO).
        SphereVBO.SphereUnbind();
    }

    // Function to bind the Vertex Array Object (VAO).
    void SphereVAO::SphereBind() {
        glBindVertexArray(ID);
    }

    // Function to unbind the Vertex Array Object (VAO).
    void SphereVAO::SphereUnbind() {
        glBindVertexArray(0);
    }

    // Function to delete the Vertex Array Object (VAO).
    void SphereVAO::SphereDelete() {
        glDeleteVertexArrays(1, &ID);
    }

    // Implementation of SphereVBO constructor.
    SphereVBO::SphereVBO(GLfloat* sphereVerticesSphere, GLsizeiptr size) {
        // Generate a buffer object.
        glGenBuffers(1, &ID);

        // Bind the buffer object to the GL_ARRAY_BUFFER target.
        glBindBuffer(GL_ARRAY_BUFFER, ID);

        // Copy the vertex data to the buffer.
        glBufferData(GL_ARRAY_BUFFER, size, sphereVerticesSphere, GL_STATIC_DRAW);
    }

    // Function to bind the Vertex Buffer Object (VBO).
    void SphereVBO::SphereBind() {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    }

    // Function to unbind the Vertex Buffer Object (VBO).
    void SphereVBO::SphereUnbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    // Function to delete the Vertex Buffer Object (VBO).
    void SphereVBO::SphereDelete() {
        glDeleteBuffers(1, &ID);
    }

} // namespace BufferManagerSphere
