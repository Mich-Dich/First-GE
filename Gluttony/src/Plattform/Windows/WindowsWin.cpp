#include "glpch.h"
#include "WindowsWin.h"

#include "Gluttony/Events/ApplicationEvent.h"
#include "Gluttony/Events/MouseEvent.h"
#include "Gluttony/Events/KeyEvent.h"

#include <glad/glad.h>

namespace Gluttony {

	static bool s_GLFWInitalised = false;

	static void GLFWErrorCallback(int error, const char* description) {

		GL_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props) {

		return new WindowsWin(props);
	}

	WindowsWin::WindowsWin(const WindowProps& props) {

		Init(props);
	}

	WindowsWin::~WindowsWin() {

		Shutdown();
	}

	void WindowsWin::Init(const WindowProps& props) {

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		GL_CORE_LOG("Created window: {0} Size: [X: {1}, Y: {2}]", props.Title, props.Width, props.Height);

		if (!s_GLFWInitalised) {

			int Success = glfwInit();
			GL_CORE_ASSERT(Success, "Could not initalize GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitalised = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GL_CORE_ASSERT(status, "Failes to initalize Glad");

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set Callback for RESIZE WINDOW
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
			});

		// Set Callback for CLOSE WINDOW
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
			});

		// Set Callback for KEY
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scanCode, int action, int mods) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {

			case GLFW_PRESS: {

				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}

			case GLFW_RELEASE: {

				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}

			case GLFW_REPEAT: {

				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
			}
			});

		// Set Callback for MOUSE MOVE
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)x, (float)x);
			data.EventCallback(event);

		});

		// Set Callback for MOUSE BUTTON
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {

				case GLFW_PRESS: {

					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}

				case GLFW_RELEASE: {

					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
			});


		// Set Callback for MOUSE SCROLL
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double x, double y) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float) x, (float) y);
			data.EventCallback(event);

		});

	}

	void WindowsWin::Shutdown() const {

		glfwDestroyWindow(m_Window);
	}

	void WindowsWin::OnUpdate() {

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWin::SetVSync(bool enabled) {

		if (enabled)
			glfwSwapInterval(0);
		else
			glfwSwapInterval(1);

		m_Data.VSync = enabled;
	}

	bool WindowsWin::IsVSync() const {

		return m_Data.VSync;
	}

}