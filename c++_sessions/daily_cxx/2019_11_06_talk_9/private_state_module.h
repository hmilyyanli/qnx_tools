#include <iostream>

class TCPState {
protected:
  TCPState() = default;
  TCPState(const TCPState &) = default;
  TCPState(TCPState &&) noexcept = default;

  auto operator=(const TCPState &) -> TCPState & = default;
  auto operator=(TCPState &&) noexcept -> TCPState & = default;

public:
  virtual ~TCPState() = default;

  virtual auto open(const TCPConnection &) const -> const TCPState * {
    ::std::cout << "Ups member open() called\n";
    return nullptr;
  }
  virtual auto synchronize(const TCPConnection &) const -> const TCPState * {
    ::std::cout << "Ups member synchronize() called\n";
    return nullptr;
  }
  virtual auto close(const TCPConnection &) const -> const TCPState * {
    ::std::cout << "Ups member close() called\n";
    return nullptr;
  }
  virtual auto send(const TCPConnection &) const -> const TCPState * {
    ::std::cout << "Ups member send() called\n";
    return nullptr;
  }
};

struct TCPStateFlyweight {
  static auto openState() -> const TCPState *;
  static auto synchronizeState() -> const TCPState *;
  static auto closeState() -> const TCPState *;
};

class TCPOpenState final : public TCPState {
public:
  auto synchronize(const TCPConnection &) const -> const TCPState * final {
    return TCPStateFlyweight::synchronizeState();
  }
  auto close(const TCPConnection &) const -> const TCPState * {
    return TCPStateFlyweight::closeState();
  }
};

class TCPSynchronizeState final : public TCPState {
public:
  auto send(const TCPConnection &) const -> const TCPState * final {
    ::std::cout << "Successfully send data!\n";
    return this;
  }
  auto close(const TCPConnection &) const -> const TCPState * {
    return TCPStateFlyweight::closeState();
  }
};

class TCPCloseState final : public TCPState {
public:
  auto open(const TCPConnection &) const -> const TCPState * final {
    return TCPStateFlyweight::openState();
  }
};

auto TCPStateFlyweight::openState() -> const TCPState * {
  static const auto instance = TCPOpenState{};
  return &instance;
}
auto TCPStateFlyweight::synchronizeState() -> const TCPState * {
  static const auto instance = TCPSynchronizeState{};
  return &instance;
}
auto TCPStateFlyweight::closeState() -> const TCPState * {
  static const auto instance = TCPCloseState{};
  return &instance;
}
