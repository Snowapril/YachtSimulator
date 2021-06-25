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

 protected:
    VkSwapchainKHR _swapChain;
    VkFormat _swapChainImageFormat;
    std::vector<VkImage> _swapChainImages;
    std::vector<VkImageView> _swapChainImageViews;

 private:
};
};  // namespace Renderer

#endif  //! SWAPCHAIN_HPP