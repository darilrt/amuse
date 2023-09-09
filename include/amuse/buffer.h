#pragma once

#include "amuse/buffer.h"

#include <cstdint>

namespace gl {
    
	enum class Type {
		Float = 0x1406,
		Int = 0x1404,
		UInt = 0x1405,
	};

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

		void AddBufferFloat(VertexBuffer& vbo, uint32_t count);

	private:

		uint32_t id = 0;
		uint32_t count = 0;
	};

	template<>
	void gl::VertexArray::AddBuffer<float>(VertexBuffer& vbo, uint32_t count);

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
