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