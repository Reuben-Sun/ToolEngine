#pragma once

#include <vector>
#include "include/asset_pipeline/gltf_loader.h"

import Global_Context;
import RenderScene;

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