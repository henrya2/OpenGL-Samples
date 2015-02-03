#include "Utils.h"

namespace Utils
{
	void genTriGrid(int numVertRows, int numVertCols, float dx, float dz, const glm::vec3& center, std::vector<glm::vec3>& verts, std::vector<glm::u16>& indices)
	{
		int numVertices = numVertRows * numVertCols;
		int numCellRows = numVertRows - 1;
		int numCellCols = numVertCols - 1;

		int numTris = numCellRows * numVertCols * 2;

		float width = numCellCols * dx;
		float depth = numCellRows * dz;

		verts.resize(numVertices);

		float xOffset = -width * 0.5f;
		float zOffset = -depth * 0.5f;

		int k = 0;
		for (float i = 0; i < numVertRows; ++i)
		{
			for (float j = 0; j < numVertCols; ++j)
			{
				verts[k].x = j * dx + xOffset;
				verts[k].z = i * dz + zOffset;
				verts[k].y = 0.0f;

				verts[k] += center;

				k++;
			}
		}

		indices.resize(numTris * 3);

		k = 0;
		for (glm::u16 i = 0; i < (glm::u16)numCellRows; ++i)
		{
			for (glm::u16 j = 0; j < (glm::u16)numCellCols; ++j)
			{
				indices[k] = i * numVertCols + j;
				indices[k + 1] = (i + 1) * numVertCols + j;
				indices[k + 2] = i * numCellCols + j + 1;

				indices[k + 3] = i * numCellCols + j + 1;
				indices[k + 4] = (i + 1) * numVertCols + j;
				indices[k + 5] = (i + 1) * numVertCols + j + 1;

				k += 6;
			}
		}
	}
}
