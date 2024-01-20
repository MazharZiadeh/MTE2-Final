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
    // Cube 1 (contrainer)
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
std::vector<Particles> currentParticles;


//flagzzzz...................................................................

bool pauseParticles = false; // Flag to control particle motion

bool refreshParticles = false; // Flag to control particle refresh

int numParticles = 10; // Initial number of particles
bool wireframeMode = false;

//,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,


void initializeParticles() {
    // Seed for random number generation
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < numParticles; ++i) {                                // Adjust number of particles as needed, 10 is my particlse numbers
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

        float radius = 0.1f;

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


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        // Set a flag to indicate that particles should be refreshed
        refreshParticles = true;
    }
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_O) {
            // Toggle wireframe mode
            wireframeMode = !wireframeMode;
            glPolygonMode(GL_FRONT_AND_BACK, wireframeMode ? GL_LINE : GL_FILL);
        }
        if (key == GLFW_KEY_G) {
            // Decrease the number of particles by 1, with a minimum of 1
            numParticles = std::max(1, numParticles - 1);
            refreshParticles = true;
        }
        else if (key == GLFW_KEY_H) {
            // Increase the number of particles by 1
            numParticles += 1;
            refreshParticles = true;
        }
        else if (key == GLFW_KEY_J) {
            numParticles = 10; // Adjust to your initial value
            refreshParticles = true;
        }
        if (key == GLFW_KEY_P && action == GLFW_PRESS) {
            // Toggle the pause flag
            pauseParticles = !pauseParticles;
        }

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
    BufferManagerParticles::ParticlesVBO particlesVBO1(vertices, sizeof(vertices));
    BufferManagerParticles::ParticlesEBO particlesEBO1(indicesCube, sizeof(indicesCube));

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

    // Set the key callback function
    glfwSetKeyCallback(window, key_callback);
    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the color and depth buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0);  // Black-blue color in RGBA
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Enable wireframe mode if necessary
        if (wireframeMode) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        // Activate the shader programs
        shaderProgram.Activate();
        camera.Inputs(window);
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

        // Draw the main cube 
        glm::mat4 mainCubeModel = glm::scale(glm::mat4(10.0f), glm::vec3(2.0f)); // Adjust scale as needed
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(mainCubeModel));
        CheckOpenGLError("Before Container Rendering");
        VAO1.Bind();
        EBO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indicesCube) / sizeof(int), GL_UNSIGNED_INT, 0);
        EBO1.Unbind();
        VAO1.Unbind();
        CheckOpenGLError("after Container Rendering");

        // Check if particles need to be refreshed
        if (refreshParticles) {
            // Clear the current particles and reinitialize
            currentParticles.clear();
            initializeParticles();

            // Reset the flag
            refreshParticles = false;
        }

        // Activate the particle shader program
        newshaderProgram.Activate();
        camera.Matrix(45.0f, 0.1f, 100.0f, newshaderProgram, "camMatrixParticles");

        for (auto& particle : currentParticles) {
            if (!pauseParticles) {
                particle.update(0.05f); // Adjust delta time as needed
                particle.handleWallCollisions();

                for (auto& other : currentParticles) {
                    if (&particle != &other) {
                        particle.handleParticlesCollisions(other);
                    }
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
            glDrawElements(GL_TRIANGLES, sizeof(indicesCube) / sizeof(int), GL_UNSIGNED_INT, 0);
            particlesEBO1.ParticlesUnbind();
            particlesVAO1.ParticlesUnbind();
        }

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
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
