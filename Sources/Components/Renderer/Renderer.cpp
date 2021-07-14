#include <Components/Renderer/Device.hpp>
#include <Components/Renderer/Renderer.hpp>
#include <Components/Renderer/Utils.hpp>
#include <Components/Renderer/Window.hpp>
#include <cassert>

namespace Renderer
{
Renderer::Renderer(std::shared_ptr<Window> windowPtr,
                   std::shared_ptr<Device> devicePtr)
{
    assert(Initialize(windowPtr, devicePtr));
}
Renderer::~Renderer()
{
    FlushDeletion();
}
bool Renderer::Initialize(std::shared_ptr<Window> windowPtr,
                          std::shared_ptr<Device> devicePtr)
{
    _window = windowPtr;
    _device = devicePtr;

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
            std::abort();
        }
    }
    else
    {
        _swapChain = std::make_unique<SwapChain>(_device, extent);
    }
}
VkCommandBuffer Renderer::BeginFrame()
{
    auto result = _swapChain->AcquireNextImage(&_currentImageIndex);
    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        RecreateSwapChain(_window->GetScreenSize());
        return nullptr;
    }
    VK_CHECK_ERROR(result, "Failed to acquire swap chain image");
    //! Get current frame command buffer from the device
    auto cmd = _device->GetCommandBuffer();
    //! Now that we are sure that the commands finished executing,
    //! we can safely reset the commandbuffer to begin recording again
    VK_CHECK_ERROR(vkResetCommandBuffer(cmd, 0),
                   "Failed to reset command buffer");

    //! Begin the command buffer recording. We will use this command buffer
    //! exactly once, so we want to let vulkan know that
    VkCommandBufferBeginInfo cmdBeginInfo = {};
    cmdBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cmdBeginInfo.pNext = nullptr;
    cmdBeginInfo.pInheritanceInfo = nullptr;
    cmdBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    VK_CHECK_ERROR(vkResetCommandBuffer(cmd, 0),
                   "Failed to reset command buffer");

    VK_CHECK_ERROR(vkBeginCommandBuffer(cmd, &cmdBeginInfo),
                   "Failed to reset command buffer")
    return cmd;
}
void Renderer::EndFrame()
{
    //! Get current frame command buffer from the device
    auto cmd = _device->GetCommandBuffer();
    VK_CHECK_ERROR(vkEndCommandBuffer(cmd),
                   "Failed to complete command buffer recording");

    VK_CHECK_ERROR(_swapChain->SubmitCommandBuffer(cmd, _currentImageIndex),
                   "Failed to submit command buffer");
}
void Renderer::BeginSwapChainRenderPass(VkCommandBuffer commandBuffer)
{
    static int testFrame = 0;
    _clearColor.float32[2] = std::abs(std::sin(testFrame++ / 120.0f));

    VkClearValue clearValue = { _clearColor };

    //! Start the main renderpass
    //! We will use the clear color from above and the framebuffer of the index
    //! the swapchain gave us
    VkRenderPassBeginInfo renderPassBeginInfo = {};
    renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassBeginInfo.pNext = nullptr;
    renderPassBeginInfo.clearValueCount = 1;
    renderPassBeginInfo.pClearValues = &clearValue;
    renderPassBeginInfo.renderPass = _swapChain->GetRenderPass();
    renderPassBeginInfo.renderArea.offset = { 0, 0 };
    renderPassBeginInfo.renderArea.extent = _window->GetScreenSize();

    if (VkFramebuffer currentFramebuffer =
            _swapChain->GetFramebuffer(_currentImageIndex))
        renderPassBeginInfo.framebuffer = currentFramebuffer;
    else
    {
        LOG_ERROR << "Failed to get correct framebuffer from the swapchain";
        std::abort();
    }

    vkCmdBeginRenderPass(commandBuffer, &renderPassBeginInfo,
                         VK_SUBPASS_CONTENTS_INLINE);
}
void Renderer::EndSwapChainRenderPass(VkCommandBuffer commandBuffer)
{
    vkCmdEndRenderPass(commandBuffer);
}
};  // namespace Renderer