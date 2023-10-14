#pragma once

#include <GLFW/glfw3.h>
#include "Gluttony/Window.h"

namespace Gluttony {
	
	class WindowsWin : public Window{

	public:
		WindowsWin(const WindowProps& props);
		virtual ~WindowsWin();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Width; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	protected:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown() const;

	private:
		GLFWwindow* m_Window;

		struct WindowData {

			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}
