#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace Utils
{
	void genTriGrid(int numVertRows, int numVertCols,
		float dx, float dz,
		const glm::vec3& center,
		std::vector<glm::vec3>& verts,
		std::vector<glm::u16>& indices);
}