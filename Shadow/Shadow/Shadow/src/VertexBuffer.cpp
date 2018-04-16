#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	GLCall(glGenBuffers(1, &id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
VertexBuffer::VertexBuffer() {
	GLCall(glDeleteBuffers(1, &id));
}

void VertexBuffer::addData(const void* data, unsigned int size) {
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
	amountData += size;
}

void VertexBuffer::Bind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void VertexBuffer::unBind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}