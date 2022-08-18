#include <dec_output_stream_protocol.hpp>

#include <iostream> // std::cout
#include <regex>    // std::regex_replace

// ============================================================================
//                                LOCAL CLASSES
// ----------------------------------------------------------------------------

namespace {

//                         ================
//                         class CoutStream
//                         ================

class CoutStream final : public ::dec::OutputStreamProtocol {
public:
  // MANIPULATORS
  auto PrintString(::std::string &f_message) -> CoutStream & override {
    ::std::cout << f_message;
    return *this;
  }
  //    Take the specified 'f_message' push it to 'std::cout'.
};

//                         ============================
//                         class GermanUmlautsDecorator
//                         ============================

class GermanUmlautDecorator final : public ::dec::OutputStreamDecorator {
public:
  // CREATORS
  explicit GermanUmlautDecorator(::dec::OutputStreamProtocol &ts) noexcept
      : ::dec::OutputStreamDecorator{ts} {}

  // MANIPULATORS
  auto ApplyDecoratorPrintString(::std::string &f_message)
      -> GermanUmlautDecorator & override {
    using namespace ::std::literals;
    f_message =
        ::std::regex_replace(f_message, ::std::regex{"\x8e"}, "Ae"s); // Ä
    f_message =
        ::std::regex_replace(f_message, ::std::regex{"\x99"}, "Oe"s); // Ö
    f_message =
        ::std::regex_replace(f_message, ::std::regex{"\x9a"}, "Ue"s); // Ü
    f_message =
        ::std::regex_replace(f_message, ::std::regex{"\x84"}, "ae"s); // ä
    f_message =
        ::std::regex_replace(f_message, ::std::regex{"\x94"}, "oe"); // ö
    f_message =
        ::std::regex_replace(f_message, ::std::regex{"\x81"}, "ue"s); // ü
    return *this;
  }
};

//                         ========================
//                         class UppercaseDecorator
//                         ========================

class UppercaseDecorator final : public ::dec::OutputStreamDecorator {
public:
  // CREATORS
  explicit UppercaseDecorator(::dec::OutputStreamProtocol &ts) noexcept
      : ::dec::OutputStreamDecorator{ts} {}

  // MANIPULATORS
  auto ApplyDecoratorPrintString(::std::string &f_message)
      -> UppercaseDecorator & override {
    // auto ToUpper = [](char c) noexcept {
    //   constexpr int Ascii_a{'a'};
    //   constexpr int Ascii_z{'z'};
    //   const int Ascii_c{c};
    //   if (Ascii_c <= Ascii_z && Ascii_c >= Ascii_a) {
    //     constexpr int Ascii_A{'A'};
    //     c = static_cast<char>(Ascii_c - Ascii_a + Ascii_A);
    //   }
    //   return c;
    // };
    ::std::transform(f_message.begin(), f_message.end(), f_message.begin(),
                     ::toupper);
    return *this;
  }
};

} // namespace

// ============================================================================
//                                     MAIN
// ----------------------------------------------------------------------------

auto main() -> int {
  using namespace ::std::literals;

  auto msg = "\x8e\x94\x81-abc"s;

  ::CoutStream coutStream;
  ::GermanUmlautDecorator germanUmlautDecorator{coutStream};
  ::UppercaseDecorator uppercaseDecorator{uppercaseDecorator};
  germanUmlautDecorator.PrintString(msg);
}
