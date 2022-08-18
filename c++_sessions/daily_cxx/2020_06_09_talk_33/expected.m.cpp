#include <iostream>
#include <vaddons/error_handling/vad_errh_system_error.hpp>
#include <vaddons/error_handling/vaddons_expected.hpp>

namespace {
    struct Number {
        double value;
    };

    auto squareInput(Number number) -> ::vad::TExpected<::Number, ::vad::errh::CErrorCode>
    {
        constexpr auto upperBound = 10.;
        if (!(number.value < upperBound)) {
            return ::vad::makeUnexpected(makeErrorCode(::vad::errh::EErrc::ARGUMENT_OUT_OF_DOMAIN));
        }
        return ::vad::makeExpected(Number{ number.value * number.value }, ::vad::errh::CErrorCode{});
    }

    // technical stuff begin...
    class MyHandler final : public ::vad::aha::CInterfaceFailureHandler {
    public:
        auto failedEnsure(const ::vad::aha::CInterfaceFailureSpec& f_failSpec) const -> void final {
            ::std::cerr << "error\n";
        }

        auto failedExpect(const ::vad::aha::CInterfaceFailureSpec& f_failSpec) const -> void final {
            ::std::cerr << "error\n";
        }

        auto failedAssert(const ::vad::aha::CInterfaceFailureSpec& f_failSpec) const -> void final {
            ::std::cerr << "error\n";
        }
    };
} // namespace
    
auto main() -> int {
    MyHandler myHandler;
    static_cast<void>(::vad::aha::CAssertUtil::setFailureHandler(&myHandler));
    // technical stuff end...

    const auto expectNumber = ::squareInput({ 5. });
    ::std::cout << expectNumber.valueOr(Number{ -1. }).value << "\n";
    if (expectNumber.status() == makeErrorCondition(::vad::errh::EErrc::ARGUMENT_OUT_OF_DOMAIN)) {
        ::std::cout << "Handling error!\n";
    }
}
