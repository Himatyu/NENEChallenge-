#include "Mesh.h"
#include "../Rendering/Graphics.h"

namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Entity
		{
			Mesh::Mesh() :
				vertexSize(0),
				offset(0),
				vertexCont(0)
			{
			}
			Mesh::~Mesh()
			{
				//SAFE_RELEASE(pVertexBuffer);
			}
		}
	}
}