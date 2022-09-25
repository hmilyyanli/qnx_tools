#ifndef _CSOMEFIASCO_H
#define _CSOMEFIASCO_H
#include <iostream>
struct NiftyCounterGuard {
  NiftyCounterGuard();
  ~NiftyCounterGuard();
};
static NiftyCounterGuard niftyCounterGuard;
#endif
