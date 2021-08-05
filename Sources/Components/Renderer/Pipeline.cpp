#include <vulkan/vulkan.h>
#include <Components/Renderer/Device.hpp>
#include <Components/Renderer/Pipeline.hpp>
#include <fstream>
#include <vector>

namespace Renderer
{
Pipeline::Pipeline(std::shared_ptr<Device> devicePtr) : _device(devicePtr)
{
    //! Do nothing
}

Pipeline::~Pipeline()
{
    FlushDeletion();
}

bool Pipeline::LoadShaderModule(const std::string& path,
                                VkShaderModule* outShaderModule)
{
    //! Open the file with the cursor at the end
    std::ifstream file(path, std::ios::ate | std::ios::binary);

    if (!file.is_open())
        return false;

    //! Find what the size of the file
    const size_t fileSize = static_cast<size_t>(file.tellg());

    //! Spir-V expects the buffer to be on uint32
    std::vector<unsigned int> buffer(fileSize / sizeof(unsigned int));

    //! Put file cursor at the begining
    file.seekg(0);

    //! Read the buffer contents
    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

    //! Now buffer reading done
    file.close();

    //! Create a new shader module using the buffer we loaded
    VkShaderModuleCreateInfo shaderModuleInfo = {};
    shaderModuleInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shaderModuleInfo.pNext = nullptr;

    //! Codesize has to be in bytes
    shaderModuleInfo.codeSize = buffer.size() * sizeof(unsigned int);
    shaderModuleInfo.pCode = buffer.data();

    //! Check that the creation goes well
    VkShaderModule shaderModule;

    if (vkCreateShaderModule(_device->GetDevice(), &shaderModuleInfo, nullptr,
                             &shaderModule) != VK_SUCCESS)
        return false;

    //! Now shader loading success
    *outShaderModule = shaderModule;

    return true;
}
};  // namespace Renderer