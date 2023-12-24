// Include guards to prevent multiple inclusion of the header
#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

// Include necessary OpenGL headers
#include <glad/glad.h>

// Include necessary standard C++ headers
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

// Function to read the contents of a file and return it as a string
std::string get_file_contents(const char* filename);

// Shader class declaration
class Shader
{
public:
    // Shader program ID
    GLuint ID;

    // Constructor that takes the file paths for the vertex and fragment shaders
    Shader(const char* vertexFile, const char* fragmentFile);

    // Function to activate the shader program
    void Activate();

    // Function to delete the shader program
    void Delete();

private:
    // Private function to handle compilation errors
    void compileErrors(unsigned int shader, const char* type);
};

// End of include guards
#endif
