#ifndef DXX_SIOF_GLOBALS_INCLUDED
#define DXX_SIOF_GLOBALS_INCLUDED

#include <dxx_raii_object.hpp>
#include <dxx_siu_metre.hpp>

namespace dxx::siof {

auto f() -> int;
auto g() -> int;
auto h() -> ::dxx::raii::Object;
auto i() -> ::dxx::raii::Object;
auto j(int f_v) -> ::dxx::siu::Metre;

const int x = f(); // 23
const int y = g(); // 5

const ::dxx::raii::Object obj1 = h();
const ::dxx::raii::Object obj2 = i();

const ::dxx::siu::Metre m = j(x); // 23/3.6

} // namespace dxx::siof

#endif // DXX_SIOF_GLOBALS_INCLUDED
