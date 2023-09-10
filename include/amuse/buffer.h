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
		enum Usage : uint32_t {
			Stream = 0x88E0,
			Static = 0x88E4,
			Dynamic = 0x88E8,
		};

		VertexBuffer();
		~VertexBuffer();

		void Bind();
		void Unbind();

		void SetData(void* data, uint32_t size, gl::VertexBuffer::Usage usage);

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

		void AddBuffer(VertexBuffer& vbo, gl::Type type, uint32_t count);

	private:

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
