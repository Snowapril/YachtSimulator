#include <Components/Common/Logger.hpp>
#include <Components/Common/Macros.hpp>
#include <Components/Renderer/Window.hpp>
#include <cassert>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Renderer
{
Window::Window()
{
    //! Do nothing
}

Window::Window(int width, int height, const std::string& title)
{
    assert(Initialize(width, height, title));
}

Window::~Window()
{
    //! Do nothing
}

bool Window::Initialize(int width, int height, const std::string& title)
{
    if (!glfwInit())
    {
        LOG_ERROR << "GLFW initialization failed";
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    _window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    //! Push glfw destroy call to resource deallocation stack
    PushDeletionCall([=]() { glfwDestroyWindow(_window); });

    //! Set also title member variable
    _title = title;

    return true;
}

bool Window::CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
{
    return VkCheckError(
        glfwCreateWindowSurface(instance, _window, nullptr, surface));
}

VkExtent2D Window::GetScreenSize() const
{
    return _screenSize;
}

std::string Window::GetWindowTitle() const
{
    return _title;
}

};  // namespace Renderer