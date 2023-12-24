#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "MyShader.h"

class Camera
{
public:
    // Camera position in 3D space
    glm::vec3 Position;
    // Camera orientation (where it's looking)
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    // Up vector for the camera
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

    // Flag to determine if it's the first click for mouse input
    bool firstClick = true;

    // Width and height of the viewport
    int width;
    int height;

    // Camera movement speed and sensitivity settings
    float speed = 0.1f;
    float sensitivity = 100.0f;

    // Constructor for the Camera class
    Camera(int width, int height, glm::vec3 position);

    // Function to calculate the view matrix and projection matrix, and set them in the shader
    void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);

    // Function to handle user inputs for camera movement
    void Inputs(GLFWwindow* window);
};

#endif
