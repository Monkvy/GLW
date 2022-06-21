#include "Renderer.h"

#include <algorithm>

#include <glm/glm.hpp>


namespace glw
{

	Renderer::Renderer(glm::mat4 projectionMatrix, std::string shaderFilePath)
		: m_Vbo(GLW_MAX_VERTICES), m_Ibo(GLW_MAX_INDICES), m_BasicShader(shaderFilePath), m_Color{1, 1, 1, 1}
	{
        m_Vao.AddBuffer(m_Vbo);
        m_BasicShader.Bind();
        m_BasicShader.SetUniformMat4f("u_MVP", projectionMatrix);
	}

	Renderer::~Renderer()
	{
		
	}

	void Renderer::BeginDraw()
    {
		m_Vertices.clear();
		m_Indices.clear();
        glClear(GL_COLOR_BUFFER_BIT);
    }

	void Renderer::DrawRect(vec2 pos, vec2 size, int textureID)
	{
		Vertex v0{
			{ pos.x, pos.y },
			{ m_Color.x, m_Color.y, m_Color.z, m_Color.w },
			{ 0.0, 0.0 },
			(float)textureID
		};
		Vertex v1{
			{ pos.x + size.x, pos.y},
			{ m_Color.x, m_Color.y, m_Color.z, m_Color.w },
			{ 0.0, 1.0 },
			(float)textureID
		};
		Vertex v2{
			{ pos.x, pos.y + size.y },
			{ m_Color.x, m_Color.y, m_Color.z, m_Color.w },
			{ 1.0, 0.0 },
			(float)textureID
		};
		Vertex v3{
			{ pos.x + size.x, pos.y + size.y },
			{ m_Color.x, m_Color.y, m_Color.z, m_Color.w },
			{ 1.0, 1.0 },
			(float)textureID
		};

		m_Vertices.push_back(v0);
		m_Vertices.push_back(v1);
		m_Vertices.push_back(v2);
		m_Vertices.push_back(v3);

		uint32_t max = 0;
		if (m_Indices.size() != 0) {
			max = *std::max_element(m_Indices.begin(), m_Indices.end()) + 1;
		}

		m_Indices.push_back(0 + max);
		m_Indices.push_back(1 + max);
		m_Indices.push_back(3 + max);

		m_Indices.push_back(0 + max);
		m_Indices.push_back(2 + max);
		m_Indices.push_back(3 + max);
	}

	void Renderer::DrawTriangle(vec2 p1, vec2 p2, vec2 p3, int textureID)
	{
		Vertex v0{
			{ p1.x, p1.y },
			{ m_Color.x, m_Color.y, m_Color.z, m_Color.w },
			{ 0.0, 0.0 },
			(float)textureID
		};
		Vertex v1{
			{ p2.x, p2.y},
			{ m_Color.x, m_Color.y, m_Color.z, m_Color.w },
			{ 0.0, 1.0 },
			(float)textureID
		};
		Vertex v2{
			{ p3.x, p3.y },
			{ m_Color.x, m_Color.y, m_Color.z, m_Color.w },
			{ 1.0, 0.0 },
			(float)textureID
		};

		m_Vertices.push_back(v0);
		m_Vertices.push_back(v1);
		m_Vertices.push_back(v2);

		uint32_t max = 0;
		if (!m_Indices.empty()) {
			max = *std::max_element(m_Indices.begin(), m_Indices.end()) + 1;
		}

		m_Indices.push_back(0 + max);
		m_Indices.push_back(1 + max);
		m_Indices.push_back(2 + max);
	}

	void Renderer::EndDraw() const
    {
		m_Vao.Bind();
		m_Vao.Bind();
		m_Ibo.Bind();
        m_BasicShader.Bind();

		// Write vertices data
		Vertex vertices[GLW_MAX_VERTICES];
		std::copy(m_Vertices.begin(), m_Vertices.end(), vertices);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		// Write indices data
		uint32_t indices[GLW_MAX_INDICES];
		std::copy(m_Indices.begin(), m_Indices.end(), indices);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);

        glDrawElements(GL_TRIANGLES, GLW_MAX_INDICES, GL_UNSIGNED_INT, nullptr);
    }
}