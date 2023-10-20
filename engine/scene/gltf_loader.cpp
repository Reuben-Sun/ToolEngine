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
			const tinygltf::Scene& scene = m_gltf_model.scenes[m_gltf_model.defaultScene > -1 ? m_gltf_model.defaultScene : 0];
			for (size_t i = 0; i < scene.nodes.size(); i++)
			{
				const tinygltf::Node& node = m_gltf_model.nodes[scene.nodes[i]];
				if (node.mesh > -1)
				{
					int vertex_start = 0;
					int final_index = 0;

					const tinygltf::Mesh& mesh = m_gltf_model.meshes[node.mesh];
					for (size_t j = 0; j < mesh.primitives.size(); j++)
					{
						const tinygltf::Primitive& primitive = mesh.primitives[j];
						if (primitive.indices > -1)
						{
							uint32_t index_count = 0;
							int pos_byte_stride;
							uint32_t vertex_count = 0;
							const float* position_buffer = nullptr;
							const float* uv_buffer = nullptr;
							int uv_byte_stride;
							const float* color_buffer = nullptr;
							int color_byte_stride;

							// position
							const tinygltf::Accessor& position_accessor = m_gltf_model.accessors[primitive.attributes.find("POSITION")->second];
							const tinygltf::BufferView& position_view = m_gltf_model.bufferViews[position_accessor.bufferView];
							position_buffer = reinterpret_cast<const float*>(&(m_gltf_model.buffers[position_view.buffer].data[position_accessor.byteOffset + position_view.byteOffset]));
							// TODO: pos AABB
							vertex_count = static_cast<uint32_t>(position_accessor.count);
							pos_byte_stride = position_accessor.ByteStride(position_view) ? (position_accessor.ByteStride(position_view) / sizeof(float)) : tinygltf::GetNumComponentsInType(TINYGLTF_TYPE_VEC3);

							// uv
							if (primitive.attributes.find("TEXCOORD_0") != primitive.attributes.end()) {
								const tinygltf::Accessor& uv_accessor = m_gltf_model.accessors[primitive.attributes.find("TEXCOORD_0")->second];
								const tinygltf::BufferView& uv_view = m_gltf_model.bufferViews[uv_accessor.bufferView];
								uv_buffer = reinterpret_cast<const float*>(&(m_gltf_model.buffers[uv_view.buffer].data[uv_accessor.byteOffset + uv_view.byteOffset]));
								uv_byte_stride = uv_accessor.ByteStride(uv_view) ? (uv_accessor.ByteStride(uv_view) / sizeof(float)) : tinygltf::GetNumComponentsInType(TINYGLTF_TYPE_VEC2);
							}
							// color
							if (primitive.attributes.find("COLOR_0") != primitive.attributes.end()) {
								const tinygltf::Accessor& color_accessor = m_gltf_model.accessors[primitive.attributes.find("COLOR_0")->second];
								const tinygltf::BufferView& color_view = m_gltf_model.bufferViews[color_accessor.bufferView];
								color_buffer = reinterpret_cast<const float*>(&(m_gltf_model.buffers[color_view.buffer].data[color_accessor.byteOffset + color_view.byteOffset]));
								color_byte_stride = color_accessor.ByteStride(color_view) ? (color_accessor.ByteStride(color_view) / sizeof(float)) : tinygltf::GetNumComponentsInType(TINYGLTF_TYPE_VEC3);
							}
							// index
							const tinygltf::Accessor& index_accessor = m_gltf_model.accessors[primitive.indices > -1 ? primitive.indices : 0];
							const tinygltf::BufferView& index_buffer_view = m_gltf_model.bufferViews[index_accessor.bufferView];
							const tinygltf::Buffer& buffer = m_gltf_model.buffers[index_buffer_view.buffer];
							index_count = static_cast<uint32_t>(index_accessor.count);
							const void* index_data_ptr = &(buffer.data[index_accessor.byteOffset + index_buffer_view.byteOffset]);

							// append index
							/*for (size_t i = 0; i < index_accessor.count; i++)
							{
								Index new_index;
								new_index.index = final_index;
								loaded_index_buffer.push_back(new_index);
								final_index++;
							}*/

							// append vertex
							vertex_start += vertex_count;
							for (int i = 0; i < vertex_count; i++)
							{
								Vertex new_vertex;
								new_vertex.pos = glm::vec3(position_buffer[i * pos_byte_stride], position_buffer[i * pos_byte_stride + 1], position_buffer[i * pos_byte_stride + 2]);
								new_vertex.texture_coord = glm::vec2(uv_buffer[i * uv_byte_stride], uv_buffer[i * uv_byte_stride + 1]);
								//new_vertex.color = glm::vec3(bufferColorSet[i * colorByteStride], bufferColorSet[i * colorByteStride + 1], bufferColorSet[i * colorByteStride + 2]);
								new_vertex.color = glm::vec3(1, 1, 1);
								loaded_vertex_buffer.push_back(new_vertex);
								Index new_index;
								new_index.index = loaded_index_buffer.size();
								loaded_index_buffer.push_back(new_index);
							}
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