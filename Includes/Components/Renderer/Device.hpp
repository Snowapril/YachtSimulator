#ifndef DEVICE_HPP
#define DEVICE_HPP

#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1
#include <vulkan/vulkan.hpp>
#include <Components/Renderer/Resource.hpp>
#include <memory>

namespace Renderer
{
class Window;
class Device : public Resource
{
 public:
    //! Constructor with pre-defined window instance.
    Device(std::shared_ptr<Window> windowPtr);

    //! Default destructor
    ~Device();

    //! Initialize vulkan instance & device
    bool Initialize(std::shared_ptr<Window> windowPtr);

    //! Returns vulkan instance handle
    inline vk::Instance GetInstance() const
    {
        return _instance;
    }

    //! Returns vulkan device handle
    inline vk::Device GetDevice() const
    {
        return _device;
    }

    //! Returns vulkan physical device handle
    inline vk::PhysicalDevice GetPhysicalDevice() const
    {
        return _chosenGPU;
    }

    //! Returns window surface handle
    inline vk::SurfaceKHR GetSurface() const
    {
        return _surface;
    }

    //! Returns main command buffer
    inline vk::CommandBuffer GetCommandBuffer() const
    {
        return _mainCommandBuffer;
    }

    //! Returns main command buffer
    inline vk::Queue GetGraphicsQueue() const
    {
        return _graphicsQueue;
    }

 private:
    //! Initialize vulkan instance, physical device and logical device
    bool InitVulkan();

    //! Initialize command pool
    bool InitCommands();

    vk::Instance _instance;
    vk::DebugUtilsMessengerEXT _debugMessenger;
    vk::PhysicalDevice _chosenGPU;
    vk::Device _device;
    vk::SurfaceKHR _surface;
    vk::Queue _graphicsQueue;
    unsigned int _graphicsQueueFamily;

    vk::CommandPool _commandPool;
    vk::CommandBuffer _mainCommandBuffer;

    std::shared_ptr<Window> _window;
};
};  // namespace Renderer

#endif  //! DEVICE_HPP