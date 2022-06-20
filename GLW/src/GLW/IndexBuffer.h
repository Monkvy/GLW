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

		// Get the number of the maximum indices.
		inline uint32_t getCount() const { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}