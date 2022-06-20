#pragma once
#include <iostream>
#include <gl/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLW::GLClearError(); \
    x; \
    ASSERT(GLW::GLLogCall(#x, __FILE__, __LINE__))


namespace GLW 
{
	static unsigned int minGLErrorSeverity;

	static void GLErrorCallback(
		GLenum source,
		GLenum type, 
		GLuint id, 
		GLenum severity,
		GLsizei length, 
		const GLchar* message, 
		const void* userParam)
	{
		if (severity >= minGLErrorSeverity)
			std::cout << "[OpenGL Error] " << message << " [Severity: " << severity << "]" << std::endl << std::endl;
	}

	static void InitGLErrorCallback(unsigned int minSeverity)
	{
		minGLErrorSeverity = minSeverity;
		glDebugMessageCallback(GLErrorCallback, nullptr);
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	}

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
}