#include <Components/Common/Macros.hpp>
#include <Components/Renderer/Device.hpp>
#include <Components/Renderer/Renderer.hpp>
#include <Components/Renderer/Window.hpp>
#include <cassert>

namespace Renderer
{
Renderer::Renderer(std::shared_ptr<Device> devicePtr,
                   std::shared_ptr<Window> windowPtr)
{
    assert(Initialize(devicePtr, windowPtr));
}
Renderer::~Renderer()
{
}
bool Renderer::Initialize(std::shared_ptr<Device> devicePtr,
                          std::shared_ptr<Window> windowPtr)
{
    //! Store devicePtr and windowPtr to member variables
    _device = devicePtr;
    _window = windowPtr;

    //! Create the initial swapchain
    RecreateSwapChain(_window->GetScreenSize());

    return true;
}
void Renderer::RecreateSwapChain(VkExtent2D extent)
{
    if (_swapChain)
    {
        auto oldSwapChain = std::move(_swapChain);
        _swapChain = std::make_unique<SwapChain>(_device, extent);
        if (oldSwapChain->GetImageFormat() != _swapChain->GetImageFormat())
        {
            LOG_ERROR << "New swapchain image format is not matched with "
                         "original one";
            abort();
        }
    }
    else
    {
        _swapChain = std::make_unique<SwapChain>(_device, extent);
    }
}
VkCommandBuffer Renderer::BeginFrame()
{
    //! Now that we are sure that the commands finished executing,
    //! we can safely reset the commandbuffer to begin recording again
    // vkResetCommandBuffer()
    //! TODO(snowapril) : complete this method
    return nullptr;
}
void Renderer::EndFrame()
{
}
void Renderer::BeginSwapChainRenderPass(VkCommandBuffer commandBuffer)
{
    UNUSED_VARIABLE(commandBuffer);
}
void Renderer::EndSwapChainRenderPass(VkCommandBuffer commandBuffer)
{
    UNUSED_VARIABLE(commandBuffer);
}
};  // namespace Renderer