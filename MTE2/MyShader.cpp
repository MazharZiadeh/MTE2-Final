#include "MyShader.h"
#include <glm/gtc/matrix_transform.hpp>  


/**
 * @brief Constructs a Shader object with the given vertex and fragment shader file paths.
 *
 * This constructor loads the shader code from the specified files, compiles the shaders,
 * links them into a shader program, and performs error checking.
 *
 * @param vertexPath The file path of the vertex shader.
 * @param fragmentPath The file path of the fragment shader.
 */

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    // Load shaders from file
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // Ensure ifstream objects can throw exceptions
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // Open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        // Read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // Close file handlers
        vShaderFile.close();
        fShaderFile.close();

        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // Compile shaders
    unsigned int vertex, fragment;

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    CompileShader(vertex, vShaderCode);

    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    CompileShader(fragment, fShaderCode);

    // Shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    CheckCompileErrors(ID, "PROGRAM");

    // Delete shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Activate() {
    glUseProgram(ID);
}

void Shader::Delete() {
    glDeleteProgram(ID);
}

void Shader::CompileShader(unsigned int shader, const char* shaderCode) {
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);
    CheckCompileErrors(shader, "SHADER");
}
 //
void Shader::CheckCompileErrors(unsigned int shader, std::string type) { // NOLINT(misc-unused-parameters)
    int success;
    char infoLog[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}




void Shader::SetBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
}

void Shader::SetInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));

}

void Shader::SetVec3(const std::string& name, const glm::vec3& value, bool normalize) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, normalize ? glm::value_ptr(glm::normalize(value)) : glm::value_ptr(value));
}

void Shader::SetVec3(const std::string& name, float x, float y, float z, bool normalize) const {
    if (normalize) {
        glm::vec3 normalizedVec = glm::normalize(glm::vec3(x, y, z));
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(normalizedVec));
    }
    else {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
}
