#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using string = std::string;

class Shader
{
public:
	unsigned int id;

	//Default
	Shader();

	//With paths to shaders
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

	// generate using vertex and frag shaders
	void generate(const char* vertexShaderPath, const char* fragShaderPath);

	void activate();

	//uniform
	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void set3Float(const std::string& name, float v1, float v2, float v3);
	void set3Float(const std::string& name, glm::vec3 v);
	void set4Float(const std::string& name, float v1, float v2, float v3, float v4);
	//void set4Float(const std::string& name, aiColor4D color);
	void set4Float(const std::string& name, glm::vec4 v);
	void setMat4(const std::string& name, glm::mat4 val);

	//utility
	string loadShaderSrc(const char* filePath);
	GLuint compileShader(const char* filePath, GLuint type);
	void errorCheck(unsigned int Shader);
};
#endif
