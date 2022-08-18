#ifndef DXX_IOFU_GLOBALS_INCLUDED
#define DXX_IOFU_GLOBALS_INCLUDED

namespace dxx::raii {
class Object;
} // namespace dxx::raii

namespace dxx::siu {
class Metre;
} // namespace dxx::siu

namespace dxx::iofu {

auto x() -> const int &; // 22
auto y() -> int &;       // 5

auto obj1() -> const ::dxx::raii::Object &;
auto obj2() -> const ::dxx::raii::Object &;

auto m() -> const ::dxx::siu::Metre &; // 23/3.6

} // namespace dxx::iofu

#endif // DXX_IOFU_GLOBALS_INCLUDED
