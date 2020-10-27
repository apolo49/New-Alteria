#ifndef MOUSE_H
#define MOUSE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Camera.h"

#define LEFT_CLICK			GLFW_MOUSE_BUTTON_LEFT
#define RIGHT_CLICK			GLFW_MOUSE_BUTTON_RIGHT
#define MID_CLICK			GLFW_MOUSE_BUTTON_MIDDLE
#define CURSOR				GLFW_CURSOR
#define CURSOR_DISABLED		GLFW_CURSOR_DISABLED

class Mouse
{
public:
	static void cursorPosCallback(GLFWwindow* window, double _x, double _y);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void mouseWheelCallback(GLFWwindow* window, double dx, double dy);

	static double getMouseX();
	static double getMouseY();

	static double getDX();
	static double getDY();

	static bool button(int button);
	static bool buttonChanged(int button);
	static bool buttonWentUp(int button);
	static bool buttonWentDown(int button);

private:
	static double x;
	static double y;

	static double lastX;
	static double lastY;

	static double dx;
	static double dy;

	static bool firstMouse;

	static bool buttons[];
	static bool buttonsChanged[];
};

#endif
