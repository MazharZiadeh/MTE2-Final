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
#include "Particle.h"

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

GLfloat verticesParticle[] = {
    // Cube 1 (contrainer)
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

GLuint indicesParticle[] = {
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


std::vector<Particle> particles;

void initializeParticles() {
    // Seed for random number generation
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < 100; ++i) {
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

        particles.emplace_back(position, velocity, radius);
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

    // Create shader program and set up OpenGL settings
    Shader shaderProgram("default.vert", "default.frag");

    // Create and set up Vertex Array Object (VAO) for Cube 1
    BufferManager::VAO VAO1;
    VAO1.Bind();


    // ((Create and set up Vertex Array Object (VAO) for particles)
    BufferManagerParticles::ParticleVAO VAO2;
    VAO2.Bind();

    // Create and set up Vertex Buffer Object (VBO) and Element Buffer Object (EBO) for Cube 1
    BufferManager::VBO VBO1(vertices, sizeof(vertices));
    BufferManager::EBO EBO1(indicesCube, sizeof(indicesCube));


    // Create and set up Vertex Buffer Object (VBO) and Element Buffer Object (EBO) for particles
    BufferManagerParticles::ParticleVBO VBO2(verticesParticle, sizeof(verticesParticle));
    BufferManagerParticles::ParticleEBO EBO2(indicesParticle, sizeof(indicesParticle));

    // Link attributes in VAO to the VBO for Cube 1
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();


    // Link attributes in VAO to the VBO for particles
    VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO2.Unbind();
    VBO2.Unbind();
    EBO2.Unbind();

    // Enable depth testing and set up the camera
    glEnable(GL_DEPTH_TEST);
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    // Initialize particles
    initializeParticles();

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the color and depth buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Enable wireframe mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // Activate the shader program
        shaderProgram.Activate();

        // Process camera inputs and set camera matrix in the shader
        camera.Inputs(window);
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

        // Draw the main cube (replace this with actual rendering code)
        glm::mat4 mainCubeModel = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)); // Adjust scale as needed
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(mainCubeModel));
        // Bind VAO, then texture, and draw the main cube
        VAO1.Bind();

        // Draw the cube
        glDrawElements(GL_TRIANGLES, sizeof(indicesCube) / sizeof(int), GL_UNSIGNED_INT, 0);

        // Check for OpenGL errors
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            // Handle the error (you might want to log it or print a message)
            // For simplicity, I'll just print an error message to the console
            std::cerr << "OpenGL error: " << error << std::endl;
        }

        // Unbind the VAO
        VAO1.Unbind();



        // Update and draw particles
        for (auto& particle : particles) {
            // Update particle position based on velocity and time (the bigger the delta time, the faster the motion)
            // Smaller delta time can result in smoother motion but may require more frequent updates
            particle.update(0.01f); // Adjust delta time as needed

            // Handle collisions with walls or other objects
            particle.handleWallCollisions();

            // Draw particle (replace this with actual rendering code)
            // Translate the particle model matrix to its current position
            // Scale the particle to make it smaller (the smaller the scale, the smaller the particle)
            // Adjust both translation and scale factors as needed
            glm::mat4 particleModel = glm::translate(glm::mat4(1.0), particle.getPosition())
                * glm::scale(glm::mat4(1.0f), glm::vec3(particle.getRadius())); // Adjust scale as needed

            // Set the model matrix in the shader program
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(particleModel));

            // Bind VAO and draw a small cube for each particle
            VAO2.Bind();
            glDrawElements(GL_TRIANGLES, sizeof(indicesParticle) / sizeof(int), GL_UNSIGNED_INT, 0);

            // Unbind VAO for the small cube
            VAO2.Unbind();
        }

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }



    // Print OpenGL version and extensions
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "OpenGL Extensions: " << glGetString(GL_EXTENSIONS) << std::endl;

    // Clean up resources
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    VAO2.Delete();
    VBO2.Delete();
    EBO2.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
