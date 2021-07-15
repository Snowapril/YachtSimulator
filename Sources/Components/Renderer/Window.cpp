#include <Components/Common/Logger.hpp>
#include <Components/Renderer/Utils.hpp>
#include <Components/Renderer/Window.hpp>
#include <cassert>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Renderer
{
Window::Window(int width, int height, const std::string& title)
{
    bool initResult = Initialize(width, height, title);
    assert(initResult == true);
}

Window::~Window()
{
    FlushDeletion();
}

bool Window::Initialize(int width, int height, const std::string& title)
{
    _screenSize = { static_cast<unsigned int>(width),
                    static_cast<unsigned int>(height) };
    _title = title;

    if (!glfwInit())
    {
        LOG_ERROR << "GLFW initialization failed";
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    _window = glfwCreateWindow(static_cast<int>(_screenSize.width),
                               static_cast<int>(_screenSize.height),
                               _title.c_str(), nullptr, nullptr);

    //! Push glfw destroy call to resource deallocation stack
    PushDeletionCall([=]() { glfwDestroyWindow(_window); });

    return true;
}

void Window::CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
{
    VK_CHECK_ERROR(glfwCreateWindowSurface(instance, _window, nullptr, surface),
                   "Failed to create window surface");
}

bool Window::WindowShouldClose()
{
    return glfwWindowShouldClose(_window) == GLFW_TRUE;
}

void Window::PollEvents()
{
    glfwPollEvents();
}

};  // namespace Renderer