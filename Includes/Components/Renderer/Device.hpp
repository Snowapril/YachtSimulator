#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <vulkan/vulkan.h>
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
    inline VkInstance GetInstance() const
    {
        return _instance;
    }

    //! Returns vulkan device handle
    inline VkDevice GetDevice() const
    {
        return _device;
    }

    //! Returns vulkan physical device handle
    inline VkPhysicalDevice GetPhysicalDevice() const
    {
        return _chosenGPU;
    }

    //! Returns window surface handle
    inline VkSurfaceKHR GetSurface() const
    {
        return _surface;
    }

    //! Returns main command buffer
    inline VkCommandBuffer GetCommandBuffer() const
    {
        return _mainCommandBuffer;
    }

    //! Returns main command buffer
    inline VkQueue GetGraphicsQueue() const
    {
        return _graphicsQueue;
    }

 private:
    //! Initialize vulkan instance, physical device and logical device
    bool InitVulkan();

    //! Initialize command pool
    bool InitCommands();

    VkInstance _instance;
    VkDebugUtilsMessengerEXT _debugMessenger;
    VkPhysicalDevice _chosenGPU;
    VkDevice _device;
    VkSurfaceKHR _surface;
    VkQueue _graphicsQueue;
    unsigned int _graphicsQueueFamily;

    VkCommandPool _commandPool;
    VkCommandBuffer _mainCommandBuffer;

    std::shared_ptr<Window> _window;
};
};  // namespace Renderer

#endif  //! DEVICE_HPP