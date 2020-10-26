#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using string = std::string;

class Shader
{
public:
	unsigned int id;

	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

	void activate();

	//uniform
	void setBool(const string& name, bool value);
	void setInt(const string& name, int value);
	void setFloat(const string& name, float value);
	void set4Float(const string& name, float v1, float v2, float v3, float v4);
	void setMat4(const std::string& name, glm::mat4 val);

	//utility
	string loadShaderSrc(const char* filePath);
	GLuint compileShader(const char* filePath, GLuint type);
	void errorCheck(unsigned int Shader);
};
#endif
