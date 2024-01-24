#version 330 core

// Output variable for the fragment shader, representing the final color
out vec4 FragColorOut; 

// Input variable, representing the color calculated in the vertex shader
in vec3 FragColor;  

// Main function for the fragment shader
void main()
{
    // Set the output color with an alpha value of 1.0
    FragColorOut = vec4(FragColor, 1.0);
}
