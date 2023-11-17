#include "include/common/macro.h"
export module Model;
import Index;
import Vertex;
import Transform;

namespace ToolEngine
{
	export struct Model
	{
		std::vector<Vertex> vertices;
		std::vector<Index> indices;
		Transform transform;
		// material
		// aabb
	};
}