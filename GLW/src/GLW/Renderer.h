#pragma once
#include <iostream>
#include <array>
#include <vector>
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Vertex.h"

#define GLW_MAX_VERTICES 400
#define GLW_MAX_INDICES 600


namespace GLW 
{
    class Renderer 
    {
    public:
        Renderer(glm::mat4 projectionMatrix, std::string shaderFilePath);
        ~Renderer();

        void SetColor(vec4 color) { m_Color = color; }

        void BeginDraw();
        void DrawRect(vec2 position, vec2 size, uint32_t textureID=-1);
        void DrawTriangle(vec2 p1, vec2 p2, vec2 p3, int textureID=-1);
        void EndDraw() const;

    private:
        VertexArray m_Vao;
        VertexBuffer m_Vbo;
        IndexBuffer m_Ibo;
        Shader m_BasicShader;
        vec4 m_Color;

        std::vector<Vertex> m_Vertices;
        std::vector<uint32_t> m_Indices;
    };
}
