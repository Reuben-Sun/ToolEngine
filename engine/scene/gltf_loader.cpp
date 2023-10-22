#include "gltf_loader.h"

namespace ToolEngine
{
	GltfLoader::GltfLoader(std::string model_path)
	{
		// MARK: maybe error
		std::string gltf_load_error;
		std::string gltf_load_warning;
		bool gltf_load_result = m_loader_context.LoadASCIIFromFile(&m_gltf_model, &gltf_load_error, &gltf_load_warning, model_path);

		if (gltf_load_result)
		{
			// load mesh
			std::vector<Index> triangle_strip_indices;
			for (auto& mesh : m_gltf_model.meshes)
			{
				for (auto& primitive : mesh.primitives)
				{
					if (primitive.attributes.find("POSITION") != primitive.attributes.end()) 
					{
						const int accessor_index = primitive.attributes.at("POSITION");
						const tinygltf::Accessor& accessor = m_gltf_model.accessors[accessor_index];
						const tinygltf::BufferView& buffer_view = m_gltf_model.bufferViews[accessor.bufferView];
						const tinygltf::Buffer& buffer = m_gltf_model.buffers[buffer_view.buffer];

						const float* data_ptr = reinterpret_cast<const float*>(&buffer.data[buffer_view.byteOffset + accessor.byteOffset]);
						const int pre_components_num = 3;
						const int elements_count = accessor.count;

						for (int i = 0; i < elements_count; i++) 
						{
							Vertex local_vertex;
							local_vertex.pos = glm::vec3(data_ptr[i * pre_components_num], data_ptr[i * pre_components_num + 1], data_ptr[i * pre_components_num + 2]);
							loaded_vertex_buffer.push_back(local_vertex);
						}
					}
					if (primitive.indices >= 0) 
					{
						const tinygltf::Accessor& accessor = m_gltf_model.accessors[primitive.indices];
						const tinygltf::BufferView& buffer_view = m_gltf_model.bufferViews[accessor.bufferView];
						const tinygltf::Buffer& buffer = m_gltf_model.buffers[buffer_view.buffer];

						const int* data_ptr = reinterpret_cast<const int*>(&buffer.data[buffer_view.byteOffset + accessor.byteOffset]);
						const int elements_count = accessor.count;

						for (int i = 0; i < elements_count; i++) 
						{
							Index local_index;
							local_index.index = data_ptr[i];
							triangle_strip_indices.push_back(local_index);
						}
					}
				}
			}
			// convert Triangle Strip to Triangle List
			for (int i = 2; i < triangle_strip_indices.size(); ++i) {
				if (i % 2 == 0) {
					loaded_index_buffer.push_back(triangle_strip_indices[i - 2]);
					loaded_index_buffer.push_back(triangle_strip_indices[i - 1]);
					loaded_index_buffer.push_back(triangle_strip_indices[i]);
				}
				else {
					loaded_index_buffer.push_back(triangle_strip_indices[i - 1]);
					loaded_index_buffer.push_back(triangle_strip_indices[i - 2]);
					loaded_index_buffer.push_back(triangle_strip_indices[i]);
				}
			}
			// TODO: load children
			// TODO: load transform, material, texture, skin, skeleton, animtion, blendshape
		}
	}
	GltfLoader::~GltfLoader()
	{
	}
}