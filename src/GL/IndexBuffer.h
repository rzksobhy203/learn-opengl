#pragma once

class IndexBuffer
{
private:
	unsigned int m_Count;
	unsigned int m_RendererID;
public:
	IndexBuffer(const unsigned int *data, unsigned int count);
	~IndexBuffer();

	void bind() const;
	static void unbind();

	inline unsigned int getCount() const { return m_Count; }
};
