#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


namespace glw
{
	class VertexArray 
	{
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vertexBuffer);
		void AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_RendererID;
	};
}