#pragma once
#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLW::GLClearError(); \
    x; \
    ASSERT(GLW::GLLogCall(#x, __FILE__, __LINE__))

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"


namespace GLW 
{
    // Removes all OpenGL Errors so the glGetError
    // function can be called to get the latest error.
    void GLClearError();

    // This function prints out the latest OpenGL errors
    // and the function, file & line number, where the error occurred.
    bool GLLogCall(const char* function, const char* file, int line);


    class Renderer 
    {
    public:
        void Clear() const;
        void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;
    };
}
