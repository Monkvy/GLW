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
        // @param glm::mat4 projectionMatrix - The projection matrix, that defines, what the lowest & highest x & y value is.
        // @param std::string shaderFilePath - The file path to the shader file, that contains the vertex & fragment shader.
        Renderer(glm::mat4 projectionMatrix, std::string shaderFilePath);
        ~Renderer();

        void SetColor(vec4 color) { m_Color = color; }

        // Clears the screen & clears the vertices & indices vector.
        // Has to be called before every draw function.
        void BeginDraw();

        // @param vec2 position - The top left position of the rectangle
        // @param vec2 size - The width and height.
        // @param uint32_t textureID(-1) - The texture id of the rect (-1 = no texture, use colors).
        void DrawRect(vec2 position, vec2 size, uint32_t textureID=-1);

		// @param vec2 p1, p2, p3 - The triangle corners.
		// @param uint32_t textureID(-1) - The texture id (-1 = no texture, use colors).
        void DrawTriangle(vec2 p1, vec2 p2, vec2 p3, int textureID=-1);

        // Renders everything on the screen.
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
