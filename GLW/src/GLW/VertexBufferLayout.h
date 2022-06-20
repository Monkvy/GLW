#pragma once
#include <vector>

#include <GL/glew.h>


namespace glw
{
	struct VertexBufferElement 
	{
		uint32_t type;
		uint32_t count;
		unsigned char normalized;

		// Get the size in bytes of a given type
		// @param uint32_t type - The type (GL_FLOAT, GL_UNSIGNED_INT or GL_UNSIGNED_BYTE)
		static uint32_t GetSizeOfType(uint32_t type);
	};

	class VertexBufferLayout 
	{
	public:
		VertexBufferLayout() : m_Stride(0) {}

		template<typename T>
		void Push(uint32_t count);
		template<>
		void Push<float>(uint32_t count);
		template<>
		void Push<uint32_t>(uint32_t count);
		template<>
		void Push<unsigned char>(uint32_t count);

		inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
		inline uint32_t GetStride() const { return m_Stride; }

	private:
		std::vector<VertexBufferElement> m_Elements;
		uint32_t m_Stride;
	};
}