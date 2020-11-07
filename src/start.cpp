#pragma once
#include "start.h"

Camera Camera::defaultCamera(glm::vec3(0.0f, 0.0f, 3.0f));
double deltaTime = 0.0f; // tme btwn frames
double lastFrame = 0.0f; // time of last frame

Screen screen;
float mixVal;

/*
*
* Function to start the program, initialises OpenGL, GLFW and GLAD as well
* as sets the OpenGL version and calls the shaders to be created.
*
*/
int Start::main()
{
	//Initialise GLFW and OpenGL
	glfwInit();

	//Tell GLFW to use OpenGL 3.3 and if the architecture is an Apple allow forward compatibility
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	//If the screen could not initialise report, terminate GLFW and OpenGL and return failure
	if (!screen.init()) {
		std::cout << "Could not open window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//If the GLAD wrapper for OpenGL could not initialise, terminate GLFW and OpenGL and return failure
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "GLAD not initisialised";
		glfwTerminate();
		return -1;
	}

	screen.setParameters();
	Shader shader("assets/object.vert", "assets/object.frag");

	//Open Main Loop and send shader to the window. If a failure terminate GLFW and OpenGL and return failure for safe shutdown
	if (mainLoop(shader)) {
		glfwTerminate();
		return -1;
	}

	//If all ends correctly terminate GLFW and OpenGL and return safe execution
	glfwTerminate();
	return 0;
}

/*
*
* The main loop for the program. Creates objects and processes them sequentially.
* Planning to be syncronous for more streamlined and performant loop.
* First sets delta time, Then processes inputs.
* Then updates the screen and activates the shaders
* Draws arrays of triangles and creates the view and projection matrices.
* Then renders the screen and sends a new frame.
*
*/

int Start::mainLoop(Shader shader) {
	//glm::mat4 trans = glm::mat4(1.0);
	Cube cube(Material::emerald, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.75f));
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