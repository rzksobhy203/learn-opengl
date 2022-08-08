#include "Renderer.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count)
	: m_Count(count)
{
	GLCALL(glad_glGenBuffers(1, &m_RendererID));
	GLCALL(glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCALL(glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLCALL(glad_glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::bind() const
{
	GLCALL(glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::unbind()
{
	GLCALL(glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
