#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "Graphics/GL.h"

namespace Graphics
{
	Shader::Shader(const std::string& filePath)
	{
		std::ifstream stream(filePath);
		if (stream.fail()) printf("%s doesn't exist\n", filePath);

		std::stringstream ss;
		std::string line;

		while (getline(stream, line)) ss << line << "\n";
		std::string* data = new std::string(ss.str());

		if (data)
		{
			auto [vertexShaderSource, fragmentShaderSource] = ParseShader(data);
			mRendererId = CreateShader(vertexShaderSource, fragmentShaderSource);
			delete data;
		}
		stream.close();
	}

	Shader::~Shader()
	{
		if (mRendererId == 0) return;
		glDeleteProgram(mRendererId);
	}

	void Shader::Bind() const
	{
		glUseProgram(mRendererId);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::SetUniform1i(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetUniform2f(const std::string& name, float v0, float v1)
	{
		glUniform2f(GetUniformLocation(name), v0, v1);
	}

	void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
	{
		glUniform3f(GetUniformLocation(name), v0, v1, v2);
	}

	void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void Shader::SetUniformMatrix4fv(const std::string& name, float m[16])
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, m);
	}

	int Shader::GetUniformLocation(const std::string& name)
	{
		if (mUniformLocations.find(name) != mUniformLocations.end()) return mUniformLocations[name];

		int location = glGetUniformLocation(mRendererId, name.c_str());
		if (location == -1) std::cout << "Uniform " << name << " doesn't exist\n";
		mUniformLocations[name] = location;
		return location;
	}

	std::tuple<std::string, std::string> Shader::ParseShader(const std::string* shaderData) const
	{
		enum class ShaderType
		{
			None = -1,
			Vertex = 0,
			Fragment = 1
		};

		const unsigned int vertexStart = shaderData->find("#shader vertex");
		const unsigned int fragmentStart = shaderData->find("#shader fragment");
		const unsigned int size = shaderData->size();

		if (vertexStart == std::string::npos || fragmentStart == std::string::npos)
		{
			printf("Shader data is invalid! Aborting");
			return {};
		}

		return { (shaderData->substr(vertexStart + 15, fragmentStart - vertexStart - 15)),
			(shaderData->substr(fragmentStart + 17, size - fragmentStart - 17)) };
	}

	unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			printf("Failed to compile shader! %s\n", message);
			glDeleteShader(id);
			return GL_INVALID_ID;
		}

		return id;
	}

	unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		unsigned int program = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}
}
