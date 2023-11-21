#include "include/common/macro.h"
export module Scene;

import GlobalContext;
import RenderScene;
import GltfLoader;
import CameraManager;

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