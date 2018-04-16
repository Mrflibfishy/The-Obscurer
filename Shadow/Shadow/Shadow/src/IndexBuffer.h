#pragma once
#include <GL/glew.h>
#include "Renderer.h"

class IndexBuffer {
private:
	GLuint id;
	GLuint count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	IndexBuffer();

	void Bind() const;
	void unBind() const;

	inline unsigned int GetCount() const { return count; }
};