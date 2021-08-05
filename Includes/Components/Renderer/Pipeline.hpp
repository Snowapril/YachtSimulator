#ifndef VK_PIPELINE_HPP
#define VK_PIPELINE_HPP

#include <Components/Renderer/Resource.hpp>
#include <memory>

namespace Renderer
{
class Device;

class Pipeline : public Resource
{
 public:
    //! Default constructor
    Pipeline(std::shared_ptr<Device> devicePtr);

    //! Default destructor
    ~Pipeline();

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