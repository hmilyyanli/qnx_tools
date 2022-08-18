#ifndef DXX_NCNT_GLOBALS_INCLUDED
#define DXX_NCNT_GLOBALS_INCLUDED

namespace dxx::raii {
class Object;
} // namespace dxx::raii

namespace dxx::siu {
class Metre;
} // namespace dxx::siu

namespace dxx::ncnt {

extern const int &x; // 22
extern int &y;       // 5

extern const ::dxx::raii::Object &obj1;
extern const ::dxx::raii::Object &obj2;

extern const ::dxx::siu::Metre &m;

struct NiftyCounterGuard {
  NiftyCounterGuard();
  ~NiftyCounterGuard();
};
static NiftyCounterGuard niftyCounterGuard;

} // namespace dxx::ncnt

#endif // DXX_NCNT_GLOBALS_INCLUDED
