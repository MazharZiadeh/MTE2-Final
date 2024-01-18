#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Inputs the color from the Vertex Shader
in vec3 color;

void main()
{
    // Assign a color directly to FragColor without using textures
    FragColor = vec4(color, 1.0);
}