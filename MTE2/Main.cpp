#include <filesystem>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "MyShader.h"
#include "BufferManager.h"
#include "BufferManagerParticles.h"
#include "Camera.h"
#include "Particles.h"

const unsigned int width = 1920;
const unsigned int height = 1080;

GLfloat vertices[] = {
    // Cube 1 (container)
    // Positions          // Normals           // Texture Coords
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // 0
    -1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // 1
     1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // 2
     1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // 3
    -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // 4
    -1.0f,  1.0f, -1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // 5
     1.0f,  1.0f, -1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // 6
     1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // 7
};

GLuint indicesCube[] = {
    0, 1, 2, // front face (Cube 1)
    0, 2, 3,
    4, 5, 1, // left face (Cube 1)
    4, 1, 0,
    3, 2, 6, // right face (Cube 1)
    3, 6, 7,
    1, 5, 6, // top face (Cube 1)
    1, 6, 2,
    4, 0, 3, // bottom face (Cube 1)
    4, 3, 7,
    5, 4, 7, // back face (Cube 1)
    5, 7, 6
};

GLfloat verticesParticles[] = {
    // particles
    // Positions          // Normals           // Texture Coords
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // 0
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // 1
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // 2
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // 3
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // 4
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // 5
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // 6
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // 7
};

GLuint indicesParticles[] = {
    0, 1, 2, // front face
    0, 2, 3,
    4, 5, 1, // left face
    4, 1, 0,
    3, 2, 6, // right face
    3, 6, 7,
    1, 5, 6, // top face
    1, 6, 2,
    4, 0, 3, // bottom face
    4, 3, 7,
    5, 4, 7, // back face
    5, 7, 6
};

std::vector<Particles> currentParticles;

void initializeParticles() {
    // Seed for random number generation
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < 60; ++i) {
        glm::vec3 position(
            static_cast<float>(std::rand()) / RAND_MAX * 2.0f - 1.0f,
            static_cast<float>(std::rand()) / RAND_MAX * 2.0f - 1.0f,
            static_cast<float>(std::rand()) / RAND_MAX * 2.0f - 1.0f
        );

        glm::vec3 velocity(
            static_cast<float>(std::rand()) / RAND_MAX * 2.0f - 1.0f,
            static_cast<float>(std::rand()) / RAND_MAX * 2.0f - 1.0f,
            static_cast<float>(std::rand()) / RAND_MAX * 2.0f - 1.0f
        );

        float radius = 0.05f;

        currentParticles.emplace_back(position, velocity, radius);
    }
}
// Function to check OpenGL errors
void CheckOpenGLError(const char* operation) {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error after " << operation << ": " << error << std::endl;
    }
}


int main() {
    // Initialize GLFW
    glfwInit();

    // Set GLFW window hints for OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(width, height, "MTE2", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load OpenGL functions using GLAD
    gladLoadGL();

    // Set the viewport dimensions
    glViewport(0, 0, width, height);

    // Create shader program and set up OpenGL settings for cube 
    Shader shaderProgram("cube.vert", "cube.frag");
    // Create shader program and set up OpenGL settings for particles  
    Shader newshaderProgram("particles.vert", "particles.frag");

    // Create and set up Vertex Array Object (VAO) for Cube 1
    BufferManager::VAO VAO1;
    VAO1.Bind();

    // Create and set up Vertex Array Object (VAO) for particles
    BufferManagerParticles::ParticlesVAO particlesVAO1;
    particlesVAO1.ParticlesBind();

    // Create and set up Vertex Buffer Object (VBO) and Element Buffer Object (EBO) for Cube 1
    BufferManager::VBO VBO1(vertices, sizeof(vertices));
    BufferManager::EBO EBO1(indicesCube, sizeof(indicesCube));

    // Create and set up Vertex Buffer Object (VBO) and Element Buffer Object (EBO) for particles
    BufferManagerParticles::ParticlesVBO particlesVBO1(verticesParticles, sizeof(verticesParticles));
    BufferManagerParticles::ParticlesEBO particlesEBO1(indicesParticles, sizeof(indicesParticles));

    // Link attributes in VAO to the VBO for Cube 1
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Link attributes in VAO to the VBO for particles
    particlesVAO1.LinkAttrib(particlesVBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    particlesVAO1.LinkAttrib(particlesVBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    particlesVAO1.LinkAttrib(particlesVBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    particlesVAO1.ParticlesUnbind();
    particlesVBO1.ParticlesUnbind();
    particlesEBO1.ParticlesUnbind();
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Set the depth function to less than or equal
    glDepthFunc(GL_LEQUAL);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 3.0f));  // Move the camera back along the z-axis

    // Initialize particles
    initializeParticles();

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the color and depth buffers
        CheckOpenGLError("before clear buffers");
        glClearColor(0.0f, 0.0f, 0.2f, 1.0f);  // Black-blue color in RGBA
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        CheckOpenGLError("after clear buffers");

        // Enable wireframe mode
        CheckOpenGLError("before enable wireframe mode");
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        CheckOpenGLError("after enable wireframe mode");

        // Activate the shader programs
        CheckOpenGLError("before activate shader program");
        shaderProgram.Activate();
        camera.Inputs(window);
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
        CheckOpenGLError("after activate shader program");

        // Draw the main cube 
        glm::mat4 mainCubeModel = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f)); // Adjust scale as needed
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(mainCubeModel));
        CheckOpenGLError("just before binding");
        VAO1.Bind();
        EBO1.Bind();
        CheckOpenGLError("before draw main cube and binding");
        glDrawElements(GL_TRIANGLES, sizeof(indicesCube) / sizeof(int), GL_UNSIGNED_INT, 0);
        CheckOpenGLError("after draw main cube and before unbinding");
        //EBO1.Unbind();
        //VAO1.Unbind();
        CheckOpenGLError("after draw main cube and unbinding");

        // Activate the particle shader program
        CheckOpenGLError("before particle shader program");
        newshaderProgram.Activate();
        camera.Matrix(45.0f, 0.1f, 100.0f, newshaderProgram, "camMatrixParticles");
        CheckOpenGLError("after activate particle shader program");
        // Update and draw particles
        for (auto& particle : currentParticles) {
            particle.update(0.01f); // Adjust delta time as needed
            particle.handleWallCollisions();


            for (auto& other : currentParticles) {
                if (&particle != &other) {
					particle.handleParticlesCollisions(other);
				}
			}
            // Draw particles
            glm::mat4 particlesModel = glm::translate(glm::mat4(1.0), particle.getPosition())
                * glm::scale(glm::mat4(1.0f), glm::vec3(particle.getRadius())); // Adjust scale as needed

            // Set the model matrix in the shader program
            glUniformMatrix4fv(glGetUniformLocation(newshaderProgram.ID, "modelParticles"), 1, GL_FALSE, glm::value_ptr(particlesModel));

            // Bind VAO and draw a small cube for each particle
            particlesVAO1.ParticlesBind();
            particlesEBO1.ParticlesBind();
            glDrawElements(GL_TRIANGLES, sizeof(indicesParticles) / sizeof(int), GL_UNSIGNED_INT, 0);
            //particlesEBO1.ParticlesUnbind();
            //particlesVAO1.ParticlesUnbind();
            CheckOpenGLError("after draw particles and then unbding ");
        }
        CheckOpenGLError("before swapping buffer");

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
        CheckOpenGLError("after swapping buffer");

    }
    // Clean up resources
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    particlesVAO1.ParticlesDelete();
    particlesVBO1.ParticlesDelete();
    particlesEBO1.ParticlesDelete();
    shaderProgram.Delete();
    newshaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
