#pragma once

#include "amuse/buffer.h"

#include <cstdint>

namespace gl {
    
	class IndexBuffer {
	public:
		uint32_t count;

		IndexBuffer();
		~IndexBuffer();

		void Bind();
		void Unbind();
		
		void SetData(void* data, uint32_t count);
		
	private:
		uint32_t id;
	};

	class VertexBuffer {
	public:
		VertexBuffer();
		~VertexBuffer();

		void Bind();
		void Unbind();

		void SetData(void* data, uint32_t size);

	private:
		uint32_t id;
	};

	class VertexArray {
	public:
		VertexArray();
		~VertexArray();

		void Bind();
		void Unbind();

		void DrawTriangles(IndexBuffer& ibo);

		void DrawLines(int32_t linesCount);

		template<typename T>
		void AddBuffer(VertexBuffer& vbo, uint32_t count) { }

		template<>
		void AddBuffer<float>(VertexBuffer& vbo, uint32_t count) { AddBufferFloat(vbo, count); }

	private:
		void AddBufferFloat(VertexBuffer& vbo, uint32_t count);

		uint32_t id = 0;
		uint32_t count = 0;
	};

	class FrameBuffer {
	public:
		// FrameBuffer();

		// void Bind();
		// void Unbind();

		// void AttachTexture(Texture& texture);

	private:
		uint32_t id;
	};
}
