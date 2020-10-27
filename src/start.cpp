#pragma once
#include "start.h"

Camera Camera::defaultCamera(glm::vec3(0.0f, 0.0f, 3.0f));
double deltaTime = 0.0f; // tme btwn frames
double lastFrame = 0.0f; // time of last frame

Screen screen;
float mixVal;

int Start::main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	if (!screen.init()) {
		std::cout << "Could not open window" << std::endl;
		glfwTerminate();
		return -1;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "GLAD not initisialised";
		glfwTerminate();
		return -1;
	}

	screen.setParameters();
	Shader shader("assets/object.vert", "assets/object.frag");

	if (mainLoop(shader)) {
		glfwTerminate();
		return -1;
	}

	glfwTerminate();
	return 0;
}

int Start::mainLoop(Shader shader) {
	//glm::mat4 trans = glm::mat4(1.0);
	Cube cube(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.75f));
	cube.init();
	while (!screen.shouldClose()) {
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		processInput(deltaTime);

		//render
		screen.update();

		//draw shapes
		shader.activate();

		shader.setFloat("mixVal", mixVal);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Create transformation matrix
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = Camera::defaultCamera.getViewMatrix();
		projection = glm::perspective(
			glm::radians(Camera::defaultCamera.zoom),
			(float)Screen::SCR_WIDTH / (float)Screen::SCR_HEIGHT, 0.1f, 100.0f);

		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		cube.render(shader);

		//send new frame
		screen.newFrame();
		glfwPollEvents();
	}
	return 0;
}

void Start::processInput(double deltaTime) {
	if (Keyboard::key(KEY_ESC)) {
		screen.setShouldClose(true);
	}

	// change mix value
	if (Keyboard::key(KEY_UP)) {
		mixVal += .05f;
		if (mixVal > 1) {
			mixVal = 1.0f;
		}
	}
	if (Keyboard::key(KEY_DOWN)) {
		mixVal -= .05f;
		if (mixVal < 0) {
			mixVal = 0.0f;
		}
	}

	// move camera
	if (Keyboard::key(KEY_W)) {
		Camera::defaultCamera.updateCameraPos(CameraDirection::FORWARD, deltaTime);
	}
	if (Keyboard::key(KEY_S)) {
		Camera::defaultCamera.updateCameraPos(CameraDirection::BACKWARD, deltaTime);
	}
	if (Keyboard::key(KEY_D)) {
		Camera::defaultCamera.updateCameraPos(CameraDirection::RIGHT, deltaTime);
	}
	if (Keyboard::key(KEY_A)) {
		Camera::defaultCamera.updateCameraPos(CameraDirection::LEFT, deltaTime);
	}
	if (Keyboard::key(KEY_SPACE)) {
		Camera::defaultCamera.updateCameraPos(CameraDirection::UP, deltaTime);
	}
	if (Keyboard::key(KEY_LSHIFT) || Keyboard::key(KEY_RSHIFT)) {
		Camera::defaultCamera.updateCameraPos(CameraDirection::DOWN, deltaTime);
	}
}