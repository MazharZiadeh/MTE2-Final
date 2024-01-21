#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aColor;
layout (location = 1) in vec2 aTexCoords;

out vec3 FragColor;

uniform mat4 modelSphere;
uniform mat4 camMatrixSphere;

void main()
{
    gl_Position = camMatrixSphere * modelSphere * vec4(aPos, 1.0);
    FragColor = aColor;
}