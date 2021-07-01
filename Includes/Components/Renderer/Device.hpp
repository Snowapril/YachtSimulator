#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <vulkan/vulkan.h>
#include <Renderer/Resource.hpp>
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
    bool Initialize();
    //! Returns vulkan instance handle
    VkInstance GetInstance() const;
    //! Returns vulkan device handle
    VkDevice GetDevice() const;
    //! Returns vulkan physical device handle
    VkPhysicalDevice GetPhysicalDevice() const;
    //! Returns window surface handle
    VkSurfaceKHR GetSurface() const;

 protected:
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

 private:
    //! Initialize vulkan instance, physical device and logical device
    bool InitVulkan();
    //! Initialize command pool
    bool InitCommands();
};
};  // namespace Renderer

#endif  //! DEVICE_HPP