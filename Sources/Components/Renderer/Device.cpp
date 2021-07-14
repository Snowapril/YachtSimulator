#include <vkbootstrap/VkBootstrap.h>
#include <Components/Renderer/Device.hpp>
#include <Components/Renderer/Initializer.hpp>
#include <Components/Renderer/Utils.hpp>
#include <Components/Renderer/Window.hpp>

namespace Renderer
{
Device::Device(std::shared_ptr<Window> windowPtr)
{
    assert(Initialize(windowPtr));
}
Device::~Device()
{
    FlushDeletion();
}
bool Device::Initialize(std::shared_ptr<Window> windowPtr)
{
    _window = windowPtr;

    if (!InitVulkan())
        return false;

    if (!InitCommands())
        return false;

    return true;
}

bool Device::InitVulkan()
{
    vkb::InstanceBuilder builder;

    auto instRet =
        builder.set_app_name(_window->GetWindowTitle().c_str())
            .request_validation_layers(true)
            .require_api_version(VK_VERSION_1_0, VK_VERSION_1_1, VK_VERSION_1_2)
            .use_default_debug_messenger()
            .build();

    vkb::Instance vkbInstance = instRet.value();

    //! Store the instance
    _instance = vkbInstance.instance;
    //! Store the debug messenger
    _debugMessenger = vkbInstance.debug_messenger;

    //! Create window surface with just generated vulkan instance
    _window->CreateWindowSurface(_instance, &_surface);

    //! Use vkbootstrap to select GPU
    vkb::PhysicalDeviceSelector selector{ vkbInstance };
    vkb::PhysicalDevice physicalDevice =
        selector.set_minimum_version(VK_VERSION_1_0, VK_VERSION_1_1)
            .set_surface(_surface)
            .select()
            .value();

    //! Create the final vulkan device
    vkb::DeviceBuilder deviceBuilder{ physicalDevice };
    vkb::Device vkbDevice = deviceBuilder.build().value();

    //! Get the VkDevice handle
    _device = vkbDevice.device;
    _chosenGPU = physicalDevice.physical_device;

    //! Get graphics queue from vkbootstrap device
    _graphicsQueue = vkbDevice.get_queue(vkb::QueueType::graphics).value();
    _graphicsQueueFamily =
        vkbDevice.get_queue_index(vkb::QueueType::graphics).value();

    PushDeletionCall([=]() {
        vkDestroyDevice(_device, nullptr);
        vkDestroySurfaceKHR(_instance, _surface, nullptr);
        vkb::destroy_debug_utils_messenger(_instance, _debugMessenger, nullptr);
        vkDestroyInstance(_instance, nullptr);
    });

    return true;
}

bool Device::InitCommands()
{
    //! Create a command pool for commands submitted to the graphics queue
    //! The command pool will be one that can submit graphics commands
    //! We also want the pool to allow for resetting of individual command
    //! buffers
    VkCommandPoolCreateInfo commandPoolInfo =
        Initializer::CommandPoolCreateInfo(
            _graphicsQueueFamily,
            VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

    //! Create command pool and check result
    VK_CHECK_ERROR(
        vkCreateCommandPool(_device, &commandPoolInfo, nullptr, &_commandPool),
        "Failed to create command pool");

    //! Allocate the default command buffer that we will use for rendering
    //! Commands will be made from our _commandPool
    //! We will allocate only one command buffer.
    //! Command level is primary
    VkCommandBufferAllocateInfo commandBufferInfo =
        Initializer::CommandBufferAllocateInfo(_commandPool, 1,
                                               VK_COMMAND_BUFFER_LEVEL_PRIMARY);

    //! Allocate command buffer from the command pool and check result
    VK_CHECK_ERROR(vkAllocateCommandBuffers(_device, &commandBufferInfo,
                                            &_mainCommandBuffer),
                   "Failed to allocate main command buffer");

    PushDeletionCall([=]() {
        //! Destroying the command pool will destroy all command buffers from it
        vkDestroyCommandPool(_device, _commandPool, nullptr);
    });

    return true;
}

};  // namespace Renderer