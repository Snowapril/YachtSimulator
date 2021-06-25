#include <vkbootstrap/VkBootstrap.h>
#include <Renderer/Device.hpp>
#include <Renderer/Window.hpp>

namespace Renderer
{
Device::Device(std::shared_ptr<Window> windowPtr) : _window(windowPtr)
{
}
Device::~Device()
{
}
bool Device::Initialize()
{
    if (!InitVulkan())
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
    if (!_window->CreateWindowSurface(_instance, &_surface))
        return false;

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

    PushDeletionCall([=]() {
        vkDestroyDevice(_device, nullptr);
        vkDestroySurfaceKHR(_instance, _surface, nullptr);
        vkb::destroy_debug_utils_messenger(_instance, _debugMessenger, nullptr);
        vkDestroyInstance(_instance, nullptr);
    });

    return true;
}

VkInstance Device::GetInstance() const
{
    return _instance;
}

VkDevice Device::GetDevice() const
{
    return _device;
}

VkPhysicalDevice Device::GetPhysicalDevice() const
{
    return _chosenGPU;
}

VkSurfaceKHR Device::GetSurface() const
{
    return _surface;
}

};  // namespace Renderer