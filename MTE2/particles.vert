#version 330 core

// Input attributes: Position, Color, and Texture Coordinates
layout (location = 0) in vec3 aPos;         // Vertex position
layout (location = 2) in vec3 aColor;       // Vertex color (assumed to be normal, normalized position)
layout (location = 1) in vec2 aTexCoords;   // Texture coordinates

// Output variable for fragment shader
out vec3 FragColor; 

// Uniform matrices for model and camera transformations
uniform mat4 modelParticles;    // Model transformation matrix
uniform mat4 camMatrixParticles; // Camera transformation matrix

// Main function for the vertex shader
void main()
{
    // Calculate the final position of the vertex in clip space
    gl_Position = camMatrixParticles * modelParticles * vec4(aPos, 1.0);
    
    // Assuming aColor represents the normal (normalized position)
    // Color the fragment based on normals (even: RGB(107, 138, 71), odd: RGB(246, 201, 21))
    if (int(aColor.x * 255) % 2 == 0) {
        // Even segment
        FragColor = vec3(107.0 / 255.0, 138.0 / 255.0, 71.0 / 255.0);  // RGB(107, 138, 71) - Even color
    } else {
        // Odd segment
        FragColor = vec3(246.0 / 255.0, 201.0 / 255.0, 21.0 / 255.0);  // RGB(246, 201, 21) - Odd color
    }
}
