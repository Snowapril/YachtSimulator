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

void Pipeline::GetDefaultPipelineConfig(PipelineConfigInfo* config)
{
    //! Vertex input state create info
    config->vertexInput.sType =
        VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    config->vertexInput.pNext = nullptr;
    config->vertexInput.vertexBindingDescriptionCount = 0;
    config->vertexInput.vertexAttributeDescriptionCount = 0;

    //! Input assembly create info
    config->inputAssembly.sType =
        VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    config->inputAssembly.pNext = nullptr;
    config->inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
    config->inputAssembly.primitiveRestartEnable = VK_FALSE;

    //! Rasterization state create info
    config->rasterizer.sType =
        VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    config->rasterizer.pNext = nullptr;
    config->rasterizer.depthClampEnable = VK_FALSE;
    config->rasterizer.rasterizerDiscardEnable = VK_FALSE;
    config->rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    config->rasterizer.lineWidth = 1.0f;
    config->rasterizer.cullMode = VK_CULL_MODE_NONE;
    config->rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    config->rasterizer.depthBiasEnable = VK_FALSE;
    config->rasterizer.depthBiasConstantFactor = 0.0f;
    config->rasterizer.depthBiasClamp = 0.0f;
    config->rasterizer.depthBiasSlopeFactor = 0.0f;

    //! Multisampling state create info
    config->multisampling.sType =
        VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    config->multisampling.pNext = nullptr;
    config->multisampling.sampleShadingEnable = VK_FALSE;
    config->multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    config->multisampling.minSampleShading = 1.0f;
    config->multisampling.pSampleMask = nullptr;
    config->multisampling.alphaToCoverageEnable = VK_FALSE;
    config->multisampling.alphaToOneEnable = VK_FALSE;

    //! Color blend attachment state info
    config->colorBlendAttachment.colorWriteMask =
        VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
        VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    config->colorBlendAttachment.blendEnable = VK_FALSE;

    //! Color blend state info
    config->colorBlendState.sType =
        VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    config->colorBlendState.pNext = nullptr;
    config->colorBlendState.logicOpEnable = VK_FALSE;
    config->colorBlendState.logicOp = VK_LOGIC_OP_COPY;
    config->colorBlendState.attachmentCount = 1;
    config->colorBlendState.pAttachments = &(config->colorBlendAttachment);

    //! Viewport state info
    config->viewportState.sType =
        VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    config->viewportState.pNext = nullptr;
    config->viewportState.viewportCount = 1;
    config->viewportState.pViewports = &(config->viewport);
    config->viewportState.scissorCount = 1;
    config->viewportState.pScissors = &(config->scissor);
}

};  // namespace Renderer