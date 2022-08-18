// Code example for Chain of Responsibility pattern

#include <iostream>
#include <system_error>

// ============================================================================
//                                   CLASSES
// ----------------------------------------------------------------------------

//                         =========================
//                         class HelpHandlerProtocol
//                         =========================

class HelpHandlerProtocol {
protected:
  // PROTECTED CREATORS
  HelpHandlerProtocol() = default;
  HelpHandlerProtocol(const HelpHandlerProtocol &) = default;
  HelpHandlerProtocol(HelpHandlerProtocol &&) noexcept = default;

  // PROTECTED MANIPULATORS
  auto operator=(const HelpHandlerProtocol &)
      -> HelpHandlerProtocol & = default;
  auto operator=(HelpHandlerProtocol &&) noexcept
      -> HelpHandlerProtocol & = default;

public:
  // CREATORS
  virtual ~HelpHandlerProtocol() = default;

  // MANIPULATORS
  virtual auto handleHelp() -> void = 0;
  virtual auto nextHandler() -> HelpHandlerProtocol & = 0;

  // ACCESSORS
  virtual auto hasHelp() const -> bool = 0;
};

//                         =================
//                         class Application
//                         =================

class Application final : public HelpHandlerProtocol {
public:
  // MANIPULATORS
  auto handleHelp() -> void final {
    ::std::cerr << "Hello, this is the generic help for the visu.\n";
  }
  auto nextHandler() -> HelpHandlerProtocol & final { return *this; } 

  // ACCESSORS
  auto hasHelp() const -> bool final { return true; }
};

//                         ====================
//                         class WidgetProtocol
//                         ====================

class WidgetProtocol : public HelpHandlerProtocol {
protected:
  // PROTECTED CREATORS
  WidgetProtocol() = default;
  WidgetProtocol(const WidgetProtocol &) = default;
  WidgetProtocol(WidgetProtocol &&) noexcept = default;

  // PROTECTED MANIPULATORS
  auto operator=(const WidgetProtocol &) -> WidgetProtocol & = default;
  auto operator=(WidgetProtocol &&) noexcept -> WidgetProtocol & = default;

public:
  // CREATORS
  ~WidgetProtocol() = default;

  // MANIPULATORS
  virtual auto draw() -> void = 0;
};

//                         ============
//                         class Button
//                         ============

class Button final : public WidgetProtocol {
  // DATA
  WidgetProtocol *m_successor_p; // not-null
  ::std::error_code m_errorCode;

public:
  // CREATORS
  explicit Button(
      WidgetProtocol &successor, // NOLINT(google-runtime-references)
      ::std::error_code errorCode)
      : m_successor_p{&successor}, m_errorCode{errorCode} {}

  // MANIPULATORS
  auto draw() -> void final { ::std::cout << "Button::draw()\n"; }

  auto handleHelp() -> void final {
    if (this->hasHelp()) {
      ::std::cerr << this->m_errorCode.category().name() << ": "
                  << this->m_errorCode.message() << "\n";
    } else {
      this->nextHandler().handleHelp();
    }
  }

  auto nextHandler() -> HelpHandlerProtocol & final {
    return *this->m_successor_p;
  }

  // ACCESSORS
  auto hasHelp() const -> bool override {
    return this->m_errorCode.operator bool();
  }
};

//                         ============
//                         class Dialog
//                         ============

class Dialog final : public WidgetProtocol {
  // DATA
  HelpHandlerProtocol *m_successor_p; // not-null
  ::std::error_code m_errorCode;

public:
  // CREATORS
  explicit Dialog(
      HelpHandlerProtocol &successor, // NOLINT(google-runtime-references)
      ::std::error_code errorCode)
      : m_successor_p{&successor}, m_errorCode{errorCode} {}

  // MANIPULATORS
  auto draw() -> void final { ::std::cout << "Dialog::draw()\n"; }

  auto handleHelp() -> void final {
    if (this->hasHelp()) {
      ::std::cerr << this->m_errorCode.category().name() << ": "
                  << this->m_errorCode.message() << "\n";
    } else {
      this->nextHandler().handleHelp();
    }
  }

  auto nextHandler() -> HelpHandlerProtocol & final {
    return *this->m_successor_p;
  }

  // ACCESSORS
  auto hasHelp() const -> bool override {
    return this->m_errorCode.operator bool();
  }
};

// ============================================================================
//                                     MAIN
// ----------------------------------------------------------------------------

auto main() -> int try {
  auto app = ::Application{};

  // 1. Chain
  auto selectSequenceWidget = ::Dialog{app, ::std::error_code{}};
  auto confirmSequenceButton =
      ::Button{selectSequenceWidget, ::std::error_code{}};
  auto browseForSequenceButton =
      ::Button{selectSequenceWidget, make_error_code(::std::errc::file_exists)};

  // 2. Chain
  auto plotWidget = ::Dialog{app, make_error_code(::std::errc::no_link)};
  auto toogleColorButton = ::Button{plotWidget, ::std::error_code{}};

  // Generic program is working with 'WidgetProtocol' objects
  confirmSequenceButton.handleHelp();
  browseForSequenceButton.handleHelp();

  toogleColorButton.handleHelp();
} catch (...) {
  return 1;
}
