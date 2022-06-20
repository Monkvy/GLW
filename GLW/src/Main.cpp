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


static std::array<GLW::Vertex, 3> CreateTriangle(std::vector<uint32_t>& indices, float x1, float y1, float x2, float y2, float x3, float y3, float texID = -1) {
	GLW::Vertex v0{
		{ x1, y1 },
		{ 1.0, 0.5, 1.0, 1.0 },
		{ 0.0, 0.0 },
		texID
	};

	GLW::Vertex v1{
		{ x2, y2},
		{ 1.0, 0.5, 1.0, 1.0 },
		{ 0.0, 1.0 },
		texID
	};

	GLW::Vertex v2{
		{ x3, y3 },
		{ 1.0, 0.5, 1.0, 1.0 },
		{ 1.0, 1.0 },
		texID
	};

	uint32_t max = 0;
	if (indices.size() != 0) {
		max = *std::max_element(indices.begin(), indices.end()) + 1;
	}

	indices.push_back(0 + max);
	indices.push_back(1 + max);
	indices.push_back(2 + max);

	return { v0, v1, v2};
}

static std::array<GLW::Vertex, 4> CreateRect(std::vector<uint32_t>& indices, float x, float y, float sizeX, float sizeY, float texID=-1) {
	GLW::Vertex v0{
		{ x, y },
		{ 1.0, 0.5, 1.0, 1.0 },
		{ 0.0, 0.0 },
		texID
	};

	GLW::Vertex v1{
		{ x, y + sizeY},
		{ 1.0, 0.5, 1.0, 1.0 },
		{ 0.0, 1.0 },
		texID
	};

	GLW::Vertex v2{
		{ x + sizeX, y },
		{ 1.0, 0.5, 1.0, 1.0 },
		{ 1.0, 0.0 },
		texID
	};

	GLW::Vertex v3{
		{ x + sizeX, y + sizeY },
		{ 1.0, 0.5, 1.0, 1.0 },
		{ 1.0, 1.0 },
		texID
	};

	uint32_t max = 0;
	if (indices.size() != 0) {
		max = *std::max_element(indices.begin(), indices.end()) + 1;
	}

	indices.push_back(0 + max);
	indices.push_back(1 + max);
	indices.push_back(2 + max);

	indices.push_back(1 + max);
	indices.push_back(2 + max);
	indices.push_back(3 + max);

	return { v0, v1, v2, v3 };
}


int main()
{
	// Initialize GLFW
	if (!glfwInit())
		throw std::runtime_error("glfwInit failed!");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window
	const unsigned int width = 1280, height = 960;
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Application", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		throw std::runtime_error("glfwCreateWindow failed!");
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		throw std::runtime_error("glewInit failed!");
	}

	GLW::InitGLErrorCallback(GL_DEBUG_SEVERITY_NOTIFICATION+1);

	// Print the current OpenGL version
	std::cout << "GL " << glGetString(GL_VERSION) << std::endl;

	{
		// Blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		// Renderer
		glm::mat4 proj = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
		GLW::Renderer renderer(proj, "res/shaders/Basic.shader");

		// Create texture
		GLW::Texture texture1("res/img1.png");
		GLW::Texture texture2("res/img2.png");
		texture1.Bind(0);
		texture2.Bind(1);

		float x = 0.0;

		// Main loop
		while (!glfwWindowShouldClose(window))
		{
			renderer.BeginDraw();
			renderer.DrawRect({ x, 400.0 }, { 100.0, 150.0 }, 0);
			renderer.DrawTriangle({ width / 2, height / 4 }, { width / 4, height - height / 4 }, { width - width / 4, height - height / 4}, 1);
			renderer.EndDraw();

			x += 0.2;

			// Swap buffers & poll events
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	// Cleanup
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
