#version 330 core

out vec4 FragColorOut;

in vec3 FragColor;

void main()
{
    FragColorOut = vec4(FragColor, 1.0);
}
