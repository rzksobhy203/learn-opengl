#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void *data, const unsigned int size);
	~VertexBuffer();

	void bind() const;
	static void unbind();
};
