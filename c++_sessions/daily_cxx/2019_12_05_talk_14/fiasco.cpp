#include "fiasco.hpp"
#include <iostream>

int NiftyCounter = 0;

NiftyCounterGuard::NiftyCounterGuard() {
  std::cout << " NiftyCounter: " << NiftyCounter << "\n";
}

NiftyCounterGuard::~NiftyCounterGuard() {
  std::cout << "~NiftyCounter: " << NiftyCounter << "\n";
}
//static NiftyCounterGuard niftyCounterGuard;
