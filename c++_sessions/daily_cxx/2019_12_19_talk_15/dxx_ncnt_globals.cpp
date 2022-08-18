#include <dxx_ncnt_globals.hpp>

#include <dxx_raii_object.hpp>
#include <dxx_siu_metre.hpp>

#include <iostream>
#include <new>         // placement new
#include <type_traits> // aligned_storage

namespace dn = ::dxx::ncnt;

namespace {

template <class T>
using Buffer = typename ::std::aligned_storage<sizeof(T), alignof(T)>::type;

Buffer<int> xBuffer;
Buffer<int> yBuffer;

Buffer<::dxx::raii::Object> obj1Buffer;
Buffer<::dxx::raii::Object> obj2Buffer;

Buffer<::dxx::siu::Metre> mBuffer;

int NiftyCounter = 0;

} // namespace

const int & ::dn::x = reinterpret_cast<const int &>(xBuffer); // NOLINT
int & ::dn::y = reinterpret_cast<int &>(yBuffer);             // NOLINT

const ::dxx::raii::Object & ::dn::obj1 =
    reinterpret_cast<const ::dxx::raii::Object &>(obj1Buffer); // NOLINT
const ::dxx::raii::Object & ::dn::obj2 =
    reinterpret_cast<const ::dxx::raii::Object &>(obj2Buffer); // NOLINT

const ::dxx::siu::Metre & ::dn::m =
    reinterpret_cast<const ::dxx::siu::Metre &>(mBuffer); // NOLINT

namespace dxx::ncnt {
NiftyCounterGuard::NiftyCounterGuard() {
  ::std::cout << " NiftyCounter: " << NiftyCounter << "\n";
  if (NiftyCounter == 0) {
    new (&yBuffer) int{5};
    new (&xBuffer) int{3 * y + 7};

    new (&obj2Buffer) dxx::raii::Object{nullptr, 6};
    new (&obj1Buffer) dxx::raii::Object{&obj2, 5};

    new (&mBuffer) dxx::siu::Metre{static_cast<double>(x) / 3.6}; // NOLINT
  }
  ++NiftyCounter;
}

NiftyCounterGuard::~NiftyCounterGuard() {
  ::std::cout << "~NiftyCounter: " << NiftyCounter << "\n";
  --NiftyCounter;
  if (NiftyCounter == 0) {
    m.~Metre();

    obj1.~Object();
    obj2.~Object();

    // y.~int();
    // x.~int();
  }
}

} // namespace dxx::ncnt
