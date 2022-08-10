#include "Shader.h"
#include "Renderer.h"
#include <alloca.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>

std::tuple<std::string, std::string> Shader::parseShader() const
{
	std::ifstream stream(m_FilePath);
	std::stringstream ss[2];

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1,
	};

	std::string line;
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::compileShader(unsigned int type, const std::string &source) const
{
	GLCALL(unsigned int id = glad_glCreateShader(type));
	const char *src = source.c_str();

	GLCALL(glad_glShaderSource(id, 1, &src, nullptr));
	GLCALL(glad_glCompileShader(id));

	int result;
	GLCALL(glad_glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result != GL_TRUE)
	{
		int length;
		GLCALL(glad_glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

		char *message = (char*)alloca(length);
		GLCALL(glad_glGetShaderInfoLog(id, length, &length, nullptr));

		std::cout << "[ERROR] OpenGL could not compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader\n";
		std::cout << message << '\n';
		exit(EXIT_FAILURE);
	}

	return id;
}

Shader::Shader(const std::string &file_path)
	: m_FilePath(file_path)
{
	GLCALL(m_RendererID = glad_glCreateProgram());
	auto [VertexShader, FragmentShader] = parseShader();

	unsigned int vs = compileShader(GL_VERTEX_SHADER, VertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, FragmentShader);

	GLCALL(glad_glAttachShader(m_RendererID, vs));
	GLCALL(glad_glAttachShader(m_RendererID, fs));
	GLCALL(glad_glLinkProgram(m_RendererID));

	int result;
	GLCALL(glad_glGetProgramiv(m_RendererID, GL_LINK_STATUS, &result));
	if (result != GL_TRUE)
	{
		int length;
		GLCALL(glad_glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &length));

		char *message = (char*)alloca(length);
		GLCALL(glad_glGetProgramInfoLog(m_RendererID, length, &length, message));

		std::cout << "[ERROR] could not link program\n";
		std::cout << message;
		exit(EXIT_FAILURE);
	}

	glad_glValidateProgram(m_RendererID);
	GLCALL(glad_glGetProgramiv(m_RendererID, GL_VALIDATE_STATUS, &result));
	if (result != GL_TRUE)
	{
		int length;
		GLCALL(glad_glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &length));

		char *message = (char*)alloca(length);
		GLCALL(glad_glGetProgramInfoLog(m_RendererID, length, &length, message));

		std::cout << "[ERROR] could not validate program\n";
		std::cout << message;
		exit(EXIT_FAILURE);
	}
}

Shader::~Shader()
{
	GLCALL(glad_glDeleteProgram(m_RendererID));
}

void Shader::bind() const
{
	GLCALL(glad_glUseProgram(m_RendererID));
}

void Shader::unbind()
{
	GLCALL(glad_glUseProgram(0));
}

int Shader::GetUniformLocation(const std::string& name)
{
    GLCALL(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "No active uniform variable with name " << name << " found" << std::endl;
    return location;
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    GLCALL(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
{
    GLCALL(glUniform4f(GetUniformLocation(name), f0, f1, f2, f3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4 &matrix)
{
	GLCALL(glad_glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}
