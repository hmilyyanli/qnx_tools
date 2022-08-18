#include <dxx_con_globals.hpp>
#include <dxx_iofu_globals.hpp>
#include <dxx_ncnt_globals.hpp>
#include <dxx_raii_object.hpp>
#include <dxx_siof_globals.hpp>
#include <dxx_siu_metre.hpp>

#include <iostream>

auto main() -> int {
  ::std::cout << "============================================================="
                 "=========\n"
              << "                         MAIN\n"
              << "============================================================="
                 "========="
                 "\n";

  const int expectedX = 22;
  const int expectedY = 5;

  ::std::cout << "-- Hello Fiasco!\n"
              << "x: " << ::dxx::siof::x << ", (expected " << expectedX << ")\n"
              << "y: " << ::dxx::siof::y << ", (expected " << expectedY << ")\n"
              << "m: " << ::dxx::siof::m.value() << ", (expected 23/3.6)\n"
              << "-- Hello constexpr!\n"
              << "x: " << ::dxx::con::x << ", (expected " << expectedX << ")\n"
              << "y: " << ::dxx::con::y << ", (expected " << expectedY << ")\n"
              << "m: " << ::dxx::con::m.value() << ", (expected 23/3.6)\n"
              << "-- Hello init on first use!\n"
              << "x: " << ::dxx::iofu::x() << ", (expected " << expectedX
              << ")\n"
              << "y: " << ::dxx::iofu::y() << ", (expected " << expectedY
              << ")\n"
              << "m: " << ::dxx::iofu::m().value() << ", (expected 23/3.6)\n";
  ::dxx::iofu::obj1();

  ::std::cout << "x: " << ::dxx::ncnt::x << ", (expected " << expectedX << ")\n"
              << "y: " << ::dxx::ncnt::y << ", (expected " << expectedY << ")\n"
              << "m: " << ::dxx::ncnt::m.value() << ", (expected 23/3.6)\n";

  ::std::cout << "============================================================="
                 "=========\n"
              << "                         END MAIN\n"
              << "============================================================="
                 "=========\n";
}
