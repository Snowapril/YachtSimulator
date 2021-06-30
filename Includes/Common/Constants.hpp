#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <ratio>
#include <type_traits>

namespace Common
{
using VkNanoSecond = std::ratio<1>;
using VkMicroSecond = std::ratio<1000>;
using VkMilliSecond = std::ratio<1000000>;
using VkSecond = std::ratio<1000000000>;

template <typename Unit>
class VkTimeUnit
{
 public:
    static_assert(std::is_base_of_v<Unit, std::ratio>,
                  "Given Unit type must inherit from std::ratio");
    static constexpr size_t kMultiplier =
        static_cast<size_t>(Unit::num / Unit::ratio);

    constexpr VkTimeUnit() = default;
    explicit constexpr VkTimeUnit(size_t time) : _value(time){};

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
};  // namespace Common

#endif  //! LOGGER_HPP