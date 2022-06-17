#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Renderer.h"


namespace GLW 
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
        GLCall(glDeleteProgram(m_RendererID))
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

    unsigned int Shader::CompileShader(unsigned int type, const std::string& source) 
    {
        // Create the shader
        GLCall(unsigned int id = glCreateShader(type));
        const char* src = source.c_str();

        // Compile the shader
        GLCall(glShaderSource(id, 1, &src, nullptr));
        GLCall(glCompileShader(id));

        // Handle errors
        int result;
        GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

        if (result == GL_FALSE) 
        {
            // Get the length of the error message
            int length;
            GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

            // Get the error message
            char* message = new char[length];
            GLCall(glGetShaderInfoLog(id, length, &length, message));

            // Get the type in string to tell the user what shader failed
            std::string shaderType = "Vertex shader";
            if (type == GL_FRAGMENT_SHADER) shaderType = "Fragment shader";
            else shaderType = "shader";

            // Print the error message
            std::cout << "Failed to compile " << shaderType << std::endl;
            std::cout << message << std::endl;

            // Free memory & return
            delete[] message;
            GLCall(glDeleteShader(id));
            return NULL;
        }
        return id;
    }

    void Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) 
    {
        // Create program & compile shaders
        GLCall(m_RendererID = glCreateProgram());
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        // Attach shaders to the program
        GLCall(glAttachShader(m_RendererID, vs));
        GLCall(glAttachShader(m_RendererID, fs));
        GLCall(glLinkProgram(m_RendererID));
        GLCall(glValidateProgram(m_RendererID));

        // Delete the shaders
        GLCall(glDeleteShader(vs));
        GLCall(glDeleteShader(fs));
    }

    void Shader::Bind() const 
    {
        GLCall(glUseProgram(m_RendererID));
    }

    void Shader::Unbind() const 
    {
        GLCall(glUseProgram(0));
    }

    void Shader::SetUniform1i(const std::string& name, int value) 
    {
        GLCall(glUniform1i(GetUniformLocation(name), value));
    }

    void Shader::SetUniform1f(const std::string& name, float value) 
    {
        GLCall(glUniform1f(GetUniformLocation(name), value));
    }

    void Shader::SetUniform1iv(const std::string& name, int size, int value[]) {
        GLCall(glUniform1iv(GetUniformLocation(name), size, value));
    }

    void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) 
    {
        GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
    }

    void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) 
    {
        GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
    }

    unsigned int Shader::GetUniformLocation(const std::string& name) 
    {
        std::cout << "called: " << name << std::endl;
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
            return m_UniformLocationCache[name];

        GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
        if (location == -1)
            std::cout << "Warning: uniform " << name << " does not exist!" << std::endl;

        m_UniformLocationCache[name] = location;
        return location;
    }
}