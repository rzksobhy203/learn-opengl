#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	GLCALL(glad_glGenVertexArrays(1, &m_RendererID));
	GLCALL(glad_glBindVertexArray(m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCALL(glad_glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::bind() const
{
	GLCALL(glad_glBindVertexArray(m_RendererID));
}

void VertexArray::unbind()
{
	GLCALL(glad_glBindVertexArray(0));
}

void VertexArray::addBuffer(const VertexBuffer &vbo, const VertexArrayLayout &layout) const
{
	bind();
	vbo.bind();

	int offset = 0;
	const auto& elements = layout.getElements();
	for (size_t i = 0; i < elements.size(); i++)
	{
		GLCALL(glad_glEnableVertexAttribArray(i));
		GLCALL(glad_glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized, layout.getStride(), (const void*)offset));

		offset += elements[i].count * VertexArrayLayoutElement::getSizeOfType(elements[i].type);
	}
}
