#pragma once

#include <string>
#include "Graphics/Mesh.h"

namespace Utils
{
	class ObjParser
	{
	public:
		std::string Name;
		std::vector<Graphics::Vertex> Vertices;
		std::vector<Graphics::Triangle> Triangles;
	public:
		ObjParser();
		~ObjParser();

		void Parse(const std::string& fileContent);
	private:
		void ExtractFaceVertex(const std::string& input, const std::vector<glm::vec3>& positions,
			const std::vector<glm::vec2>& textures, const std::vector<glm::vec3>& normals,
			std::vector<Graphics::Vertex>& vertices, unsigned int* index) const;
		void Split(const std::string& input, const char& delimiter, std::vector<std::string>* output) const;
		int ToInt(const std::string& stringValue) const;
		float ToFloat(const std::string& stringValue) const;
	};
}