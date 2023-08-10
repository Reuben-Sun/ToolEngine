#include "include/render/pipeline_state.h"

namespace ToolEngine
{
	void PipelineState::reset()
	{
		m_pipeline_layout = nullptr;
	}

	void PipelineState::clearDirty()
	{
		dirty = false;
	}

	void PipelineState::setPipelineLayout(PipelineLayout& pipeline_layout)
	{
		if (m_pipeline_layout != VK_NULL_HANDLE) 
		{
			if (pipeline_layout.getHandle() != m_pipeline_layout->getHandle())
			{
				m_pipeline_layout = &pipeline_layout;
				dirty = true;
			}
		}
		else
		{
			m_pipeline_layout = &pipeline_layout;
			dirty = true;
		}
	}

	void PipelineState::setRenderPass(const RenderPass& render_pass)
	{
		if (m_render_pass != VK_NULL_HANDLE)
		{
			if (render_pass.getHandle() != m_render_pass->getHandle())
			{
				m_render_pass = &render_pass;
				dirty = true;
			}
		}
		else
		{
			m_render_pass = &render_pass;
			dirty = true;
		}
	}
}