#include "shader.hpp"
#include <iostream>
#include "../common/util.hpp"
#include "../common/types.hpp"

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const char* errorMessage);
static GLuint createShader(const std::string& text, GLenum shaderType);

Shader::Shader(const char* vertPath, const char* fragPath)
{
	create(vertPath, fragPath);
}

void Shader::create(const char* vertPath, const char* fragPath)
{
	id = glCreateProgram();
	GLuint vertexShader   = createShader(readFile(vertPath), GL_VERTEX_SHADER);
	GLuint fragmentShader = createShader(readFile(fragPath), GL_FRAGMENT_SHADER);
	
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);

	glLinkProgram(id);
	checkShaderError(id, GL_LINK_STATUS, true, "Error: Shader program linking failed");

	glValidateProgram(id);
	checkShaderError(id, GL_VALIDATE_STATUS, true, "Error: Shader program is invalid");

	glDetachShader(id, vertexShader);
	glDetachShader(id, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Transform uniform setup
	u_transform = getUniformLocation("transform");
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

static GLuint createShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if(!shader)
		std::cerr << "Error: Shader creation failed!\n";

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];
	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed");

	return shader;
}

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const char* errorMessage)
{
	int success;
	char error[1024];

	if(isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if(success == GL_FALSE)
	{
		if(isProgram)
			glGetProgramInfoLog(shader, 1024, nullptr, error);
		else
			glGetShaderInfoLog(shader, 1024, nullptr, error);

		std::cerr << errorMessage << ": '" << error << "'\n";
	}
}
