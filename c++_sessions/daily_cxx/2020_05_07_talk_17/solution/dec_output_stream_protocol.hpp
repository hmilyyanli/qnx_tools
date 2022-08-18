#ifndef DEC_OUTPUT_STREAM_PROTOCOL_HPP_INCLUDED
#define DEC_OUTPUT_STREAM_PROTOCOL_HPP_INCLUDED

#include <string> // std::string

namespace dec {

// ============================================================================
//                                   CLASSES
// ----------------------------------------------------------------------------

class OutputStreamProtocol;
class OutputStreamDecorator;

//                         ===========================
//                         class OutputStreamProtocol
//                         ===========================

class OutputStreamProtocol {
protected:
  // PROTECTED CREATORS
  OutputStreamProtocol() = default;
  OutputStreamProtocol(const OutputStreamProtocol &) = default;
  OutputStreamProtocol(OutputStreamProtocol &&) noexcept = default;

  // PROTECTED MANIPULATORS
  auto operator=(const OutputStreamProtocol &)
      -> OutputStreamProtocol & = default;
  auto operator=(OutputStreamProtocol &&) noexcept
      -> OutputStreamProtocol & = default;

public:
  // CREATORS
  virtual ~OutputStreamProtocol() = default;

  // MANIPULATORS
  virtual auto PrintString(::std::string &f_message)
      -> ::dec::OutputStreamProtocol & = 0;
  //    Take the specified 'f_message' and put it to some stream object.
};

//                         ==========================
//                         class OutputStreamProtocol
//                         ==========================

class OutputStreamDecorator : public ::dec::OutputStreamProtocol {
  // DATA
  ::dec::OutputStreamProtocol *m_outputStreamProtocol_p; // not-null

protected:
  // PROTECTED CREATORS
  explicit OutputStreamDecorator(
      ::dec::OutputStreamProtocol &f_outputStreamProtocol) noexcept
      : m_outputStreamProtocol_p{&f_outputStreamProtocol} {
  }

public:
  // MANIPULATORS
  auto PrintString(::std::string &f_message)
      -> ::dec::OutputStreamProtocol & final {
    this->ApplyDecoratorPrintString(f_message);
    return this->m_outputStreamProtocol_p->PrintString(f_message);
  }

  virtual auto ApplyDecoratorPrintString(::std::string &f_message)
      -> ::dec::OutputStreamDecorator & = 0;
  //    Read the specified 'f_message' to sth. with it and load the result into
  //    'f_message'.
};

} // namespace dec

#endif // DEC_OUTPUT_STREAM_PROTOCOL_HPP_INCLUDED
