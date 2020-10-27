#ifndef SCREEN_H
#define SCREEN_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "mouse.h"
#include "Keyboard.h"

class Screen {
public:
	static unsigned int SCR_WIDTH, SCR_HEIGHT;

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	Screen();

	int init();

	void setParameters();

	// main loop
	void update();
	void newFrame();

	// window closing
	bool shouldClose();
	void setShouldClose(bool shouldClose);

private:
	GLFWwindow* window;
};

#endif
