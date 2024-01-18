#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Inputs the color from the Vertex Shader
in vec3 color;

void main()
{
    // Assign the color orange to FragColor without using textures
    FragColor = vec4(1.0, 0.5, 0.0, 1.0); // Orange color in RGBA format
}