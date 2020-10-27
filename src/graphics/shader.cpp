#include "Shader.h"

Shader::Shader() {}

void Shader::generate(const char* vertexShaderPath, const char* fragShaderPath) {
	int success;
	char infoLog[512];

	// compile shaders
	GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
	GLuint fragShader = compileShader(fragShaderPath, GL_FRAGMENT_SHADER);

	// create program and attach shaders
	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragShader);
	glLinkProgram(id);

	// linking errors
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "Linking error:" << std::endl << infoLog << std::endl;
	}

	// delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	generate(vertexShaderPath, fragmentShaderPath);
}

void Shader::activate()
{
	glUseProgram(id);
}

string Shader::loadShaderSrc(const char* filePath)
{
	std::ifstream file;
	std::stringstream buf;

	string ret = "";

	file.open(filePath);

	if (file.is_open()) {
		buf << file.rdbuf();
		ret = buf.str();
	}
	else {
		std::cout << "Could not open " << filePath << std::endl;
	}

	file.close();
	return ret;
}

GLuint Shader::compileShader(const char* filePath, GLuint type)
{
	GLuint Shader = glCreateShader(type);
	string ShaderSrc = loadShaderSrc(filePath);
	const GLchar* ShaderTxt = ShaderSrc.c_str();
	glShaderSource(Shader, 1, &ShaderTxt, NULL);
	glCompileShader(Shader);
	errorCheck(Shader);
	return Shader;
}

void Shader::errorCheck(unsigned int Shader)
{
	char infoLog[255];
	int success;
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(Shader, 512, NULL, infoLog);
		std::cout << "Error with shader compilation:" << std::endl << infoLog << std::endl;
	}
}

/*
* Uniform variables
*/
void Shader::setBool(const string& name, bool value)
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const string& name, int value)
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const string& name, float value)
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::set3Float(const std::string& name, float v1, float v2, float v3) {
	glUniform3f(glGetUniformLocation(id, name.c_str()), v1, v2, v3);
}

void Shader::set3Float(const std::string& name, glm::vec3 v) {
	glUniform3f(glGetUniformLocation(id, name.c_str()), v.x, v.y, v.z);
}

void Shader::set4Float(const std::string& name, float v1, float v2, float v3, float v4) {
	glUniform4f(glGetUniformLocation(id, name.c_str()), v1, v2, v3, v4);
}

/*
void Shader::set4Float(const std::string& name, aiColor4D color) {
	glUniform4f(glGetUniformLocation(id, name.c_str()), color.r, color.g, color.b, color.a);
}
*/

void Shader::set4Float(const std::string& name, glm::vec4 v) {
	glUniform4f(glGetUniformLocation(id, name.c_str()), v.x, v.y, v.z, v.w);
}

void Shader::setMat4(const std::string& name, glm::mat4 val)
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}