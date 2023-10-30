export module RenderScene;
import <vector>;

import Model;
import RenderCamera;

namespace ToolEngine
{
	export struct RenderScene
	{
		std::vector<Model> models;
		RenderCamera render_camera;
	};
}