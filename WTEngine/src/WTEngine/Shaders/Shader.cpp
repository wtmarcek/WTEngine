#include "wtfpch.h"

#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>

namespace WTF {

	Shader::Shader(std::string& filePath)
		: m_FilePath(filePath), m_RendererID(0)
	{
		ShaderProgramSource source = ParseShader(filePath);
		m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
	}

	Shader::~Shader()
	{
		GLCall(glDeleteProgram(m_RendererID));
	}

	void Shader::Bind() const
	{
		GLCall(glUseProgram(m_RendererID));
	}

	void Shader::Unbind() const
	{
		GLCall(glUseProgram(0));
	}

	void Shader::SetUniform1i(const std::string & name, int value)
	{
		GLCall(glUniform1i(GetUniformLocation(name), value));
	}

	void Shader::SetUniform1f(const std::string & name, float value)
	{
		GLCall(glUniform1f(GetUniformLocation(name), value));
	}

	void Shader::SetUniform4f(const std::string & name, float v0, float v1, float v2, float v3)
	{
		GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
	}

	void Shader::SetUniformMat4f(const std::string & name, const glm::mat4 & value)
	{
		GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]));
	}

	ShaderProgramSource Shader::ParseShader(const std::string& filepath)
	{
		std::fstream stream(filepath);

		enum class ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};
		
		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;
		while (std::getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					type = ShaderType::FRAGMENT;
				}
			}
			else
			{
				if ((int)type > -1)
				{
					ss[(int)type] << line << '\n';
				}
			}
		}

		return { ss[(int)ShaderType::VERTEX].str(), ss[(int)ShaderType::FRAGMENT].str() };
	}

	unsigned int Shader::CompileShader(unsigned int type, const std::string & source)
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		GLCall(glShaderSource(id, 1, &src, nullptr));
		GLCall(glCompileShader(id));

		int result;
		GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE)
		{
			int length = 0;
			GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &result));
			std::unique_ptr<char> message = std::make_unique<char>();
			GLCall(glGetShaderInfoLog(id, length, &length, message.get()));
			std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
			std::cout << message.get() << std::endl;
			return 0;
		}

		return id;
	}

	unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		GLCall(unsigned int program = glCreateProgram());
		GLCall(unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader));
		GLCall(unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader));

		GLCall(glAttachShader(program, vs));
		GLCall(glAttachShader(program, fs));
		GLCall(glLinkProgram(program));
		GLCall(glValidateProgram(program));

		GLCall(glDeleteShader(vs));
		GLCall(glDeleteShader(fs));

		return program;
	}

	int Shader::GetUniformLocation(const std::string & name)
	{
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
		{
			return m_uniformLocationCache[name];
		}

		GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
		if (location == -1)
		{
			std::cout << "Warning: uniform " << name << " does not exist!" << std::endl;
		}
		m_uniformLocationCache[name] = location;
		return location;
	}

}