#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <fstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "shader.h"
#include "VertexArray.h"


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}


	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		log("FUCK");
	}


	float vertexData[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f
	};


	unsigned int indexData[] = {
		0,1,2,
		2,3,0
	};

	VertexArray va;
	VertexBuffer vb(vertexData, sizeof(float) * 5 * 4);
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(3);
	va.AddBuffer(vb, layout);
	IndexBuffer ib(indexData, 6);




	Shader shader("res/vertexShader.glsl", "res/fragmentShader.glsl");

	va.unBind();
	vb.unBind();
	ib.unBind();


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		shader.Bind();
		//va.Bind();
		ib.Bind();

		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}