#pragma once
#include "start.h"

int Start::main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	GLFWwindow* window = glfwCreateWindow(800, 600, "Alteria", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "GLAD not initisialised";
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, frameBuffer_SizeCallback);

	if (mainLoop(window, Shader("assets/vertex_core.glsl", "assets/fragment_core.glsl"), LoadVAO()))
		return 1;

	return 0;
}

int Start::mainLoop(GLFWwindow* window, Shader shader, unsigned int VAO) {
	glm::mat4 trans = glm::mat4(1.0);
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		//render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		trans = glm::rotate(trans, glm::radians(((float)glfwGetTime() / 100)), glm::vec3(1.0f, 1.0f, 1.0f));
		//draw shapes
		glBindVertexArray(VAO);
		shader.activate();
		shader.setMat4("transform", trans);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//send new frame
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}

void Start::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

unsigned int Start::LoadVAO() {
	float vertices[] = {
		0.5f, 0.5f, 0.0f, //top right
		-0.5f, 0.5f, 0.0f, //top left
		-0.5f, -0.5f, 0.0f, //bottom left
		0.5f, -0.5f, 0.0f //bottom right
	};

	int indices[]{
		0,1,2,
		2,3,0
	};

	//VAO,VBO
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//bind VAO
	glBindVertexArray(VAO);

	//bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//set attrib pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	return VAO;
}