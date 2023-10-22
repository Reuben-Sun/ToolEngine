#pragma once

#include <vector>
#include "include/render/scene/render_scene.h"
#include "include/file/file_utils.h"
#include "gltf_loader.h"

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