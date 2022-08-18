#include <vaddons/util/vad_util_flag_enum.hpp>

#include <iostream>

#include <vector>
#include <bitset>
#include <cstdint>

namespace {

    enum class EFlags : ::std::uint32_t {
        e_NONE = 0U,
        e_HAVE_MOFU = 1U << 0U,
        e_HAVE_MOPED = 1U << 1U,
        e_HAVE_SEPA = 1U << 2U,
    };

} // namespace

namespace vad {
    namespace util {
        template<>
        struct TIsFlagEnum<::EFlags> : ::vad::true_type{};
    }
}

auto main() -> int {
    constexpr auto flags1 = ::EFlags::e_HAVE_MOFU | ::EFlags::e_HAVE_MOPED;
    constexpr auto flags2 = ::EFlags::e_HAVE_SEPA | ::EFlags::e_HAVE_MOFU;
    constexpr auto flags3 = flags1 | flags2;
    constexpr auto flags4 = flags1 & flags2;
    constexpr auto flags5 = flags1 ^ flags2;
    if (::vad::util::CFlagEnumUtil::fulfills(flags5, ::EFlags::e_HAVE_MOPED))
        ::std::cout << "Hello Moped!\n";
    ::std::cout << "Hello flag_enum!\n";
}
