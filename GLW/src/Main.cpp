#include <iostream>
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

    // Print the current OpenGL version
    std::cout << "GL " << glGetString(GL_VERSION) << std::endl;

    {
		float rect_size = 200;
		float top = height / 2 - 200 / 2;
		float left1 = width / 2 - rect_size * 2;
		float left2 = width / 2 + rect_size;
		
		// 0: top left, 1: bottom left, 2: top right, 3: bottom right
		// 0, 1: position, 2, 3, 4, 5: color, 6, 7: texture coordinate, 8: texture id
		float positions[] = {
			(float)left1,				(float)top,				  0.18f, 0.6f, 0.96f, 1.0f, 0.0f, 0.0f, 0.0f,
			(float)left1,				(float)(top + rect_size), 0.18f, 0.6f, 0.96f, 1.0f, 0.0f, 1.0f, 0.0f,
			(float)(left1 + rect_size), (float)top,				  0.18f, 0.6f, 0.96f, 1.0f, 1.0f, 0.0f, 0.0f,
			(float)(left1 + rect_size), (float)(top + rect_size), 0.18f, 0.6f, 0.96f, 1.0f, 1.0f, 1.0f, 0.0f,

			(float)left2,				(float)top,				  1.0f, 0.093f, 0.24f, 1.0f, 0.0f, 0.0f, 1.0f,
			(float)left2,				(float)(top + rect_size), 1.0f, 0.093f, 0.24f, 1.0f, 0.0f, 1.0f, 1.0f,
			(float)(left2 + rect_size), (float)top,				  1.0f, 0.093f, 0.24f, 1.0f, 1.0f, 0.0f, 1.0f,
			(float)(left2 + rect_size), (float)(top + rect_size), 1.0f, 0.093f, 0.24f, 1.0f, 1.0f, 1.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			1, 2, 3,

			4, 5, 6,
			5, 6, 7
		};

		// Blending
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		// Vertex array & vertex buffer
		GLW::VertexArray va;
		GLW::VertexBuffer vb(positions, 8 * 9 * sizeof(float));
		GLW::VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(4);
		layout.Push<float>(2);
		layout.Push<float>(1);
		va.AddBuffer(vb, layout);

		// Index buffer
		GLW::IndexBuffer ib(indices, 12);

		// Shader
		GLW::Shader shader("res/shaders/basic.shader");
		shader.Bind();

		// Projection matrix
		glm::mat4 proj = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
		shader.SetUniformMat4f("u_MVP", proj);

		GLW::Renderer renderer;

		// Create texture
		GLW::Texture texture1("res/img1.png");
		GLW::Texture texture2("res/img2.png");
		texture1.Bind(0);
		texture2.Bind(1);

		// Unbind everything
		va.Unbind();
		shader.Unbind();
		vb.Unbind();
		ib.Unbind();

		// Main loop
		while (!glfwWindowShouldClose(window))
		{
			renderer.Clear();

			shader.Bind();
			renderer.Draw(va, ib, shader);

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
