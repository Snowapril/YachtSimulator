#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include <vulkan/vulkan.h>
#include <Components/Renderer/Resource.hpp>
#include <memory>

namespace Renderer
{
class Device;
class Pipeline;

class RenderSystem : public Resource
{
 public:
    //! Constructor with the given device and renderpass
    RenderSystem(std::shared_ptr<Device> devicePtr, VkRenderPass renderPass);

    //! Default destructor
    ~RenderSystem();

    //! Initialize the render system with the given device and renderpass
    bool Initialize(std::shared_ptr<Device> devicePtr, VkRenderPass renderPass);

 private:
    bool CreatePipelineLayout(VkRenderPass renderPass);
    bool CreatePipeline();

    std::shared_ptr<Device> _device;
    std::unique_ptr<Pipeline> _pipeline;
    VkPipelineLayout _pipelineLayout;
};
};  // namespace Renderer

#endif  //! RENDER_SYSTEM_HPP