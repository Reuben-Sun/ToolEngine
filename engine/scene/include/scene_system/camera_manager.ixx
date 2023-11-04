export module CameraManager;
import RenderCamera;

namespace ToolEngine
{
	// TODO: make a behaviour tree
	export struct CameraMoveState
	{
		int forward_count;
		int right_count;
	};

	export class CameraManager
	{
	public:
		CameraManager();
		~CameraManager();

		void tick(float delta_time);
		RenderCamera& getRenderCamera();
		CameraMoveState m_move_state;
	private:
		RenderCamera m_camera;
		float m_camera_speed = 10.0f;	// TODO: use speed curve
		// CameraDebugState
	};
}