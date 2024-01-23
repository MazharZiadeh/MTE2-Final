#ifndef MYSHADER_H
#define MYSHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);

    void Activate();

    void Delete();

    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec3(const std::string& name, const glm::vec3& value) const;
    void SetMat4(const std::string& name, const glm::mat4& value) const;

    // New functions for handling lighting uniforms
    void SetVec3(const std::string& name, const glm::vec3& value, bool normalize = false) const;
    void SetVec3(const std::string& name, float x, float y, float z, bool normalize = false) const;

private:
    void CompileShader(unsigned int shader, const char* shaderCode);
    void CheckCompileErrors(unsigned int shader, std::string type);
};

#endif // MYSHADER_H
