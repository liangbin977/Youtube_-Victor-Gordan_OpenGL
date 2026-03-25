#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shaderClass.h"

class Camera {
public:
	glm::vec3 position;
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	bool firstClick = true;

	float width;
	float height;

	// 滚轮缩放相关
	float scale = 1.0f;               // 当前缩放倍数（默认 1.0）
	float scrollSensitivity = 0.15f;  // 每个滚轮单位改变的比例
	float minScale = 0.1f;
	float maxScale = 10.0f;

	// 模型旋转（由右键拖动控制）
	glm::vec2 modelRotation = glm::vec2(0.0f); // x = 俯仰, y = 偏航，单位度
	bool firstClickModel = true;
	float modelRotSensitivity = 180.0f; // 灵敏度（度/规范化鼠标位移）

	float speed = 0.005f;
	float sensitivity = 100.0f;

	Camera(float width, float height, glm::vec3 position);
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	void Matrix(Shader& shader, const char* uniform);
	
	//键盘输入处理
	void Inputs(GLFWwindow* window);
	// 由滚轮回调调用
	void ProcessScroll(double yoffset);
	glm::vec3 GetScale();
	// 模型旋转
	glm::vec2 GetModelRotation() const { return modelRotation; }
	void ProcessModelRotation(GLFWwindow* window);
};