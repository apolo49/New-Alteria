#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "graphics/shader.h"
#include "graphics/texture.h"
#include "graphics/model.h"

#include "graphics/models/cube.hpp"

#include "io/keyboard.h"
#include "io/mouse.h"
#include "io/screen.h"
#include "io/camera.h"

using string = std::string;

class Start
{
public:
	static int main();

private:
	static void frameBuffer_SizeCallback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }
	static int mainLoop(Shader shader);
	static void processInput(double deltaTime);
};
