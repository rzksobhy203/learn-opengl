#pragma once

#include <vector>
#include <stdlib.h>
#include <stdio.h>

#include <glad/glad.h>

struct VertexArrayLayoutElement
{
	unsigned int count;
	unsigned int type;
	unsigned int normalized;

	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:         return 4;
		case GL_UNSIGNED_INT:  return 4;
		case GL_UNSIGNED_BYTE: return 4;
		}

		printf("[ERROR] unhandled type\n");
		exit(EXIT_FAILURE);
	}
};

class VertexArrayLayout
{
private:
	std::vector<VertexArrayLayoutElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexArrayLayout();
	
	template<typename T>
	void push(unsigned int count)
	{
		(void) count;

		printf("[ERROR] unhandled type\n");
		exit(EXIT_FAILURE);
	}

	inline std::vector<VertexArrayLayoutElement> getElements() const { return m_Elements; }
	inline unsigned int getStride() const { return m_Stride; }
};
