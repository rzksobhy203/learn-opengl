#pragma once

#include "VertexBuffer.h"
#include "VertexArrayLayout.h"

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	static void unbind();

	void addBuffer(const VertexBuffer &vbo, const VertexArrayLayout &layout) const;
};
