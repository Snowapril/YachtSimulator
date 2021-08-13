#include <Components/Renderer/Device.hpp>
#include <Components/Renderer/Pipeline.hpp>
#include <Components/Renderer/RenderSystem.hpp>
#include <cassert>

namespace Renderer
{
RenderSystem::RenderSystem(std::shared_ptr<Device> devicePtr,
                           VkRenderPass renderPass)
{
    [[maybe_unused]] bool result = Initialize(devicePtr, renderPass);
    assert(result == true);
}

RenderSystem::~RenderSystem()
{
    FlushDeletion();
}

bool RenderSystem::Initialize(std::shared_ptr<Device> devicePtr,
                              VkRenderPass renderPass)
{
    _device = devicePtr;

    if (!CreatePipelineLayout(renderPass))
        return false;

    if (!CreatePipeline())
        return false;

    return true;
}

bool RenderSystem::CreatePipelineLayout(VkRenderPass renderPass)
{
    (void)renderPass;
    return true;
}

bool RenderSystem::CreatePipeline()
{
    return true;
}
};  // namespace Renderer