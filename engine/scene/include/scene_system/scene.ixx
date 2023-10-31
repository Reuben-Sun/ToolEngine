export module Scene;

import Global_Context;
import RenderScene;
import GltfLoader;

namespace ToolEngine
{
	export class Scene
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