#ifndef VK_INITIALIZERS_HPP
#define VK_INITIALIZERS_HPP

#include <vulkan/vulkan.h>
#include <Components/Renderer/Resource.hpp>

namespace Renderer
{
namespace Initializer
{
VkCommandPoolCreateInfo CommandPoolCreateInfo(
    uint32_t queueFamilyIndex, VkCommandPoolCreateFlags flags = 0);

VkCommandBufferAllocateInfo CommandBufferAllocateInfo(
    VkCommandPool pool, uint32_t count = 1,
    VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY);

VkPipelineShaderStageCreateInfo PipelineShaderStageCreateInfo(
    VkShaderStageFlagBits stage, VkShaderModule shaderModule);

}  // namespace Initializer
};  // namespace Renderer

#endif  //! PIPELINE_HPP