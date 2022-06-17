#include "Renderer.h"
#include <iostream>


namespace GLW 
{
    void GLClearError() 
    {
        while (glGetError() != GL_NO_ERROR);
    }

    bool GLLogCall(const char* function, const char* file, int line) 
    {
        while (GLenum error = glGetError()) 
        {
            std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
            return false;
        }
        return true;
    }

    void Renderer::Clear() const 
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const 
    {
        shader.Bind();
        vertexArray.Bind();
        indexBuffer.Bind();

        GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr));
    }
}