#include "VertexBuffer.h"

#include <GL/glew.h>

#include "Vertex.h"


namespace glw
{
    VertexBuffer::VertexBuffer(uint32_t maxVertices, const void* data)
    {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, maxVertices * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() 
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    void VertexBuffer::Bind() const 
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void VertexBuffer::Unbind() const 
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}