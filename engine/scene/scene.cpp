#include "scene.h"
#include <tiny_gltf.h>

namespace ToolEngine
{
	Scene::Scene()
	{
		Model model;
		model.indices =
		{
			{0}, {1}, {2}, {2}, {3}, {0},
			{4}, {5}, {6}, {6}, {7}, {4}
		};
		model.vertices =
		{
			{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
			{{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
			{{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
			{{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

			{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
			{{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
			{{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
			{{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
		};
		Model model2;
		model2.indices =
		{
			{0}, {1}, {2}, {2}, {3}, {0}
		};
		model2.vertices =
		{
			{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
			{{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
			{{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
			{{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
		};
		m_render_scene.models = std::vector<Model>();
		m_render_scene.models.push_back(model);
		m_render_scene.models.push_back(model2);

		// TODO: load model
		tinygltf::Model gltf_model;
		tinygltf::TinyGLTF gltf_loader_context;
		std::string gltf_load_error;
		std::string gltf_load_warning;
		std::string model_path = FileUtils::getInstance().getModelsPath() + "SphereWithCube.gltf";
		bool gltf_load_result = gltf_loader_context.LoadASCIIFromFile(&gltf_model, &gltf_load_error, &gltf_load_warning, model_path);

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