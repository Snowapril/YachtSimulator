#ifndef MACROS_HPP
#define MACROS_HPP

#if defined(_WIN32) || defined(_WIN64)
#define YACHT_WINDOWS
#elif defined(__APPLE__)
#define YACHT_APPLE
#ifndef YACHT_IOS
#define YACHT_MACOSX
#endif
#elif defined(linux) || defined(__linux__)
#define YACHT_LINUX
#endif

#if defined(YACHT_WINDOWS) && defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#else
#include <sys/types.h>
#endif

#ifndef UNUSED_VARIABLE
#define UNUSED_VARIABLE(x) ((void)x)
#endif

#ifndef VK_CHECK
#define VK_CHECK(x)       \
    VkResult err = x;     \
    if (err)              \
    {                     \
        LOG_ERROR << err; \
        std::abort();     \
    }
#endif

#endif  //! end of Macros.hpp