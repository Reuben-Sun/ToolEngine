#pragma once

#include <vector>
#include "include/render/scene/render_scene.h"
#include "include/asset_pipeline/gltf_loader.h"
#include "include/global/global_context.h"

namespace ToolEngine
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		void tick();	
		RenderScene& getRenderScene();
	private:
		RenderScene m_render_scene;
		// camera
		// std::vector<Light> 
		// std::vector<Model> 
	};
}