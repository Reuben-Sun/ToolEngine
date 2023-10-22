#pragma once

#include <glm/glm.hpp>
#include "include/math/transform.h"

namespace ToolEngine
{
	struct RenderCamera
	{
		bool left_handed;
		float aspect;
		float view_size;
		float near_plane;
		float far_plane;
		float fov;
		Transform transform;

		glm::mat4x4 getProjectionMatrix();
		glm::mat4x4 getViewMatrix();
	};
}