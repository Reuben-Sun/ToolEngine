#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

export module RenderCamera;

import Transform;

namespace ToolEngine
{
	export struct RenderCamera
	{
		bool left_handed;
		float aspect;
		float view_size;
		float near_plane;
		float far_plane;
		float fov;
		Transform transform;

		glm::mat4 getProjectionMatrix();
		glm::mat4x4 getViewMatrix();
	};
}