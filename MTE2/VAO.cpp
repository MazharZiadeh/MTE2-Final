#include "MyTexture.h"
#include "VAO.h"

// Constructor: Generates a Vertex Array Object (VAO) and assigns its ID
VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

// Links Vertex Buffer Object (VBO) attributes to the VAO
// Parameters:
//   VBO: Reference to the VBO containing vertex data
//   layout: Attribute layout location in the shader
//   numComponents: Number of components in the attribute (e.g., 3 for XYZ)
//   type: Data type of the attribute (e.g., GL_FLOAT for floating-point)
//   stride: Byte offset between consecutive attributes
//   offset: Byte offset of the attribute in the vertex data

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
    // Bind the VBO
    VBO.Bind();

    // Specify the attribute layout in the VAO
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);

    // Enable the attribute at the specified layout location
    glEnableVertexAttribArray(layout);

    // Unbind the VBO
    VBO.Unbind();
}

// Binds the VAO for use in rendering
void VAO::Bind()
{
    glBindVertexArray(ID);
}

// Unbinds the currently bound VAO
void VAO::Unbind()
{
    glBindVertexArray(0);
}

// Deletes the VAO, freeing up resources
void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}
