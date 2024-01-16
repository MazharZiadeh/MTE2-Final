// buffermanagerparticles.cpp

#include "BufferManagerParticles.h"

namespace BufferManagerParticles {

    SphereVBO::SphereVBO(GLfloat* vertices, GLsizeiptr size)
    {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    void SphereVBO::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    }

    void SphereVBO::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void SphereVBO::Delete()
    {
        glDeleteBuffers(1, &ID);
    }

    SphereVAO::SphereVAO()
    {
        glGenVertexArrays(1, &ID);
    }

    void SphereVAO::LinkAttrib(SphereVBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
    {
        VBO.Bind();
        glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
        VBO.Unbind();
    }

    void SphereVAO::Bind()
    {
        glBindVertexArray(ID);
    }

    void SphereVAO::Unbind()
    {
        glBindVertexArray(0);
    }

    void SphereVAO::Delete()
    {
        glDeleteVertexArrays(1, &ID);
    }

    SphereEBO::SphereEBO(GLuint* indices, GLsizeiptr size)
    {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    }

    void SphereEBO::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    }

    void SphereEBO::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void SphereEBO::Delete()
    {
        glDeleteBuffers(1, &ID);
    }

} // namespace BufferManagerParticles
