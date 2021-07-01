#include <Renderer/Initializer.hpp>

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
}  // namespace Initializer
};  // namespace Renderer