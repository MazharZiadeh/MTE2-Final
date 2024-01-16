#version 330 core

out vec4 FragColor;

// Inputs the color from the Vertex Shader
in vec3 color;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;

// Gets the Texture Unit from the main function
uniform sampler2D tex0;

// Uniform color for particles
uniform vec3 particleColor;

void main()
{
    // If particle, use uniform color
    if (tex0 == -1) {
        FragColor = vec4(particleColor, 1.0);
    } else {
        // If sphere, use texture
        FragColor = texture(tex0, texCoord);
    }
}
