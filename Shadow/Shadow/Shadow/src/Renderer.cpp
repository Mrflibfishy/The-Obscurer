
#include "Renderer.h"
#include <iostream>

void log(const char* text) {
	std::cout << text << std::endl;
}

void GLClearError() {
	while (glGetError());
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "Opengl Error: " << error << ", " << function << " " << file << ": " << line << std::endl;
		return false;
	}
	return true;
}