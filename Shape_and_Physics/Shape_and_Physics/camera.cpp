#include "camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;

	camPosition = position;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(camPosition, camPosition + orientation, up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / (float)height, nearPlane, farPlane);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));

}

void Camera::Inputs(GLFWwindow* window)
{
	// Keyboard inputs 
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camPosition += speed * orientation;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camPosition += -glm::normalize(glm::cross(orientation, up)) * speed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camPosition += speed * -orientation;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camPosition += glm::normalize(glm::cross(orientation, up)) * speed;

	// Up and down
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camPosition += speed * up;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) camPosition -= speed * up;
	// camera speed up and down
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) speed = 0.4f;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) speed = 0.1f;

	//camera rotation
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) orientation = glm::rotate(orientation, glm::radians(-sensitivity * 0.01f), glm::normalize(glm::cross(orientation, up)));
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) orientation = glm::rotate(orientation, glm::radians(sensitivity * 0.01f), glm::normalize(glm::cross(orientation, up)));
	orientation = glm::normalize(orientation);

}
