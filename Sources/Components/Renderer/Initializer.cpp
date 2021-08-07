#include <Components/Renderer/Initializer.hpp>

namespace Renderer
{
namespace Initializer
{
VkCommandPoolCreateInfo CommandPoolCreateInfo(uint32_t queueFamilyIndex,
                                              VkCommandPoolCreateFlags flags)
{
    VkCommandPoolCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    info.pNext = nullptr;
    info.queueFamilyIndex = queueFamilyIndex;
    info.flags = flags;
    return info;
}

VkCommandBufferAllocateInfo CommandBufferAllocateInfo(
    VkCommandPool pool, uint32_t count, VkCommandBufferLevel level)
{
    VkCommandBufferAllocateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    info.pNext = nullptr;
    info.commandBufferCount = count;
    info.commandPool = pool;
    info.level = level;
    return info;
}

VkPipelineShaderStageCreateInfo PipelineShaderStageCreateInfo(
    VkShaderStageFlagBits stage, VkShaderModule shaderModule)
{
    VkPipelineShaderStageCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    info.pNext = nullptr;

    //! Set shader stage
    info.stage = stage;
    //! Pass module containing the code for this shader stage
    info.module = shaderModule;
    //! Set the entry point of the shader (normally, main)
    info.pName = "main";
    return info;
}
}  // namespace Initializer
};  // namespace Renderer