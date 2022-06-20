#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLW/gwl.h"


int main()
{
	// Initialize GLFW
	if (!glfwInit())
		throw std::runtime_error("glfwInit failed!");

	// Set the OpenGL version & profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window
	const uint32_t width = 1280, height = 960;
	GLFWwindow* window = glfwCreateWindow(width, height, "GLW", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		throw std::runtime_error("glfwCreateWindow failed!");
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		throw std::runtime_error("glewInit failed!");
	}

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize GLW
	GLW::InitGLErrorCallback(GL_DEBUG_SEVERITY_NOTIFICATION+1);

	// Print the current OpenGL version
	std::cout << "GL " << glGetString(GL_VERSION) << std::endl;

	// Renderer
	glm::mat4 proj = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
	GLW::Renderer renderer(proj, "res/shaders/Basic.shader");

	// Create textures
	GLW::Texture texture1("res/img1.png");
	GLW::Texture texture2("res/img2.png");
	texture1.Bind(0);
	texture2.Bind(1);

	float x = 0.0;

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		renderer.BeginDraw();
		renderer.DrawRect({ x, 400.0f }, { 100.0f, 150.0f }, 0);
		renderer.DrawTriangle({ width / 2, height / 4 }, { width / 4, height - height / 4 }, { width - width / 4, height - height / 4}, 1);
		renderer.EndDraw();

		x += 0.2f;

		// Swap buffers & poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Cleanup
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
