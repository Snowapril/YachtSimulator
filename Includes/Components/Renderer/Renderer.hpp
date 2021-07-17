#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vulkan/vulkan.h>
#include <Components/Renderer/Resource.hpp>
#include <Components/Renderer/SwapChain.hpp>

namespace Renderer
{
class Device;
class Window;

class Renderer : public Resource
{
 public:
    //! Constructor with pre-generated Device and Window
    Renderer(std::shared_ptr<Window> windowPtr,
             std::shared_ptr<Device> devicePtr);

    //! Default destructor
    ~Renderer();

    //! Initialize the renderer with the given device and window
    bool Initialize(std::shared_ptr<Window> windowPtr,
                    std::shared_ptr<Device> devicePtr);

    //! Destroy and Recreate swapchain from the deviec
    void RecreateSwapChain(VkExtent2D extent);

    //! Begin the rendering frame
    VkCommandBuffer BeginFrame();

    //! Begin the swapchain renderpass
    void BeginSwapChainRenderPass(VkCommandBuffer commandBuffer);

    //! Finalize the rendering frame
    void EndFrame();

    //! Finalize the swapchain renderpass
    void EndSwapChainRenderPass(VkCommandBuffer commandBuffer);

 private:
    std::shared_ptr<Device> _device;
    std::shared_ptr<Window> _window;
    std::unique_ptr<SwapChain> _swapChain;
    VkClearColorValue _clearColor{ { 0.0f, 0.0f, 0.0f, 1.0f } };
    unsigned int _currentImageIndex{ 0 };

};
};  // namespace Renderer

#endif  //! RENDERER_HPP