#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>


namespace GLW 
{
	// The return type of the Shader::ParseShader() function.
	struct ShaderProgramSource 
	{
		std::string VertexSource;
		std::string FragmentSource;
	};


	// Use this class to handle the vertex & fragment shader
	// Calling the constructor will bind the shader & 
	// initialize the u_Textures shader uniform
	class Shader 
	{
	public:
		Shader(const std::string& filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		// Uniforms
		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform1iv(const std::string& name, int size, int value[]);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

	private:
		std::string m_Filepath;
		unsigned int m_RendererID;
		std::unordered_map<std::string, int> m_UniformLocationCache;

		// Separates the vertex & fragment shader source code
		ShaderProgramSource ParseShader(const std::string& filepath);
		// Compile the source code of a given shader type
		unsigned int CompileShader(unsigned int type, const std::string& source);
		// Create the shader program and store its ID in m_RendererID
		void CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		unsigned int GetUniformLocation(const std::string& name);
	};
}