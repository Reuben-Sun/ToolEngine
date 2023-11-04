#include <glm/glm.hpp>
import CameraManager;
import <string>;
import <math.h>;

namespace ToolEngine
{
	CameraManager::CameraManager()
	{
		m_move_state = { .dragging = false };
		m_camera.transform.position = glm::vec3(0.0f, 0.0f, 5.0f);
		m_camera.transform.rotation = glm::vec3(glm::radians(0.0f), glm::radians(0.0f), 0.0f);
		m_camera.transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
		m_camera.fov = glm::radians(45.0f);
		m_camera.aspect = 1280.0f / 720.0f;
		m_camera.near_plane = 0.1f;
		m_camera.far_plane = 100.0f;
		m_camera.left_handed = true;
		m_camera.view_size = 10;
	}

	CameraManager::~CameraManager()
	{
	}
	void CameraManager::tick(float delta_time)
	{
		if(m_move_state.forward_count > 0)
		{
			m_camera.transform.position -= m_camera.transform.getForward() * m_camera_speed * delta_time;
		}
		else if(m_move_state.forward_count < 0)
		{
			m_camera.transform.position += m_camera.transform.getForward() * m_camera_speed * delta_time;
		}
		if(m_move_state.right_count > 0)
		{
			m_camera.transform.position += m_camera.transform.getRight() * m_camera_speed * delta_time;
		}
		else if(m_move_state.right_count < 0)
		{
			m_camera.transform.position -= m_camera.transform.getRight() * m_camera_speed * delta_time;
		}
		
		m_camera.transform.rotation.y += m_move_state.delta_x * 0.0005;
		m_camera.transform.rotation.x += m_move_state.delta_y * 0.0005;
	}
	RenderCamera& CameraManager::getRenderCamera()
	{
		return m_camera;
	}
}