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

						const void* dataPtr = &(buffer.data[buffer_view.byteOffset + accessor.byteOffset]);
						const int elements_count = accessor.count;

						// MARK: the component type is very important, common is TINYGLTF_PARAMETER_TYPE_UNSIGNED_SHORT
						switch (accessor.componentType) 
						{
						case TINYGLTF_PARAMETER_TYPE_UNSIGNED_INT:
							{
							const uint32_t* buf = static_cast<const uint32_t*>(dataPtr);
								for (int i = 0; i < elements_count; i++)
								{
									Index local_index;
									local_index.index = buf[i];
									loaded_index_buffer.push_back(local_index);
								}
								break;
							}
						case TINYGLTF_PARAMETER_TYPE_UNSIGNED_SHORT: {
							const uint16_t* buf = static_cast<const uint16_t*>(dataPtr);
								for (int i = 0; i < elements_count; i++)
								{
									Index local_index;
									local_index.index = buf[i];
									loaded_index_buffer.push_back(local_index);
								}
								break;
							}
						case TINYGLTF_PARAMETER_TYPE_UNSIGNED_BYTE: {
							const uint8_t* buf = static_cast<const uint8_t*>(dataPtr);
								for (int i = 0; i < elements_count; i++)
								{
									Index local_index;
									local_index.index = buf[i];
									loaded_index_buffer.push_back(local_index);
								}
								break;
							}
						default:
							std::cerr << "Index component type " << accessor.componentType << " not supported!" << std::endl;
							return;
						}
					}
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