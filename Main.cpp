#define GLM_ENABLE_EXPERIMENTAL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include <stb/stb_image.h>
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"	

// 全局滚轮回调函数（非捕获 lambda）
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(window)); //Retrieve the camera pointer from the window's user pointer
	if (cam) cam->ProcessScroll(yoffset);
}

int main() {
	/* glfw开头的是GLFW的API,gl开头的是GLAD的API */

	glfwInit(); 	// Initialize GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 800, "Bin", nullptr, nullptr);
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Make the window's context current);
	gladLoadGL(); // Load OpenGL function pointers using GLAD
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // Load OpenGL function pointers using GLAD

	float width = 2056.0f;
	float height = 1028.0f;

	glViewport(0, 0, 2056, 1028);// Set the viewport to cover the entire window

	// Vertices coordinates
	GLfloat vertices[] =
	{
		//    COORDINATES                 COLORS                  TexCoord           Normal
			-0.5f,  0.0f,  0.5f,    0.83f, 0.70f, 0.44f,    0.0f,  0.0f,    0.0f, -1.0f, 0.0f,  // Bottom side
			-0.5f,  0.0f, -0.5f,    0.83f, 0.70f, 0.44f,    0.0f,  5.0f,    0.0f, -1.0f, 0.0f,  // Bottom side
			 0.5f,  0.0f, -0.5f,    0.83f, 0.70f, 0.44f,    5.0f,  5.0f,    0.0f, -1.0f, 0.0f,  // Bottom side
			 0.5f,  0.0f,  0.5f,    0.83f, 0.70f, 0.44f,    5.0f,  0.0f,    0.0f, -1.0f, 0.0f,   // Bottom side

			-0.5f,  0.0f,  0.5f,    0.83f, 0.70f, 0.44f,    0.0f,  0.0f,    -0.8f,  0.5f, 0.0f,   // Left Side
			-0.5f,  0.0f, -0.5f,    0.83f, 0.70f, 0.44f,    5.0f,  0.0f,    -0.8f,  0.5f, 0.0f,   // Left Side
			 0.0f,  0.8f,  0.0f,    0.92f, 0.86f, 0.76f,    2.5f,  5.0f,    -0.8f,  0.5f, 0.0f,   // Left Side

			-0.5f,  0.0f, -0.5f,    0.83f, 0.70f, 0.44f,    5.0f,  0.0f,     0.0f,  0.5f, -0.8f,  // Non-facing side
			 0.5f,  0.0f, -0.5f,    0.83f, 0.70f, 0.44f,    0.0f,  0.0f,     0.0f,  0.5f, -0.8f,  // Non-facing side
			 0.0f,  0.8f,  0.0f,    0.92f, 0.86f, 0.76f,    2.5f,  5.0f,     0.0f,  0.5f, -0.8f,   // Non-facing side

			 0.5f,  0.0f, -0.5f,    0.83f, 0.70f, 0.44f,    0.0f,  0.0f,     0.8f,  0.5f, 0.0f,   // Right side
			 0.5f,  0.0f,  0.5f,    0.83f, 0.70f, 0.44f,    5.0f,  0.0f,     0.8f,  0.5f, 0.0f,   // Right side
			 0.0f,  0.8f,  0.0f,    0.92f, 0.86f, 0.76f,    2.5f,  5.0f,     0.8f,  0.5f, 0.0f,   // Right side

			 0.5f,  0.0f,  0.5f,    0.83f, 0.70f, 0.44f,    5.0f,  0.0f,     0.0f,  0.5f, 0.8f,   // Facing side
			-0.5f,  0.0f,  0.5f,    0.83f, 0.70f, 0.44f,    0.0f,  0.0f,     0.0f,  0.5f, 0.8f, // Facing side
			 0.0f,  0.8f,  0.0f,    0.92f, 0.86f, 0.76f,    2.5f,  5.0f,     0.0f,  0.5f, 0.8f   // Facing side
	};

	// Indices for vertices order

	GLuint indices[] =
	{
		0, 1, 2,     // Bottom side
		0, 2, 3,     // Bottom side
		4, 6, 5,     // Left side
		7, 9, 8,     // Non-facing side
		10, 12, 11,  // Right side
		13, 15, 14   //
	};


	GLfloat lightVertices[] =
	{
		//      COORDINATES      //
		-0.1f, -0.1f,  0.1f,
		-0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f,  0.1f
	};


	GLuint lightIndices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};

	Shader shaderProgram("default.vert", "default.frag");
	VAO vao;
	vao.Bind();

	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	vao.LinkAttrib(vbo, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	vao.unBind();
	vbo.unBind();
	ebo.unBind();

	Shader lightShader("light.vert", "light.frag");
	VAO lightVAO;
	lightVAO.Bind();
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	
	lightVAO.unBind();
	lightEBO.unBind();
	lightVBO.unBind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // Set the light color to white (1.0f, 1.0f, 1.0f, 1.0f)

	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f); // Set the light position in world space
	glm::mat4 lightModel = glm::mat4(1.0f); 
	lightModel = glm::translate(lightModel, lightPos); // Translate the light's model matrix to the light's position

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f); // Set the pyramid's position in world space
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos); // Translate the pyramid's model matrix to the pyramid's position (in this case, it's at the origin so it won't actually move)

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	Texture tex("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	tex.texSlotSetting(shaderProgram, "texSlot", 0); // Set the value of the "texSlot" uniform variable in the shader program to 0 (the texture unit GL_TEXTURE0)

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	// 把 camera 指针关联到GLFW自动维护的 window 的 user pointer（void*） 中，供回调使用
	glfwSetWindowUserPointer(window, &camera);
	// 设置全局滚轮回调函数，GLFW会在滚轮事件发生时调用该函数，并传递相应的参数
	glfwSetScrollCallback(window, scroll_callback);

	glEnable(GL_DEPTH_TEST); // Enable depth testing to ensure correct rendering of 3D objects based on their depth values

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		camera.Inputs(window);
		camera.ProcessModelRotation(window);

		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		shaderProgram.Activate();
		camera.Matrix(shaderProgram, "cameraMatrix");

		// 使用 camera.scale 构建 model 矩阵用于放大/缩小模型（如果着色器中没有 model uniform，OpenGL 将忽略该 uniform）
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(camera.GetScale()));
		// 使用 camera.modelRotation 构建 model 矩阵用于旋转模型（如果着色器中没有 model uniform，OpenGL 将忽略该 uniform）
		glm::vec2 rot = camera.GetModelRotation();
		model = glm::rotate(model, glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f)); // pitch
		model = glm::rotate(model, glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f)); // yaw
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

		tex.Bind(); // if don't insert the texture into the slot, the shader will use the default white texture in slot 0
		vao.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		lightShader.Activate();
		camera.Matrix(lightShader, "cameraMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window); // Swap the front and back buffers to display the cleared color);
		glfwPollEvents();
	}
	
	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	tex.Delete();
	glfwDestroyWindow(window);	//destroy the window
	glfwTerminate();//regard to the glfwInit
	return 0;
} 