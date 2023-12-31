#include <tiny_gltf.h>
#include "include/common/macro.h"

export module GltfLoader;

import Model;
import Index;
import Vertex;
import RenderScene;

namespace ToolEngine
{
	export class GltfLoader
	{
	public:
		GltfLoader(std::string model_path);
		~GltfLoader();

		std::vector<Index> loaded_index_buffer;
		std::vector<Vertex> loaded_vertex_buffer;

	private:
		tinygltf::Model m_gltf_model;
		tinygltf::TinyGLTF m_loader_context;
	};
}