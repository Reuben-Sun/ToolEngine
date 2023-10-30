import Index;
import Vertex;

export module Model;

import <vector>;

namespace ToolEngine
{
	export struct Model
	{
		std::vector<Vertex> vertices;
		std::vector<Index> indices;
	};
}