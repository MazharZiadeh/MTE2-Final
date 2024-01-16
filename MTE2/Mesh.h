#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class Mesh {
public:
    Mesh(const GLfloat* vertices, GLsizei verticesSize, const GLuint* indices, GLsizei indicesSize);
    ~Mesh();

    void Draw();

private:
    GLuint VAO, VBO, EBO;
    GLsizei indexCount;

    void setupMesh();
};

#endif // MESH_H
