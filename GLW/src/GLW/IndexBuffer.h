#pragma once
#include <iostream>


namespace GLW 
{
	class IndexBuffer 
	{
	public:
		IndexBuffer(uint32_t maxIndices);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;
		inline uint32_t getCount() const { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}