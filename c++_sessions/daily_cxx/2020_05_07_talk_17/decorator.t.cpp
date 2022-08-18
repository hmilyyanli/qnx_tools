#include <algorithm>
#include <iostream>
#include <regex>
#include <string>

// ============================================================================
//                                    HEADER
// ----------------------------------------------------------------------------

namespace {

class COutputStreamProtocol {
protected:
  // PROTECTED CREATORS
  COutputStreamProtocol() = default;

  COutputStreamProtocol(const COutputStreamProtocol &) = default;
  COutputStreamProtocol(COutputStreamProtocol &&) noexcept = default;

  auto operator=(const COutputStreamProtocol &)
      -> COutputStreamProtocol & = default;
  auto operator=(COutputStreamProtocol &&) noexcept
      -> COutputStreamProtocol & = default;

public:
  // CREATORS
  virtual ~COutputStreamProtocol() = default;

  // MANIPULATORS
  virtual auto PrintMessage(::std::string &&f_message)
      -> COutputStreamProtocol & = 0;
};

class COutputStreamDecorator : public COutputStreamProtocol {
  // DATA
  COutputStreamProtocol *m_outputStreamProtocol_p; // not-null
protected:
  // CREATORS
  explicit COutputStreamDecorator(COutputStreamProtocol &f_input) noexcept
      : m_outputStreamProtocol_p{&f_input} {}

public:
  // MANIPULATORS
  virtual auto ApplyDecoratorAction(::std::string &f_message)
      -> COutputStreamDecorator & = 0;

  auto PrintMessage(::std::string &&f_message)
      -> COutputStreamProtocol & final {
    this->ApplyDecoratorAction(f_message);
    this->m_outputStreamProtocol_p->PrintMessage(::std::move(f_message));
    return *this;
  }
};

} // namespace

// ============================================================================
//                                    TESTS
// ----------------------------------------------------------------------------

namespace {

class CoutStream final : public COutputStreamProtocol {
public:
  auto PrintMessage(::std::string &&f_message) -> CoutStream & final {
    ::std::cout << ::std::move(f_message);
    return *this;
  }
};

class UmlautDecorator final : public COutputStreamDecorator {
public:
  // CREATORS
  explicit UmlautDecorator(COutputStreamProtocol &f_input) noexcept
      : COutputStreamDecorator{f_input} {}

  // MANIPUALTORS
  auto ApplyDecoratorAction(::std::string &f_message)
      -> UmlautDecorator & final {
    using namespace ::std::literals;
    f_message =
        ::std::regex_replace(f_message, ::std::regex{"\x8e"}, "Ae"s); // Ä
    return *this;
  }
};

class UppercaseDecorator final : public COutputStreamDecorator {
public:
  // CREATORS
  explicit UppercaseDecorator(COutputStreamProtocol &f_input) noexcept
      : COutputStreamDecorator{f_input} {}

  // MANIPUALTORS
  auto ApplyDecoratorAction(::std::string &f_message)
      -> UppercaseDecorator & final {
    ::std::transform(f_message.begin(), f_message.end(), f_message.begin(),
                     ::toupper);
    return *this;
  }
};

} // namespace

auto main() -> int {
  CoutStream coutStream;
  UppercaseDecorator uppercaseDecorator{coutStream};
  UmlautDecorator umlautDecorator{uppercaseDecorator};
  umlautDecorator.PrintMessage("\x8e Blub").PrintMessage("\nyeah!");
}
