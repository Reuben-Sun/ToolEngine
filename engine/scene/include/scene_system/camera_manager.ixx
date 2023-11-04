export module CameraManager;
import RenderCamera;
import InputManager;

namespace ToolEngine
{
	export class CameraManager
	{
	public:
		CameraManager();
		~CameraManager();

		void tick(float delta_time, InputCommand command);
		RenderCamera& getRenderCamera();
		
	private:
		RenderCamera m_camera;
		float m_camera_speed = 100.0f;
		// CameraDebugState
	};
}