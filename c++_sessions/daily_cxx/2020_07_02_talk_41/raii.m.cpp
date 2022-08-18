#include <daddons/utils/daddons_update_guard.hpp>
#include <iostream>
#include <memory>
#include <numeric>

// RAII - Resource Acquisition is Initialization
//
// Bind the lifetime of resource to the lifetime of an object.
//
// Resource - Sth. that has to acquired and afterwards released.
// Initialization - Constructor of an object.

class Port {
public:
  auto update() & -> void { ::std::cout << "update\n"; }
  auto cleanup() & -> void { ::std::cout << "cleanup\n"; }
};

auto main() -> int {
  constexpr int size{10};
  double *data_p = new double[size]; // acquire
  delete[] data_p;                   // release

  ::std::unique_ptr<double[]> raiiPtr{new double[size]}; // acquire

  {
    Port port;
    const auto updateGuard = ::daddons::utils::makeUpdateGuard(port);
    // lots of code
    return 0;
    // even more code
  }
  {
    Port port;
    const auto updateGuard = ::daddons::utils::makeUpdateGuard(port);
    // lots of code
    // return 0;
    // even more code
  }
} // implicitly released via d'tor
