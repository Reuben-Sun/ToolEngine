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
					// vertex
					int vertex_count = 0;
					std::vector<Vertex> local_vertex_buffer;
					// position
					if (primitive.attributes.find("POSITION") != primitive.attributes.end()) 
					{
						const int accessor_index = primitive.attributes.at("POSITION");
						const tinygltf::Accessor& accessor = m_gltf_model.accessors[accessor_index];
						const tinygltf::BufferView& buffer_view = m_gltf_model.bufferViews[accessor.bufferView];
						const tinygltf::Buffer& buffer = m_gltf_model.buffers[buffer_view.buffer];
						const float* data_ptr = reinterpret_cast<const float*>(&buffer.data[buffer_view.byteOffset + accessor.byteOffset]);
						const int position_byte_stride = 3;

						vertex_count = accessor.count;

						for (int i = 0; i < vertex_count; i++)
						{
							Vertex local_vertex;
							local_vertex.pos = glm::vec3(data_ptr[i * position_byte_stride], data_ptr[i * position_byte_stride + 1], data_ptr[i * position_byte_stride + 2]);
							local_vertex_buffer.push_back(local_vertex);
						}
					}
					// uv
					if (primitive.attributes.find("TEXCOORD_0") != primitive.attributes.end()) 
					{
						const int accessor_index = primitive.attributes.at("TEXCOORD_0");
						const tinygltf::Accessor& accessor = m_gltf_model.accessors[accessor_index];
						const tinygltf::BufferView& buffer_view = m_gltf_model.bufferViews[accessor.bufferView];
						const tinygltf::Buffer& buffer = m_gltf_model.buffers[buffer_view.buffer];
						const float* data_ptr = reinterpret_cast<const float*>(&buffer.data[buffer_view.byteOffset + accessor.byteOffset]);
						const int uv_byte_stride = accessor.ByteStride(buffer_view) ? (accessor.ByteStride(buffer_view) / sizeof(float)) : tinygltf::GetNumComponentsInType(TINYGLTF_TYPE_VEC2);
						for (int i = 0; i < vertex_count; i++)
						{
							local_vertex_buffer[i].texture_coord = glm::vec2(data_ptr[i * uv_byte_stride], data_ptr[i * uv_byte_stride + 1]);
						}
					}
					// append local vertex buffer to loaded vertex buffer
					for (int i = 0; i < vertex_count; i++)
					{
						loaded_vertex_buffer.push_back(local_vertex_buffer[i]);
					}
					// index
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