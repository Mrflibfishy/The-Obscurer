#include "Shader.h"
#include <fstream>
#include <iostream>



Shader::Shader(const char* filepathVS, const char* filepathFS)
	:m_RendererID(0)
{
	m_FilePath.Set(filepathVS, filepathFS);
	m_RendererID = CreateShader(m_FilePath.VertexSource, m_FilePath.FragmentSource);
}

Shader::~Shader() {
	GLCall(glDeleteProgram(m_RendererID));
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


bool Shader::checkStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType) {
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

bool Shader::checkShaderStatus(GLuint shaderID) {
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

unsigned int Shader::CreateShader(const char* vetexSource, const char* fragmentSource){
	GLuint programID = glCreateProgram();
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const char* adapter[1];
	std::string temp = readShaderCode(vetexSource);
	adapter[0] = temp.c_str();
	GLCall(glShaderSource(vertexShaderID, 1, adapter, 0));

	temp = readShaderCode(fragmentSource);
	adapter[0] = temp.c_str();
	GLCall(glShaderSource(fragmentShaderID, 1, adapter, 0));

	GLCall(glCompileShader(vertexShaderID));
	GLCall(glCompileShader(fragmentShaderID));


	if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID)) {
		ASSERT(0);
	}


	GLCall(glAttachShader(programID, vertexShaderID));
	GLCall(glAttachShader(programID, fragmentShaderID));
	GLCall(glLinkProgram(programID));

	GLCall(glDeleteShader(vertexShaderID));
	GLCall(glDeleteShader(fragmentShaderID));

	return programID;
}

void Shader::Bind() {
	GLCall(glUseProgram(m_RendererID));
}

void Shader::unBind() {
	GLCall(glUseProgram(0));
}

int Shader::GetUniformLocation(const std::string& name) {
	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform " << name << " doesn't exitst" << std::endl;

	return location;
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}
