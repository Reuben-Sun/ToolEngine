export module Scene;

import Global_Context;
import RenderScene;
import GltfLoader;
import CameraManager;
import <memory>;

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
		std::unique_ptr<CameraManager> m_camera_manager;
	};
}