#pragma once
#include <gl\glew.h>
#include "Renderer.h"
#include <string>

struct shaderProgramSource {
	const char* VertexSource;
	const char* FragmentSource;
	void Set(const char*  VS, const char*  FS) {
		VertexSource = VS;
		FragmentSource = FS;
	}

};

class Shader
{
private:
	shaderProgramSource m_FilePath;
	unsigned int  m_RendererID;
public:
	Shader(const char* filepathVS, const char* filepathFS);
	~Shader();
	void Bind();
	void unBind();

	unsigned int getID() {
		return m_RendererID;
	}

	//Set uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	bool checkStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType);
	bool checkShaderStatus(GLuint shaderID);
	unsigned int CreateShader(const char* vetexSource, const char* fragmentSource);
	int GetUniformLocation(const std::string& name);
};
