#include <doctest/doctest.h>
#include <Components/Common/Constants.hpp>

TEST_CASE("VkTimeUnit Constants Test")
{
    size_t milli = Common::VkMilliSecond(1).Get();
    size_t second = Common::VkSecond(1).Get();
    CHECK(milli * 1000 == second);
}