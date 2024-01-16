#include "Mesh.h"

Mesh::Mesh(const GLfloat* verticesParticle, GLsizei verticesSize, const GLuint* indicesParticle, GLsizei indicesSize)
    : indexCount(indicesSize / sizeof(GLuint)) {
    glGenVertexArrays(1, &ParticleVAO);
    glGenBuffers(1, &ParticleVBO);
    glGenBuffers(1, &ParticleEBO);

    glBindVertexArray(ParticleVAO);

    glBindBuffer(GL_ARRAY_BUFFER, ParticleVBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, verticesParticle, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ParticleEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indicesParticle, GL_STATIC_DRAW);

    setupMesh();

    glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &ParticleVAO);
    glDeleteBuffers(1, &ParticleVBO);
    glDeleteBuffers(1, &ParticleEBO);
}

void Mesh::Draw() {
    glBindVertexArray(ParticleVAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::setupMesh() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
}
