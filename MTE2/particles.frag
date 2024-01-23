#version 330 core

out vec4 FragColorOut;

void main()
{
    // Set FragColor to deep green (R=0, G=0.5, B=0)
    vec3 deepGreen = vec3(0.0, 0.5, 0.0);
    
    FragColorOut = vec4(deepGreen, 1.0);
}
