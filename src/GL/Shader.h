#pragma once

#include <tuple>
#include <string>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
public:
	Shader(const std::string &file_path);
	~Shader();

	void bind() const;
	static void unbind();

	int GetUniformLocation(const std::string &name);
	void SetUniform1f(const std::string &name, float value);
	void SetUniform4f(const std::string &name, float f0, float f1, float f2, float f3);
	void SetUniformMat4f(const std::string &name, const glm::mat4 &matrix);
private:
	std::tuple<std::string, std::string> parseShader() const;
	unsigned int compileShader(unsigned int type, const std::string &source) const;
};
