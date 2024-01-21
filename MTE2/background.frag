#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform vec3 colorLeft;
uniform vec3 colorMiddle;
uniform vec3 colorRight;

void main()
{
    vec3 gradientColor = mix(mix(colorLeft, colorMiddle, TexCoord.x), colorRight, TexCoord.x);
    FragColor = vec4(gradientColor, 1.0);
}
