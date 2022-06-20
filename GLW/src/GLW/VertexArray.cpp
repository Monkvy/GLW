#include "VertexArray.h"

#include "Vertex.h"


namespace GLW 
{
	VertexArray::VertexArray() 
	{
		glGenVertexArrays(1, &m_RendererID);
	}

	VertexArray::~VertexArray() 
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::AddBuffer(const VertexBuffer& vertexBuffer)
	{
		Bind();
		vertexBuffer.Bind();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, sizeof(Vertex::position) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, sizeof(Vertex::color) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, sizeof(Vertex::texCoords) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texCoords));

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, sizeof(Vertex::texID) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texID));
	}

	void VertexArray::AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout) 
	{
		Bind();
		vertexBuffer.Bind();

		const auto& elements = layout.GetElements();
		uint32_t offset = 0;

		for (uint32_t i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
			offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
		}
	}

	void VertexArray::Bind() const 
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind() const 
	{
		glBindVertexArray(0);
	}
}