#include "scene.h"
#include <tiny_gltf.h>

namespace ToolEngine
{
	Scene::Scene()
	{
		std::string model_path = FileUtils::getInstance().getModelsPath() + "Cube.gltf";
		std::unique_ptr<GltfLoader> loader = std::make_unique<GltfLoader>(model_path);
		Model model;
		model.indices = loader->loaded_index_buffer;
		model.vertices = loader->loaded_vertex_buffer;
		m_render_scene.models.push_back(model);
		RenderCamera camera;
		camera.transform.position = glm::vec3(0.0f, 1.0f, 0.0f);
		camera.transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		camera.transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
		camera.fov = glm::radians(45.0f);
		camera.aspect = 1280.0f / 720.0f;
		camera.near_plane = 0.0f;
		camera.far_plane = 20.0f;
		camera.left_handed = true;
		camera.view_size = 10;

		m_render_scene.render_camera = camera;
	}

	Scene::~Scene()
	{

	}

	void Scene::tick() 
	{

	}
	RenderScene& Scene::getRenderScene()
	{
		return m_render_scene;
	}
}