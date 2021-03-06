#include "IndexBuffer.h"

#include <GL/glew.h>


namespace glw
{
    IndexBuffer::IndexBuffer(uint32_t maxIndices)
	{
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxIndices * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);
    }

	IndexBuffer::~IndexBuffer()
	{
        glDeleteBuffers(1, &m_RendererID);
    }

    void IndexBuffer::Bind() const 
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void IndexBuffer::Unbind() const 
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}