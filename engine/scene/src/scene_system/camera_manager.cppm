#include <glm/glm.hpp>
import CameraManager;
import InputManager;
import <string>;

namespace ToolEngine
{
	CameraManager::CameraManager()
	{
		m_camera.transform.position = glm::vec3(0.0f, 0.0f, 5.0f);
		m_camera.transform.rotation = glm::vec3(glm::radians(0.0f), glm::radians(0.0f), 0.0f);
		m_camera.transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
		m_camera.fov = glm::radians(45.0f);
		m_camera.aspect = 1280.0f / 720.0f;
		m_camera.near_plane = 0.1f;
		m_camera.far_plane = 10.0f;
		m_camera.left_handed = true;
		m_camera.view_size = 10;
	}

	CameraManager::~CameraManager()
	{
	}
	void CameraManager::tick(float delta_time, InputCommand command)
	{
		if (command.detail == "Key W")
		{
			m_camera.transform.position.z -= m_camera_speed * delta_time;
		}
		else if (command.detail == "Key S")
		{
			m_camera.transform.position.z += m_camera_speed * delta_time;
		}
	}
	RenderCamera& CameraManager::getRenderCamera()
	{
		return m_camera;
	}
}