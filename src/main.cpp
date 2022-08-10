#include <cstdio>
#include <iostream>
#include <tuple>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "GL/IndexBuffer.h"
#include "GL/Renderer.h"
#include "GL/VertexArray.h"
#include "GL/VertexArrayLayout.h"
#include "GL/VertexBuffer.h"
#include "ext/matrix_clip_space.hpp"

#define INIT_WIDTH  800
#define INIT_HEIGHT 600

std::tuple<double, double> getRatio(int numerator, int dominator)
{
	double ratio = (double)numerator / dominator;
	double reminder = numerator % dominator;

	return { ratio * (dominator / reminder), dominator / reminder };
}

int main(void)
{
	if (!glfwInit())
	{
		fprintf(stderr, "[ERROR] could not intialize GLFW\n");
        return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(INIT_WIDTH, INIT_HEIGHT, "C++ - OpenGL", NULL, NULL);
	if (window == nullptr)
	{
		fprintf(stderr, "[ERROR] could create GLFW window\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	auto [numerator, dominator] = getRatio(INIT_WIDTH, INIT_HEIGHT);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		fprintf(stderr, "[ERROR] could not initialize GLAD\n");
		glfwTerminate();
		return -1;
	}

	std::cout << glad_glGetString(GL_VERSION) << '\n';

	{
		Renderer renderer;
		VertexArray vao;

		float verticies[] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f,
		};

		VertexBuffer vbo(verticies, sizeof(verticies));

		VertexArrayLayout layout;
		layout.push<float>(2);

		unsigned int indecies[] = {
			0, 1, 2,
			0, 2, 3,
		};

		IndexBuffer ibo(indecies, 6);

		glm::mat4 proj = glm::ortho(-1 * numerator / 2, numerator / 2, -1 * dominator / 2, dominator / 2);

		Shader shader("res/shader.glsl");
		shader.bind();
		shader.SetUniformMat4f("u_MVP", proj);

		VertexArray::unbind();
		VertexBuffer::unbind();
		IndexBuffer::unbind();
		Shader::unbind();

		while (!glfwWindowShouldClose(window))
		{
			renderer.clear(0, 0, 0);

			vbo.bind();
			vao.addBuffer(vbo, layout);
			renderer.draw(vao, ibo, shader);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	glfwTerminate();
	return 0;
}
