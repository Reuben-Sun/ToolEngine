export module Model;
import Index;
import Vertex;
import <vector>;

namespace ToolEngine
{
	export struct Model
	{
		std::vector<Vertex> vertices;
		std::vector<Index> indices;
	};
}