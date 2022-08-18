#include <cassert>

namespace {

enum class EEnum {
  e_OK = 0,
  e_NOT_OK,
  e_STILL_OK,
};

} // namespace

auto main() -> int {
  const auto ec = ::EEnum::e_OK;

  switch (ec) {
  case ::EEnum::e_OK:
  case ::EEnum::e_STILL_OK:
    return 0;
  case ::EEnum::e_NOT_OK:
    return 1;
  }
  assert(false && "Unreachable!");
  return 1;
}
