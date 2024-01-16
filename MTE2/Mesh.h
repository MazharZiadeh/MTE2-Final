#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class Mesh {
public:
    Mesh(const GLfloat* verticesParticle, GLsizei verticesSize, const GLuint* indicesParticle, GLsizei indicesSize);
    ~Mesh();

    void Draw();

private:
    GLuint ParticleVAO, ParticleVBO, ParticleEBO;
    GLsizei indexCount;

    void setupMesh();
};

#endif // MESH_H
