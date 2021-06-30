#include <vkbootstrap/VkBootstrap.h>
#include <Common/Macros.hpp>
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
    //! Store devicePtr and extent to member variables
    _device = devicePtr;
    _extent = extent;

    vkb::SwapchainBuilder builder{ _device->GetPhysicalDevice(),
                                   _device->GetDevice(),
                                   _device->GetSurface() };

    vkb::Swapchain vkbSwapChain =
        builder.use_default_format_selection()
            .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
            .set_desired_extent(_extent.width, _extent.height)
            .build()
            .value();

    //! Store swapchain and its related images
    _swapChain = vkbSwapChain.swapchain;
    _swapChainImages = vkbSwapChain.get_images().value();
    _swapChainImageViews = vkbSwapChain.get_image_views().value();
    _swapChainImageFormat = vkbSwapChain.image_format;

    PushDeletionCall([=]() {
        vkDestroySwapchainKHR(_device->GetDevice(), _swapChain, nullptr);
        for (auto& image : _swapChainImages)
            vkDestroyImage(_device->GetDevice(), image, nullptr);
        for (auto& imageView : _swapChainImageViews)
            vkDestroyImageView(_device->GetDevice(), imageView, nullptr);
    });

    if (!InitDefaultRenderPass())
        return false;

    if (!InitFramebuffers())
        return false;

    //! Initialize the vulkan synchronization structures
    if (!InitSyncStructures())
        return false;

    return true;
}

bool SwapChain::InitDefaultRenderPass()
{
    //! The renderpass will use this color attachment
    VkAttachmentDescription colorAttachment = {};
    //! The attachment will have the format needed by the swapchain
    colorAttachment.format = _swapChainImageFormat;
    //! 1 sample, we dont use MSAA at now. TODO(snowapril) : MSAA
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    //! We clear when this attachment is loaded
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    //! We keep the attachment stored when the renderpass ends
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    //! We dont care about stencil
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    //! We dont know or care about the starting layout of the attachment
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    //! After the renderpass ends, the image has to be on a layout ready for
    //! display
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentRef = {};
    //! attachment number will index into the pAttachments array in the parent
    //! renderpass itself
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    //! We are going to create 1 subpass, which is the minimum you can do
    VkSubpassDescription subpassDesc = {};
    subpassDesc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpassDesc.colorAttachmentCount = 1;
    subpassDesc.pColorAttachments = &colorAttachmentRef;

    VkRenderPassCreateInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    //! Connect the color attachment to the info
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    //! Connect the subpass to the info
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpassDesc;

    if (!VkCheckError(vkCreateRenderPass(_device->GetDevice(), &renderPassInfo,
                                         nullptr, &_renderPass)))
        return false;

    PushDeletionCall([=]() {
        vkDestroyRenderPass(_device->GetDevice(), _renderPass, nullptr);
    });

    return true;
}

bool SwapChain::InitFramebuffers()
{
    //! Create the framebuffer for the swapchain images.
    //! This will connect the renderpass to the images for rendering
    VkFramebufferCreateInfo framebufferInfo = {};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.pNext = nullptr;

    framebufferInfo.renderPass = _renderPass;
    framebufferInfo.attachmentCount = 1;
    framebufferInfo.width = _extent.width;
    framebufferInfo.height = _extent.height;
    framebufferInfo.layers = 1;

    //! Grap how many images we have in the swapchain
    _framebuffers.resize(_swapChainImages.size());

    //! Create framebuffers for each of the swapchain image views
    for (size_t i = 0; i < _swapChainImages.size(); ++i)
    {
        framebufferInfo.pAttachments = &_swapChainImageViews[i];
        if (!VkCheckError(vkCreateFramebuffer(_device->GetDevice(),
                                              &framebufferInfo, nullptr,
                                              &_framebuffers[i])))
            return false;

        PushDeletionCall([=]() {
            vkDestroyFramebuffer(_device->GetDevice(), _framebuffers[i],
                                 nullptr);
        });
    }

    return true;
}

bool SwapChain::InitSyncStructures()
{
    //! Create synchronization structures
    VkFenceCreateInfo fenceInfo;
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.pNext = nullptr;
    //! We want to create the fence with the create signaled flag,
    //! so we can wait on it before using it
    //! on a GPU command(for the first frame)
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    if (!VkCheckError(vkCreateFence(_device->GetDevice(), &fenceInfo, nullptr,
                                    &_renderFence)))
        return false;

    //! For the semaphores, we don't need any flags
    VkSemaphoreCreateInfo semaphoreInfo;
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaphoreInfo.pNext = nullptr;
    semaphoreInfo.flags = 0;

    if (!VkCheckError(vkCreateSemaphore(_device->GetDevice(), &semaphoreInfo,
                                        nullptr, &_presentSemaphore)))
        return false;

    if (!VkCheckError(vkCreateSemaphore(_device->GetDevice(), &semaphoreInfo,
                                        nullptr, &_renderSemaphore)))
        return false;

    //! Push fence & semaphore deletion call
    PushDeletionCall([=]() {
        vkDeviceWaitIdle(_device->GetDevice());
        vkDestroyFence(_device->GetDevice(), _renderFence, nullptr);
        vkDestroySemaphore(_device->GetDevice(), _presentSemaphore, nullptr);
        vkDestroySemaphore(_device->GetDevice(), _renderSemaphore, nullptr);
    });

    return true;
}

bool SwapChain::AcquireNextImage(unsigned int* swapChainIndex)
{
    //! Get the VkDevice
    VkDevice device = _device->GetDevice();
    //! Wait until the GPU has finished rendering the last frame.
    //! Timeout of 1 second
    if (!VkCheckError(
            vkWaitForFences(device, 1, &_renderFence, true, 1000000000)))
        return false;
    if (!VkCheckError(vkResetFences(device, 1, &_renderFence)))
        return false;

    if (!VkCheckError(vkAcquireNextImageKHR(device, _swapChain, 1000000000,
                                            _presentSemaphore, nullptr,
                                            swapChainIndex)))
        return false;

    return true;
}

VkFormat SwapChain::GetImageFormat()
{
    return _swapChainImageFormat;
}

VkSwapchainKHR SwapChain::GetSwapChain()
{
    return _swapChain;
}
};  // namespace Renderer