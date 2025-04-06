#pragma once

#include "WinterGE/Core.h"
#include "WinterGE/Events/Event.h"

namespace WinterGE
{
	class WGE_API Layer
	{
	public:
		Layer(const std::string& Name = "Layer");
		virtual ~Layer();

		virtual void OnAttach()
		{
		}

		virtual void OnDetach()
		{
		}

		virtual void OnUpdate()
		{
		}

		virtual void OnEvent(Event& Event)
		{
		}

		inline const std::string& GetName() const
		{
			return m_DebugName;
		}

		inline void SetEnabled(bool bEnabled)
		{
			m_bEnabled = bEnabled;
		}

		inline bool IsEnabled()
		{
			return m_bEnabled;
		}

	protected:
		std::string m_DebugName;
		bool m_bEnabled;
	};
}