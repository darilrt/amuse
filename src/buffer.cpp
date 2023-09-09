#include "amuse/buffer.h"
#include "amuse/gldefs.h"

#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <SDL.h>
#include <iostream>

gl::VertexArray::VertexArray() {
	GL_CALL(glGenVertexArrays(1, &this->id));
}

gl::VertexArray::~VertexArray() {
	GL_CALL(glDeleteVertexArrays(1, &this->id));
}

void gl::VertexArray::Bind() {
	GL_CALL(glBindVertexArray(this->id));
}

void gl::VertexArray::Unbind() {
	GL_CALL(glBindVertexArray(0));
}

void gl::VertexArray::DrawTriangles(IndexBuffer &ibo) {
	this->Bind();
	ibo.Bind();
	GL_CALL(glDrawElements(GL_TRIANGLES, ibo.count, GL_UNSIGNED_INT, nullptr));
}

void gl::VertexArray::DrawLines(int32_t linesCount) {
	this->Bind();
	GL_CALL(glDrawArrays(GL_LINES, 0, linesCount));
}

void gl::VertexArray::AddBufferFloat(VertexBuffer& vbo, uint32_t count) {
	this->Bind();
	vbo.Bind();

	GL_CALL(glVertexAttribPointer(this->count, count, GL_FLOAT, GL_FALSE, 0, nullptr));
	GL_CALL(glEnableVertexAttribArray(this->count));

	this->count++;
}

gl::VertexBuffer::VertexBuffer() {
	GL_CALL(glGenBuffers(1, &this->id));
}

gl::VertexBuffer::~VertexBuffer() {
	GL_CALL(glDeleteBuffers(1, &this->id));
}

void gl::VertexBuffer::Bind() {
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, this->id));
}

void gl::VertexBuffer::Unbind() {
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void gl::VertexBuffer::SetData(void* data, uint32_t size) {
	this->Bind();
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

gl::IndexBuffer::IndexBuffer() {
	GL_CALL(glGenBuffers(1, &this->id));
}

gl::IndexBuffer::~IndexBuffer() {
	GL_CALL(glDeleteBuffers(1, &this->id));
}

void gl::IndexBuffer::Bind() {
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id));
}

void gl::IndexBuffer::Unbind() {
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void gl::IndexBuffer::SetData(void *data, uint32_t count) {
	this->count = count;
	this->Bind();
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW));
}

template<>
void gl::VertexArray::AddBuffer<float>(VertexBuffer& vbo, uint32_t count) { AddBufferFloat(vbo, count); }