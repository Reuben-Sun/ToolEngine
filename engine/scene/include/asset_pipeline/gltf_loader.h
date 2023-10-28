#pragma once

#include <tiny_gltf.h>
#include <string>
#include <vector>
#include <iostream>
#include "include/render/scene/render_scene.h"
#include "include/common/macro.h"

namespace ToolEngine
{
	class GltfLoader
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