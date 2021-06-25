#ifndef MACROS_HPP
#define MACROS_HPP

#include <Common/Logger.hpp>

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

template <typename Result>
inline bool VkCheckError(Result result)
{
    if (result)
    {
        LOG_ERROR << result;
        return false;
    }
    else
    {
        return true;
    }
}

#endif  //! end of Macros.hpp