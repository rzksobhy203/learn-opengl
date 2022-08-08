#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void *data, const unsigned int size)
{
	GLCALL(glad_glGenBuffers(1, &m_RendererID));
	GLCALL(glad_glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCALL(glad_glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCALL(glad_glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::bind() const
{
	GLCALL(glad_glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::unbind()
{
	GLCALL(glad_glBindBuffer(GL_ARRAY_BUFFER, 0));
}
