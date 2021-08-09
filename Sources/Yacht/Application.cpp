#include <Components/Common/Logger.hpp>
#include <Components/Renderer/Device.hpp>
#include <Components/Renderer/Renderer.hpp>
#include <Components/Renderer/Window.hpp>
#include <Yacht/Application.hpp>
#include <cassert>

Application::Application(int width, int height, const std::string& title)
{
    [[maybe_unused]] bool result = Initialize(width, height, title);
    assert(result == true);
}

Application::~Application()
{
    _renderer.reset();
    _device.reset();
    _window.reset();
}

bool Application::Initialize(int width, int height, const std::string& title)
{
    _window = std::make_shared<Renderer::Window>(width, height, title);
    _device = std::make_shared<Renderer::Device>(_window);
    _renderer = std::make_shared<Renderer::Renderer>(_window, _device);

    return true;
}

void Application::Run()
{
    while (!_window->WindowShouldClose())
    {
        _window->PollEvents();

        if (auto cmd = _renderer->BeginFrame())
        {
            _renderer->BeginSwapChainRenderPass(cmd);

            //! Do rendering stuffs here.
            //! 

            _renderer->EndSwapChainRenderPass(cmd);
            _renderer->EndFrame();
        }
    }
}