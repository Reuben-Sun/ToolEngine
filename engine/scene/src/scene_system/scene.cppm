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
		RenderCamera camera;
		camera.transform.position = glm::vec3(0.0f, 0.0f, 5.0f);
		camera.transform.rotation = glm::vec3(glm::radians(0.0f), glm::radians(0.0f), 0.0f);
		camera.transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
		camera.fov = glm::radians(45.0f);
		camera.aspect = 1280.0f / 720.0f;
		camera.near_plane = 0.1f;
		camera.far_plane = 10.0f;
		camera.left_handed = true;
		camera.view_size = 10;

		m_render_scene.render_camera = camera;
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
			LOG_INFO("command: {}", command.detail);
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
		}
		m_camera_manager->tick(delta_time);
	}
	RenderScene& Scene::getRenderScene()
	{
		m_render_scene.render_camera = m_camera_manager->getRenderCamera();
		return m_render_scene;
	}
}