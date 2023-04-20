#pragma once

namespace dat
{
	class IState
	{
	public:
		IState() {}
		virtual ~IState() = default;

	public:
		virtual void onStateEntered() { };

		virtual void onKeyPressEvent(KEY_EVENT_RECORD record) { };

		virtual void onMousePressEvent(MOUSE_EVENT_RECORD record) { };
	};
}