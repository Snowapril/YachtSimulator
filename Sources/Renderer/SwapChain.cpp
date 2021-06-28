#include <vkbootstrap/VkBootstrap.h>
#include <Renderer/Device.hpp>
#include <Renderer/SwapChain.hpp>

namespace Renderer
{
SwapChain::SwapChain(std::shared_ptr<Device> devicePtr, VkExtent2D extent)
{
    assert(Initialize(devicePtr, extent));
}

SwapChain::~SwapChain()
{
    //! Do nothing
}

bool SwapChain::Initialize(std::shared_ptr<Device> devicePtr, VkExtent2D extent)
{
    vkb::SwapchainBuilder builder{ devicePtr->GetPhysicalDevice(),
                                   devicePtr->GetDevice(),
                                   devicePtr->GetSurface() };

    vkb::Swapchain vkbSwapChain =
        builder.use_default_format_selection()
            .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
            .set_desired_extent(extent.width, extent.height)
            .build()
            .value();

    //! Store swapchain and its related images
    _swapChain = vkbSwapChain.swapchain;
    _swapChainImages = vkbSwapChain.get_images().value();
    _swapChainImageViews = vkbSwapChain.get_image_views().value();
    _swapChainImageFormat = vkbSwapChain.image_format;

    PushDeletionCall([=]() {
        vkDestroySwapchainKHR(devicePtr->GetDevice(), _swapChain, nullptr);
        for (auto& image : _swapChainImages)
            vkDestroyImage(devicePtr->GetDevice(), image, nullptr);
        for (auto& imageView : _swapChainImageViews)
            vkDestroyImageView(devicePtr->GetDevice(), imageView, nullptr);
    });

    return true;
}

};  // namespace Renderer