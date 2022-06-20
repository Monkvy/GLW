#pragma once
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

	class Shader 
	{
	public:
		Shader(const std::string& filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform1iv(const std::string& name, int size, int value[]);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

	private:
		std::string m_Filepath;
		uint32_t m_RendererID;
		std::unordered_map<std::string, int> m_UniformLocationCache;

		ShaderProgramSource ParseShader(const std::string& filepath);
		uint32_t CompileShader(uint32_t type, const std::string& source);
		void CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

		uint32_t GetUniformLocation(const std::string& name);
	};
}