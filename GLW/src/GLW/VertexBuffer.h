#pragma once
#include <iostream>


namespace GLW
{
	class VertexBuffer 
	{
	public:
		VertexBuffer(uint32_t maxVertices, const void* data=nullptr);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_RendererID;
	};
}