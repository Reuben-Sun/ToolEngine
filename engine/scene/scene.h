#pragma once

#include <vector>
#include "include/render/scene/render_scene.h"
#include "include/file/file_utils.h"

namespace ToolEngine
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		void tick();	
		RenderScene getRenderScene();
	private:
		// camera
		// std::vector<Light> 
		// std::vector<Model> 
	};
}