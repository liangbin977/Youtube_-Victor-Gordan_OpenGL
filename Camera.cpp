#include "Camera.h"

Camera::Camera(float width, float height, glm::vec3 position)
	:width(width), height(height), position(position) {
};
void Camera::updateMatrix(float angle, float nearLimit, float FarLimit) {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	view = glm::lookAt(position, position + orientation, up);
	proj = glm::perspective(glm::radians(angle), (float)(width / height), nearLimit, FarLimit);

	cameraMatrix = proj * view;
	
};
void Camera::Matrix(Shader& shader, const char* uniform){
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix)); //value_ptr returns a pointer to the first element of the matrix, which is what OpenGL expects for uniform matrix data
}
void Camera::Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += speed * orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position += speed * -glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position += speed * -orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position += speed * glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		position += speed * up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		position += speed * -up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		speed = 0.5f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		speed = 0.1f;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		if(firstClick) {
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));
		if (!glm::angle(newOrientation, up) <= glm::radians(5.0f) || !glm::angle(newOrientation, -up) <= glm::radians(5.0f)) {
			orientation = newOrientation;
		}
		orientation = glm::rotate(orientation, glm::radians(-rotY), up);
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
};

void Camera::ProcessScroll(double yoffset) {
	// yoffset > 0: 向上滚（放大）；yoffset < 0: 向下滚（缩小）
	// 采用加法比例改变 scale，更直观可控
	scale += static_cast<float>(yoffset) * scrollSensitivity;

	if (scale < minScale) scale = minScale;
	if (scale > maxScale) scale = maxScale;
}
glm::vec3 Camera::GetScale() {
	return glm::vec3(scale);
};
void Camera::ProcessModelRotation(GLFWwindow* window) {
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		if (firstClickModel) {
			glfwSetCursorPos(window, (double)(width / 2.0f), (double)(height / 2.0f));
			firstClickModel = false;
		}

		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// 以窗口中心为参考，标准化鼠标偏移到 [-0.5,0.5] 再乘灵敏度->度数
		float normX = (float)((mouseX - (width / 2.0f)) / width);
		float normY = (float)((mouseY - (height / 2.0f)) / height);

		modelRotation.y += -normX * modelRotSensitivity; // 偏航（绕 Y）
		modelRotation.x += -normY * modelRotSensitivity; // 俯仰（绕 X），鼠标上移通常视为俯仰上

		// 限制俯仰角度，避免翻转（可按需调整）
		if (modelRotation.x > 89.0f) modelRotation.x = 89.0f;
		if (modelRotation.x < -89.0f) modelRotation.x = -89.0f;

		// 重置到中心以便下一帧继续测位移
		glfwSetCursorPos(window, (double)(width / 2.0f), (double)(height / 2.0f));
	}
	else {
		if (!firstClickModel) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			firstClickModel = true;
		}
	}
}