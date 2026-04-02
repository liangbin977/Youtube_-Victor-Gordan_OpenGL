#include"Model.h"


const unsigned int width = 2056;
const unsigned int height = 1028;


int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenG L4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Take care of all the light related things
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);



	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
	// Specifies the Depth Test to compare the new depth value with the existing depth value in the Depth Buffer
	glDepthFunc(GL_LESS);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));


	// Load in a model
	Model tree("models/trees/scene.gltf");
	Model ground("models/ground/scene.gltf");


	float modelYaw = 0.0f;
	float modelPitch = 0.0f;
	bool draggingModel = false;
	double lastMouseX = 0.0;
	double lastMouseY = 0.0;
	const float modelRotateSpeed = 0.2f;



	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.85f, 0.85f, 0.90f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);


		// 左键拖动旋转模型
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			double mouseX = 0.0;
			double mouseY = 0.0;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			if (!draggingModel)
			{
				draggingModel = true;
				lastMouseX = mouseX;
				lastMouseY = mouseY;
			}
			else
			{
				double deltaX = mouseX - lastMouseX;
				double deltaY = mouseY - lastMouseY;

				modelYaw += static_cast<float>(deltaX) * modelRotateSpeed;
				modelPitch += static_cast<float>(deltaY) * modelRotateSpeed;

				lastMouseX = mouseX;
				lastMouseY = mouseY;
			}
		}
		else
		{
			draggingModel = false;
		}

		glm::mat4 userModel = glm::mat4(1.0f);
		userModel = glm::rotate(userModel, glm::radians(modelYaw), glm::vec3(0.0f, 1.0f, 0.0f));
		userModel = glm::rotate(userModel, glm::radians(modelPitch), glm::vec3(1.0f, 0.0f, 0.0f));

		tree.Draw(shaderProgram, camera, userModel);
		ground.Draw(shaderProgram, camera, userModel);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Delete all the objects we've created
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}