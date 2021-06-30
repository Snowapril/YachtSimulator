#ifndef SWAPCHAIN_HPP
#define SWAPCHAIN_HPP

#include <vulkan/vulkan.h>
#include <Renderer/Resource.hpp>
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
    //! Acquire next swapchain image index
    //! This call will make CPU threads blocked
    bool AcquireNextImage(unsigned int* swapChainIndex);
    //! Get swapchain image format
    VkFormat GetImageFormat();
    //! Get swapchain handle
    VkSwapchainKHR GetSwapChain();

 protected:
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

 private:
    //! Initialize default renderpass with only one color attachment
    bool InitDefaultRenderPass();
    //! Create framebuffer with default renderpass
    bool InitFramebuffers();
    //! Initialize several synchronization structures
    bool InitSyncStructures();
};
};  // namespace Renderer

#endif  //! SWAPCHAIN_HPP