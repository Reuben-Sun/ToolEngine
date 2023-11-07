#include "include/common/macro.h"
#include <glm/glm.hpp>
import Scene;
import Global_Context;
import RenderScene;
import GltfLoader;
import Model;
import Index;
import Vertex;
import RenderCamera;
import InputManager;
import AssetManager;
import CameraManager;
import Timer;
import <string>;
import <memory>;
import <vector>;
import <regex>;

namespace ToolEngine
{
	Scene::Scene()
	{
		m_camera_manager = std::make_unique<CameraManager>();
		std::string model_path = g_global_context.m_asset_manager->getModelsPath() + "Cube.gltf";
		std::unique_ptr<GltfLoader> loader = std::make_unique<GltfLoader>(model_path);
		Model model;
		model.indices = loader->loaded_index_buffer;
		model.vertices = loader->loaded_vertex_buffer;
		m_render_scene.models.push_back(model);
		std::vector<Index> plane_index_buffer = { {0}, {1}, {2}, {2}, {3}, {0} };
		const std::vector<Vertex> plane_vertex_buffer =
		{
			{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
			{{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
			{{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
			{{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
		};
		Model plane_model;
		plane_model.indices = plane_index_buffer;
		plane_model.vertices = plane_vertex_buffer;
		m_render_scene.models.push_back(plane_model);
	}

	Scene::~Scene()
	{

	}

	void Scene::tick() 
	{
		float delta_time = Timer::DeltaTime();
		
		auto command = g_global_context.m_input_manager->pop();
		if (command.type != CommandType::NONE)
		{
			if (command.type == CommandType::MOVE)
			{
				if (command.detail == "Key W")
				{
					m_camera_manager->m_move_state.forward_count++;
				}
				else if (command.detail == "Key S")
				{
					m_camera_manager->m_move_state.forward_count--;
				}
				else if (command.detail == "Key A")
				{
					m_camera_manager->m_move_state.right_count--;
				}
				else if (command.detail == "Key D")
				{
					m_camera_manager->m_move_state.right_count++;
				}
				LOG_INFO("command: {}", command.detail);
			}
			else if (command.type == CommandType::END_MOVE)
			{
				if (command.detail == "Key W")
				{
					m_camera_manager->m_move_state.forward_count--;
				}
				else if (command.detail == "Key S")
				{
					m_camera_manager->m_move_state.forward_count++;
				}
				else if (command.detail == "Key A")
				{
					m_camera_manager->m_move_state.right_count++;
				}
				else if (command.detail == "Key D")
				{
					m_camera_manager->m_move_state.right_count--;
				}
			}
			if (command.type == CommandType::CLICK)
			{
				LOG_INFO("command: {}", command.detail);
				if(command.detail == "Left Mouse Down")
				{
					m_camera_manager->m_move_state.dragging = true;
				}
				else if (command.detail == "Left Mouse Up")
				{
					m_camera_manager->m_move_state.dragging = false;
				}
			}
			if (m_camera_manager->m_move_state.dragging)
			{
				if (command.type == CommandType::DRAG)
				{
					std::regex pattern("x:([-]?\\d+) y:([-]?\\d+)");
					std::smatch match;
					if (std::regex_search(command.detail, match, pattern))
					{
						double x = std::stof(match[1].str());
						double y = std::stof(match[2].str());
						m_camera_manager->m_move_state.delta_x = x;
						m_camera_manager->m_move_state.delta_y = y;
					}
				}
			}
			else 
			{
				m_camera_manager->m_move_state.delta_x = 0;
				m_camera_manager->m_move_state.delta_y = 0;
			}
		}
		m_camera_manager->tick(delta_time);
	}
	RenderScene& Scene::getRenderScene()
	{
		m_render_scene.render_camera = m_camera_manager->getRenderCamera();
		return m_render_scene;
	}
}