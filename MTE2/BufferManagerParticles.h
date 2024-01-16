// buffermanagerparticles.h

#pragma once

#include <glad/glad.h>

namespace BufferManagerParticles {

    class SphereEBO {
    public:
        GLuint ID; // Unique identifier for the Element Buffer Object (EBO)
        SphereEBO(GLuint* indices, GLsizeiptr size); // Constructor for EBO, takes an array of indices and size as parameters
        void Bind(); // Binds the EBO
        void Unbind(); // Unbinds the EBO
        void Delete(); // Deletes the EBO
    };

    class SphereVAO {
    public:
        GLuint ID; // Unique identifier for the Vertex Array Object (VAO)
        SphereVAO(); // Constructor for VAO
        void LinkAttrib(class SphereVBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset); // Links a Vertex Buffer Object (VBO) to the VAO
        void Bind(); // Binds the VAO
        void Unbind(); // Unbinds the VAO
        void Delete(); // Deletes the VAO
    };

    class SphereVBO {
    public:
        GLuint ID; // Unique identifier for the Vertex Buffer Object (VBO)
        SphereVBO(GLfloat* vertices, GLsizeiptr size); // Constructor for VBO, takes an array of vertices and size as parameters
        void Bind(); // Binds the VBO
        void Unbind(); // Unbinds the VBO
        void Delete(); // Deletes the VBO
    };

} // namespace BufferManagerParticles
