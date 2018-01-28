#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <fstream>

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

std::string readShaderCode(const char* fileName) {
	std::ifstream meinput(fileName);
	if (!meinput.good()) {
		std::cout << "File failed to load..." << fileName;
		ASSERT(0);
	}
	return std::string(
		std::istreambuf_iterator<char>(meinput),
		std::istreambuf_iterator<char>());
}


GLenum logerrors(GLenum text) {
	std::cout << text << std::endl;
	return text;
}

bool checkStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType) {
	GLint  status;
	objectPropertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE) {
		GLint infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		std::cout << buffer << std::endl;
		delete[] buffer;
		return false;
	}
	return true;
}

bool checkShaderStatus(GLuint shaderID) {
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
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

		unsigned int vao;
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));

		GLuint vertex_buffer; // Save this for later rendering
		GLCall(glGenBuffers(1, &vertex_buffer));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 5 * 4, vertexData, GL_STATIC_DRAW));

		GLuint indexBuffer; // Save this for later rendering
		GLCall(glGenBuffers(1, &indexBuffer));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer))
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indexData, GL_STATIC_DRAW));


		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0));


		GLCall(glEnableVertexAttribArray(1));
		GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 2)));


		GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		const char* adapter[1];
		std::string temp = readShaderCode("res/vertexShader.glsl");
		adapter[0] = temp.c_str();
		GLCall(glShaderSource(vertexShaderID, 1, adapter, 0));

		temp = readShaderCode("res/fragmentShader.glsl");
		adapter[0] = temp.c_str();
		GLCall(glShaderSource(fragmentShaderID, 1, adapter, 0));

		GLCall(glCompileShader(vertexShaderID));
		GLCall(glCompileShader(fragmentShaderID));


		if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID)) {
			ASSERT(0);
		}


		GLuint programID = glCreateProgram();


		glBindAttribLocation(programID, 0, std::string("vertexPos").c_str());
		glBindAttribLocation(programID, 1, std::string("vertexColor").c_str());

		GLCall(glActiveTexture(GL_TEXTURE0));
		GLCall(glAttachShader(programID, vertexShaderID));
		GLCall(glAttachShader(programID, fragmentShaderID));
		GLCall(glLinkProgram(programID));

		GLCall(glUseProgram(programID));


		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

		


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}