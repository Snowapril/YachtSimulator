#ifndef VK_PIPELINE_HPP
#define VK_PIPELINE_HPP

#include <Components/Renderer/Resource.hpp>
#include <Components/Renderer/Utils.hpp>
#include <memory>
#include <unordered_map>

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
    using ShaderInfoStorage =
        std::unordered_map<VkShaderStageFlagBits, std::string>;
    using ShaderStorage =
        std::unordered_map<VkShaderStageFlagBits, VkShaderModule>;

    /**
     * @brief Construct Pipeline object with given shader and configurations
     *
     * @param devicePtr Initialized vulkan device smart pointer
     * @param shaderInfos unordered pairs of shader flag and path
     * @param config predefined pipeline building configuration
     * @warning As scissor, viewport and pipelinelayout in config structure
     * must be initialized before call this constructor
     */
    Pipeline(std::shared_ptr<Device> devicePtr,
             const ShaderInfoStorage& shaderInfos,
             const PipelineConfigInfo& config);

    //! Default destructor
    ~Pipeline();

    /**
     * @brief Build pipeline with given config and predefined shader modules
     *
     * @param devicePtr Initialized vulkan device smart pointer
     * @param shaderInfos unordered pairs of shader flag and path
     * @param config predefined pipeline building configuration
     * @warning As scissor, viewport and pipelinelayout in config structure
     * must be initialized before call this constructor
     * @return true if building pipeline success
     * @return false if building pipeline failed
     */
    bool Initialize(std::shared_ptr<Device> devicePtr,
                    const ShaderInfoStorage& shaderInfos,
                    const PipelineConfigInfo& config);

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
    bool LoadShaderModule(const std::string& path,
                          VkShaderModule* outShaderModule);

    std::shared_ptr<Device> _device;
    std::unordered_map<VkShaderStageFlagBits, VkShaderModule> _shaderModules;
    VkPipeline _pipeline;
};
};  // namespace Renderer

#endif  //! PIPELINE_HPP