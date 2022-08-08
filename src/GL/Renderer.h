#pragma once

#include <glad/glad.h>

#define GLCALL(x) x;\
	GLLogERR(#x, __FILE__, __LINE__)

void GLLogERR(const char *function, const char *file, int line);

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
private:
public:
	void clear(GLclampf red, GLclampf green, GLclampf blue) const;
	void draw(const VertexArray &vao, const IndexBuffer &ibo, const Shader &shader) const;
};
