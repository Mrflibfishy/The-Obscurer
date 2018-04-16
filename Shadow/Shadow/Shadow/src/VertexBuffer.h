#pragma once
#include <GL/glew.h>
#include "Renderer.h"

class VertexBuffer {
	private:
		GLuint id;
		GLuint amountData = 0;
	public:
		VertexBuffer(const void* data, unsigned int size);
		VertexBuffer();

		void addData(const void* data, unsigned int size);

		void Bind() const;
		void unBind() const;

		
};