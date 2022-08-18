#include <dxx_iofu_globals.hpp>

#include <dxx_raii_object.hpp>
#include <dxx_siu_metre.hpp>

namespace di = ::dxx::iofu;

auto ::di::x() -> const int & {
  static const int g_singelton{3 * y() + 7};
  return g_singelton;
}

auto ::di::y() -> int & {
  static int g_singelton{5};
  return g_singelton;
}

auto ::di::obj1() -> const ::dxx::raii::Object & {
  static const ::dxx::raii::Object g_singelton{&obj2(), 3};
  return g_singelton;
}
auto ::di::obj2() -> const ::dxx::raii::Object & {
  static const ::dxx::raii::Object g_singelton{nullptr, 4};
  return g_singelton;
}

auto ::di::m() -> const ::dxx::siu::Metre & {
  static const ::dxx::siu::Metre g_singelton{static_cast<double>(x()) / 3.6}; // NOLINT
  return g_singelton;
}
