#pragma once
#include <iostream>


namespace glw
{
	class IndexBuffer 
	{
	public:
		IndexBuffer(uint32_t maxIndices);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_RendererID;
	};
}