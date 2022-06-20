#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>


namespace glw
{
    Shader::Shader(const std::string& filepath)
        : m_Filepath(filepath), m_RendererID(0)
    {
        ShaderProgramSource source = ParseShader(filepath);
        CreateShader(source.VertexSource, source.FragmentSource);

        // Initialize texture slots
		int samplers[32];
        for (int i = 0; i < 32; i++)
            samplers[i] = i;

        Bind();
		SetUniform1iv("u_Textures", 32, samplers);
    }

    Shader::~Shader() 
    {
        glDeleteProgram(m_RendererID);
    }

    ShaderProgramSource Shader::ParseShader(const std::string& filepath) 
    {
        std::ifstream stream(filepath);

        enum class ShaderType 
        {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;

        while (getline(stream, line)) 
        {
            if (line.find("#shader") != std::string::npos) 
            {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::VERTEX;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::FRAGMENT;
            }
            else
                ss[(int)type] << line << std::endl;
        }
        return { ss[0].str(), ss[1].str() };
    }

    uint32_t Shader::CompileShader(uint32_t type, const std::string& source)
    {
        // Create the shader
        uint32_t id = glCreateShader(type);
        const char* src = source.c_str();

        // Compile the shader
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        // Handle errors
        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE) 
        {
            // Get the length of the error message
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

            // Get the error message
            auto* message = new char[length];
            glGetShaderInfoLog(id, length, &length, message);

            // Get the type in string to tell the user what shader failed
            std::string shaderType = "Vertex shader";
            if (type == GL_FRAGMENT_SHADER) shaderType = "Fragment shader";
            else shaderType = "shader";

            // Print the error message
            std::cout << "Failed to compile " << shaderType << std::endl;
            std::cout << message << std::endl;

            // Free memory & return
            delete[] message;
            glDeleteShader(id);
            return NULL;
        }
        return id;
    }

    void Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) 
    {
        // Create program & compile shaders
        m_RendererID = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        // Attach shaders to the program
        glAttachShader(m_RendererID, vs);
        glAttachShader(m_RendererID, fs);
        glLinkProgram(m_RendererID);
        glValidateProgram(m_RendererID);

        // Delete the shaders
        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    void Shader::Bind() const 
    {
        glUseProgram(m_RendererID);
    }

    void Shader::Unbind() const 
    {
        glUseProgram(0);
    }

    void Shader::SetUniform1i(const std::string& name, int value) 
    {
        glUniform1i(GetUniformLocation(name), value);
    }

    void Shader::SetUniform1f(const std::string& name, float value) 
    {
        glUniform1f(GetUniformLocation(name), value);
    }

    void Shader::SetUniform1iv(const std::string& name, int size, int value[]) {
        glUniform1iv(GetUniformLocation(name), size, value);
    }

    void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) 
    {
        glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
    }

    void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) 
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
    }

    uint32_t Shader::GetUniformLocation(const std::string& name)
    {
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
            return m_UniformLocationCache[name];

        uint32_t location = glGetUniformLocation(m_RendererID, name.c_str());
        if (location == -1)
            std::cout << "Warning: uniform " << name << " does not exist!" << std::endl;

        m_UniformLocationCache[name] = location;
        return location;
    }
}