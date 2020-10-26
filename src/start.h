#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Start
{
public:
	static int main();
private:
	static void frameBuffer_SizeCallback(GLFWwindow* window, int width, int height);
	static int mainLoop(GLFWwindow* window);
	static void processInput(GLFWwindow* window);
};
