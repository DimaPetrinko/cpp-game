#pragma once

#include <fstream>
#include <sstream>
#include <tuple>
#include "Graphics/GL.h"

namespace Graphics::Shaders
{
	const unsigned int GetUniformLocation(unsigned int shader, const std::string& name)
	{
		GLCall(int location = glGetUniformLocation(shader, name.c_str()));
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
		GLCall(unsigned int id = glCreateShader(type));
		const char* src = source.c_str();
		GLCall(glShaderSource(id, 1, &src, nullptr));
		GLCall(glCompileShader(id));

		int result;
		GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE)
		{
			int length;
			GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
			char* message = (char*)alloca(length * sizeof(char));
			GLCall(glGetShaderInfoLog(id, length, &length, message));
			printf("Failed to compile shader! %s\n", message);
			GLCall(glDeleteShader(id));
			return 0;
		}

		return id;
	}

	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		GLCall(unsigned int program = glCreateProgram());
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
		GLCall(glAttachShader(program, vs));
		GLCall(glAttachShader(program, fs));
		GLCall(glLinkProgram(program));
		GLCall(glValidateProgram(program));

		GLCall(glDeleteShader(vs));
		GLCall(glDeleteShader(fs));

		return program;
	}
}