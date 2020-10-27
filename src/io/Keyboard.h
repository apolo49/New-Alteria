#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define KEY_Q		GLFW_KEY_Q
#define KEY_W		GLFW_KEY_W
#define KEY_E		GLFW_KEY_E
#define KEY_R		GLFW_KEY_R
#define KEY_T		GLFW_KEY_T
#define KEY_Y		GLFW_KEY_Y
#define KEY_U		GLFW_KEY_U
#define KEY_I		GLFW_KEY_I
#define KEY_O		GLFW_KEY_O
#define KEY_P		GLFW_KEY_P
#define KEY_A		GLFW_KEY_A
#define KEY_S		GLFW_KEY_S
#define KEY_D		GLFW_KEY_D
#define KEY_F		GLFW_KEY_F
#define KEY_G		GLFW_KEY_G
#define KEY_H		GLFW_KEY_H
#define KEY_J		GLFW_KEY_J
#define KEY_K		GLFW_KEY_K
#define KEY_L		GLFW_KEY_L
#define KEY_Z		GLFW_KEY_Z
#define KEY_X		GLFW_KEY_X
#define KEY_C		GLFW_KEY_C
#define KEY_V		GLFW_KEY_V
#define KEY_B		GLFW_KEY_B
#define KEY_N		GLFW_KEY_N
#define KEY_M		GLFW_KEY_M
#define KEY_ESC		GLFW_KEY_ESCAPE
#define KEY_UP		GLFW_KEY_UP
#define KEY_DOWN	GLFW_KEY_DOWN
#define KEY_LEFT	GLFW_KEY_LEFT
#define KEY_RIGHT	GLFW_KEY_RIGHT
#define KEY_SPACE	GLFW_KEY_SPACE
#define KEY_LSHIFT	GLFW_KEY_LEFT_SHIFT
#define KEY_RSHIFT	GLFW_KEY_RIGHT_SHIFT

class Keyboard
{
public:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static bool key(int key);
	static bool keyChanged(int key);
	static bool keyWentUp(int key);
	static bool keyWentDown(int key);

private:
	static bool keys[];
	static bool keysChanged[];
};
#endif
