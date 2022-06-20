#pragma once
#include <iostream>

#include <gl/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLW::GLClearError(); \
    x; \
    ASSERT(GLW::GLLogCall(#x, __FILE__, __LINE__))


namespace glw 
{
	static uint32_t minGLErrorSeverity;

	// OpenGL error callback function. 
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

	// Initialize the OpenGL error callback function
	// @param uint32_t minSeverity - The minimum severity on which errors are displayed
	static void InitGLErrorCallback(uint32_t minSeverity)
	{
		minGLErrorSeverity = minSeverity;
		glDebugMessageCallback(GLErrorCallback, nullptr);
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	}

	// Clear every OpenGL error, so the glGetError function returns the latest error.
	void GLClearError()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	// Used by the GLCall function
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