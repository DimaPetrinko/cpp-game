#pragma once

#include <fstream>
#include <sstream>
#include <tuple>
#include "Graphics/GL.h"

namespace Graphics::Shaders
{
	const unsigned int GetUniformLocation(unsigned int shader, const std::string& name)
	{
		int location = glGetUniformLocation(shader, name.c_str());
		if (location == -1) std::cout << "Uniform " << name << " doesn't exist\n";
		return location;
	}

	const std::string* LoadShaderFile(const std::string& filePath)
	{
		std::ifstream stream(filePath);
		if (stream.fail()) printf("%s doesn't exist\n", filePath);

		std::stringstream ss;
		std::string line;

		while (getline(stream, line)) ss << line << "\n";
		std::string* data = new std::string(ss.str());
		stream.close();
		return data;
	}

	std::tuple<std::string, std::string> ParseShader(const std::string* shaderData)
	{
		const unsigned int vertexStart = shaderData->find("#shader vertex");
		const unsigned int fragmentStart = shaderData->find("#shader fragment");
		const unsigned int size = shaderData->size();

		if (vertexStart == std::string::npos || fragmentStart == std::string::npos)
		{
			printf("Shader data is invalid! Aborting");
			return {};
		}

		return 
		{
			(shaderData->substr(vertexStart + 15, fragmentStart - vertexStart - 15)),
			(shaderData->substr(fragmentStart + 17, size - fragmentStart - 17))
		};
	}

	unsigned int CompileShader(unsigned int type, const std::string& source)
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
			return 0;
		}

		return id;
	}

	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
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