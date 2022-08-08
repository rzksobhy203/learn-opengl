#include "VertexArrayLayout.h"

VertexArrayLayout::VertexArrayLayout()
	: m_Stride(0)
{}

template<>
void VertexArrayLayout::push<float>(unsigned int count)
{
	m_Elements.push_back({ count, GL_FLOAT, GL_FALSE });
	m_Stride += count * VertexArrayLayoutElement::getSizeOfType(GL_FLOAT);
}

template<>
void VertexArrayLayout::push<unsigned int>(unsigned int count)
{
	m_Elements.push_back({ count, GL_UNSIGNED_INT, GL_TRUE });
	m_Stride += count * VertexArrayLayoutElement::getSizeOfType(GL_UNSIGNED_INT);
}

template<>
void VertexArrayLayout::push<unsigned char>(unsigned int count)
{
	m_Elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });
	m_Stride += count * VertexArrayLayoutElement::getSizeOfType(GL_UNSIGNED_BYTE);
}
