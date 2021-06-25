#include <Common/Logger.hpp>
#include <Renderer/Window.hpp>
#include <cassert>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Renderer
{
Window::Window()
{
    //! Do nothing
}

Window::Window(int width, int height, const char* title)
{
    assert(Initialize(width, height, title));
}

Window::~Window()
{
    //! Do nothing
}

bool Window::Initialize(int width, int height, const char* title)
{
    if (!glfwInit())
    {
        LOG_ERROR << "GLFW initialization failed";
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    _window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    //! Push glfw destroy call to resource deallocation stack
    PushDeletionCall([=]() { glfwDestroyWindow(_window); });

    return true;
}

VkExtent2D Window::GetScreenSize() const
{
    return _screenSize;
}
};  // namespace Renderer