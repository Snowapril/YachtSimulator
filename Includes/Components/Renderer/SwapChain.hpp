#ifndef SWAPCHAIN_HPP
#define SWAPCHAIN_HPP

#include <vulkan/vulkan.h>
#include <Components/Common/Logger.hpp>
#include <Components/Renderer/Resource.hpp>
#include <memory>
#include <vector>

namespace Renderer
{
class Device;
class SwapChain : public Resource
{
 public:
    //! Default constructor
    SwapChain(std::shared_ptr<Device> devicePtr, VkExtent2D extent);

    //! Default destructor
    ~SwapChain();

    //! Initialize swapchain
    bool Initialize(std::shared_ptr<Device> devicePtr, VkExtent2D extent);

    //! Submit given command buffer to graphics queue and
    //! present rendered image to swapchain
    VkResult SubmitCommandBuffer(VkCommandBuffer cmd, unsigned int imageIndex);

    //! Acquire next swapchain image index
    //! This call will make CPU threads blocked
    VkResult AcquireNextImage(unsigned int* swapChainIndex);

    //! Get swapchain image format
    inline VkFormat GetImageFormat() const
    {
        return _swapChainImageFormat;
    }

    //! Get swapchain handle
    inline VkSwapchainKHR GetSwapChain() const
    {
        return _swapChain;
    }

    //! Get currnet render pass
    inline VkRenderPass GetRenderPass() const
    {
        return _renderPass;
    }

    //! Get framebuffer with given index
    inline VkFramebuffer GetFramebuffer(unsigned int index) const
    {
        if (_framebuffers.size() <= index)
        {
            LOG_ERROR << "Out of range in framebuffers";
            return nullptr;
        }
        return _framebuffers[index];
    }

 private:
    //! Initialize default renderpass with only one color attachment
    bool InitDefaultRenderPass();

    //! Create framebuffer with default renderpass
    bool InitFramebuffers();

    //! Initialize several synchronization structures
    bool InitSyncStructures();

    VkSwapchainKHR _swapChain;
    VkFormat _swapChainImageFormat;
    VkRenderPass _renderPass;
    std::vector<VkFramebuffer> _framebuffers;
    std::vector<VkImage> _swapChainImages;
    std::vector<VkImageView> _swapChainImageViews;
    std::shared_ptr<Device> _device;
    VkExtent2D _extent;
    VkSemaphore _presentSemaphore, _renderSemaphore;
    VkFence _renderFence;
};
};  // namespace Renderer

#endif  //! SWAPCHAIN_HPP