export module Global_Context;

import LogManager;
import AssetManager;
import InputManager;
import BindingManager;
import <memory>;
import <string>;

namespace ToolEngine
{
	export class GlobalContext
	{
	public:
		void init(std::string exe_path);
		void clear();
		
		std::shared_ptr<AssetManager> m_asset_manager {nullptr};
		std::shared_ptr<InputManager> m_input_manager {nullptr};
		std::shared_ptr<LogManager> m_log_manager	{nullptr};
		std::shared_ptr<BindingManager> m_binding_manager{ nullptr };
	private:

	};

	export extern GlobalContext g_global_context;
}