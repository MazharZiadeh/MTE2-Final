#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aColor;
layout (location = 1) in vec2 aTexCoords;

out vec3 FragColor;

uniform mat4 modelParticles;
uniform mat4 camMatrixParticles;

void main()
{
    gl_Position = camMatrixParticles * modelParticles * vec4(aPos, 1.0);
    
    // Assuming aColor is the normal (normalized position)
    // Color based on normals (even: 6b8a47, odd: f6c915)
    if (int(aColor.x * 255) % 2 == 0) {
        // Even segment
        FragColor = vec3(107.0 / 255.0, 138.0 / 255.0, 71.0 / 255.0);  // RGB(107, 138, 71) - Even color
    } else {
        // Odd segment
        FragColor = vec3(246.0 / 255.0, 201.0 / 255.0, 21.0 / 255.0);  // RGB(246, 201, 21) - Odd color
    }
}
