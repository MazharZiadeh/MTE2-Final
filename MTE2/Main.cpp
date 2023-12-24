#include <filesystem>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "MyTexture.h"
#include "MyShader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"

const unsigned int width = 500;
const unsigned int height = 500;

GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-1.0f, -1.0f,  1.0f,     0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // 0
	-1.0f,  1.0f,  1.0f,     0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // 1
	 1.0f,  1.0f,  1.0f,     0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // 2
	 1.0f, -1.0f,  1.0f,     0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // 3
	-1.0f, -1.0f, -1.0f,     0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // 4
	-1.0f,  1.0f, -1.0f,     0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // 5
	 1.0f,  1.0f, -1.0f,     0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // 6
	 1.0f, -1.0f, -1.0f,     0.0f, 0.0f, 1.0f,  1.0f, 0.0f  // 7
};

GLuint indices[] =
{
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

/**
 * @brief The main function of the program.
 *
 * This function initializes GLFW, creates a GLFW window, loads OpenGL functions using GLAD,
 * sets up OpenGL settings, creates shader program, vertex array object (VAO), vertex buffer object (VBO),
 * and element buffer object (EBO), loads textures, enables depth testing, sets up the camera,
 * and enters the main rendering loop. It also cleans up resources before exiting.
 *
 * @return 0 upon successful execution.
 */
int main()
{
	// Initialize GLFW
	glfwInit();

	// Set GLFW window hints for OpenGL version and profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, "MTE2", NULL, NULL);
	if (window == NULL)
	{
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

	// Create and set up Vertex Array Object (VAO)
	VAO VAO1;
	VAO1.Bind();

	// Create and set up Vertex Buffer Object (VBO) and Element Buffer Object (EBO)
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Link attributes in VAO to the VBO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Set up paths for textures
	std::string parentDir = std::filesystem::current_path().parent_path().string();
	std::string texPath = "/res/Textures/";

	// Create a full path for the texture image
	std::string fullPath = parentDir + texPath + "elgato.png";
	std::cout << "Full Path: " << fullPath << std::endl;

	// Load texture
	Texture MyImage(fullPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	MyImage.texUnit(shaderProgram, "tex0", 0);

	// Enable depth testing and set up the camera
	glEnable(GL_DEPTH_TEST);
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	// Main rendering loop
	while (!glfwWindowShouldClose(window))
	{
		// Clear the color and depth buffers
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Activate the shader program
		shaderProgram.Activate();

		// Process camera inputs and set camera matrix in the shader
		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		// Update model matrix to rotate the cube
		static float angle = 0.0f;
		glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		angle += 0.5f; // Adjust the rotation speed as needed

		// Set the model matrix in the shader
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

		// Bind VAO, then texture, and draw the cube
		VAO1.Bind();
		MyImage.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Unbind VAO and texture
		VAO1.Unbind();
		MyImage.Unbind();

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "OpenGL Extensions: " << glGetString(GL_EXTENSIONS) << std::endl;

	// Clean up resources
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	MyImage.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}