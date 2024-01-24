#include "Camera.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
Camera::Camera(int width, int height, glm::vec3 position) // Constructor with vectors as inputs 
{
	// Constructor to initialize camera properties 
	Camera::width = width; // width of the window
	Camera::height = height; // height of the window
	Position = position; // position of the camera
}
void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform) // Function to create the matrix to be passed to the shader
{
	// Calculates the view and projection matrices and passes them to the shader
	glm::mat4 view = glm::lookAt(Position, Position + Orientation, Up); // Calculates the view matrix
	glm::mat4 projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane); // Calculates the projection matrix

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view)); // Passes the combined matrix to the shader
}
/**
 * Handles the inputs for camera movement and rotation.
 *
 * @param window The GLFW window object.
 */
void Camera::Inputs(GLFWwindow* window) // Function to handle camera inputs
{
	// Handles keyboard inputs for camera movement, and mouse inputs for camera rotation 
	// Camera speed and mouse sensitivity are set with the following constants
	// by pressing the left shift key, the camera will move 4 times faster 
	// by pressing the left control key, the camera will move 4 times slower
	// by pressing the left mouse button, the camera will rotate
	// by moving the mouse, the camera will rotate
	// wsad - movement
	// The camera's orientation is calculated with the following variables
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
	{
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}
	// Handles mouse inputs for camera rotation
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}
		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;
		// Calculates the new orientation of the camera based on mouse movement
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));
		// Checks if the new orientation is within the allowed range
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Shows mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}