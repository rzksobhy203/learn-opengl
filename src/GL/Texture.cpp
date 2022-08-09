#include "Texture.h"
#include "Renderer.h"
#include "stb_image.h"
#include <stdlib.h>
#include <iostream>

Texture::Texture(const std::string &path)
	: m_FilePath(path)
{
	if (m_FilePath.find(".png") != std::string::npos)
		stbi_set_flip_vertically_on_load(1);
	else
		stbi_set_flip_vertically_on_load(0);

	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	GLCALL(glad_glGenTextures(1, &m_RendererID));
	GLCALL(glad_glBindTexture(GL_TEXTURE_2D, m_RendererID));

	GLCALL(glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCALL(glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	if (m_LocalBuffer)
	{
		GLCALL(glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	}
	else
	{
		std::cout << "[ERROR] could not load " << m_FilePath << '\n';
		exit(EXIT_FAILURE);
	}
	stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
	GLCALL(glad_glDeleteTextures(1, &m_RendererID));
}

void Texture::bind(unsigned int slot/* = 0*/) const
{
	GLCALL(glad_glActiveTexture(GL_TEXTURE0 + slot));
	GLCALL(glad_glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::unbind()
{
	GLCALL(glad_glBindTexture(GL_TEXTURE_2D, 0));
}
