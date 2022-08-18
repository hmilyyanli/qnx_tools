#ifndef DXX_CON_GLOBALS_INCLUDED
#define DXX_CON_GLOBALS_INCLUDED

// #include <dxx_raii_object.hpp>
#include <dxx_siu_metre.hpp>

namespace dxx::con {

constexpr auto g() -> int { return 5; }
constexpr int y = g(); // 5

constexpr auto f() -> int { return 3 * y + 7; }
constexpr int x = f(); // 23

// auto h() -> ::dxx::raii::Object;
// auto i() -> ::dxx::raii::Object;
// const ::dxx::raii::Object obj1 = h();
// const ::dxx::raii::Object obj2 = i();

constexpr auto j(int f_v) -> ::dxx::siu::Metre {
  return ::dxx::siu::Metre{static_cast<double>(f_v) / 3.6}; // NOLINT
}

constexpr ::dxx::siu::Metre m = j(x); // 23/3.6

} // namespace dxx::con

#endif // DXX_CON_GLOBALS_INCLUDED
