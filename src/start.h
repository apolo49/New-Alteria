#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"

using string = std::string;

class Start
{
public:
	static int main();
private:
	static void frameBuffer_SizeCallback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }
	static int mainLoop(GLFWwindow* window, Shader shader, unsigned int VAO);
	static void processInput(GLFWwindow* window);
	static unsigned int LoadVAO();
};
