#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


namespace GLW 
{
	class VertexArray 
	{
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
		void Bind() const;
		void Unbind() const;

	private:
		unsigned int m_RendererID;
	};
}