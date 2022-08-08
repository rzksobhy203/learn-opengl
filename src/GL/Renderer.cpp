#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "Renderer.h"

void GLLogERR(const char *function, const char *file, int line)
{
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		fprintf(stderr, "[ERROR] OpenGL 0x%04x at %s in %s:%i\n", err, function, file, line);
		exit(EXIT_FAILURE);
	}
}

void Renderer::clear(GLclampf red, GLclampf green, GLclampf blue) const
{
	GLCALL(glad_glClearColor(red, green, blue, 1.0f));
	GLCALL(glad_glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::draw(const VertexArray &vao, const IndexBuffer &ibo, const Shader &shader) const
{
	vao.bind();
	ibo.bind();
	shader.bind();

	GLCALL(glad_glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr));
}
