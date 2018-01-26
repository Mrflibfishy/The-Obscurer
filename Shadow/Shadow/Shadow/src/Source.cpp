#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void log(const char* text)  {
	std::cout << text << std::endl;
}

static void GLClearError() {
	while (glGetError());
}

static bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "Opengl Error: " << error << ", " << function << " " << file << ": " << line << std::endl;
		return false;
	}
	return true;
}


GLenum logerrors(GLenum text) {
	std::cout << text << std::endl;
	return text;
}

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




	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		float data[] = {
			 0.5f, -0.5f,
			-0.5f, -0.5f,
			 0.0f,  0.5f
		};
		
		GLuint vertex_buffer; // Save this for later rendering
		GLCall(glGenBuffers(1, &vertex_buffer));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 3, 0, GL_STATIC_DRAW));
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 2 * 3, data));
		
		GLCall()

		GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
			
	


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}