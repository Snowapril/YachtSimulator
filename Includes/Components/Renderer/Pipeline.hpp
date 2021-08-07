#ifndef VK_PIPELINE_HPP
#define VK_PIPELINE_HPP

#include <Components/Renderer/Resource.hpp>
#include <memory>

namespace Renderer
{
class Device;

struct PipelineConfigInfo
{
    VkPipelineVertexInputStateCreateInfo vertexInput{};
    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    VkPipelineRasterizationStateCreateInfo rasterizer{};
    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    VkPipelineColorBlendStateCreateInfo colorBlendState{};
    VkPipelineMultisampleStateCreateInfo multisampling{};
    VkPipelineLayout pipelineLayout{};
    VkRenderPass renderPass{};
    VkPipelineViewportStateCreateInfo viewportState{};
    VkViewport viewport{};
    VkRect2D scissor{};
};
class Pipeline : public Resource
{
 public:
    //! Default constructor
    Pipeline(std::shared_ptr<Device> devicePtr);

    //! Default destructor
    ~Pipeline();

    /**
     * @brief Returns default pipeline config structure
     * @warning As scissor, viewport and pipelinelayout structure not
     * initialized in this function, you need to initialize it manually.
     * @param config default config settings are passed by pointer
     */
    static void GetDefaultPipelineConfig(PipelineConfigInfo* config);

 protected:
 private:
    /**
     * @brief Load spir-V shader binary from given file
     * 
     * @param path spir-V shader binary file path
     * @param outShaderModule pass created shader by reference
     * @return true if shader loading success return true
     * @return false if shader loading failed by some reason return false
     */
    bool LoadShaderModule(const std::string& path, VkShaderModule* outShaderModule);

    std::shared_ptr<Device> _device;
};
};  // namespace Renderer

#endif  //! PIPELINE_HPP