#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 viewPos;

// Add uniforms for the gradient colors
uniform vec3 colorLeft;
uniform vec3 colorMiddle;
uniform vec3 colorRight;

void main()
{
    // Calculate the background color using a gradient
    vec3 gradientColor = mix(mix(colorLeft, colorMiddle, TexCoord.x), colorRight, TexCoord.x);

    FragColor = vec4(gradientColor, 1.0);
}
