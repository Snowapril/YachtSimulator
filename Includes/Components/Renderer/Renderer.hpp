#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <Components/Renderer/Resource.hpp>
#include <Components/Renderer/SwapChain.hpp>
#include <vulkan/vulkan.h>

namespace Renderer
{
class Device;
class Window;

class Renderer : public Resource
{
 public:
     //! Constructor with pre-generated Device and Window
    Renderer(std::shared_ptr<Device> devicePtr,
             std::shared_ptr<Window> windowPtr);
    //! Default destructor
    ~Renderer();
    //! Initialize the renderer with the given device and window
    bool Initialize(std::shared_ptr<Device> devicePtr,
                    std::shared_ptr<Window> windowPtr);
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
 protected:
    std::shared_ptr<Device> _device;
    std::shared_ptr<Window> _window;
    std::unique_ptr<SwapChain> _swapChain;
 private:
};
};  // namespace Renderer

#endif  //! RENDERER_HPP