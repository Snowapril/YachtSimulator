#ifndef UTILS_HPP
#define UTILS_HPP

#include <vulkan/vulkan.h>
#include <Components/Common/Logger.hpp>
#include <cassert>
#include <string>

namespace Renderer
{
//! Returns VkResult error code as a string
std::string ErrorToString(VkResult result);

//! Check given VkResult is success or not
//! If failed, print error code and abort program
#define VK_CHECK_ERROR(result, message)                                   \
    {                                                                     \
        if (result)                                                       \
        {                                                                 \
            LOG_ERROR << '(' << ErrorToString(result) << ") " << message; \
            std::abort();                                                 \
        }                                                                 \
    }
};  // namespace Renderer

#endif  //! UTILS_HPP