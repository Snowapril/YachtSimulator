#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <ratio>
#include <type_traits>

namespace Common
{
template <typename Unit>
class VkTimeUnit
{
 public:
    static constexpr size_t kMultiplier =
        static_cast<size_t>(Unit::num / Unit::den);

    constexpr VkTimeUnit() = default;
    explicit constexpr VkTimeUnit(size_t time) : _value(time * kMultiplier){};

    template <typename OtherUnit>
    explicit constexpr VkTimeUnit(VkTimeUnit<OtherUnit> other)
        : _value(other._value / kMultiplier * other.kMultiplier){};

    constexpr size_t Get() const
    {
        return _value;
    }
    explicit constexpr operator size_t()
    {
        return _value;
    }

 private:
    size_t _value;
};
//! Type aliasing for frequently used time units
using VkNanoSecond = VkTimeUnit<std::ratio<1>>;
using VkMicroSecond = VkTimeUnit<std::ratio<1000>>;
using VkMilliSecond = VkTimeUnit<std::ratio<1000000>>;
using VkSecond = VkTimeUnit<std::ratio<1000000000>>;
};  // namespace Common

#endif  //! LOGGER_HPP