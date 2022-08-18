#ifndef DEC_COST_FUNCTION_PROTOCOL_HPP_INCLUDED
#define DEC_COST_FUNCTION_PROTOCOL_HPP_INCLUDED

namespace dec {

// ============================================================================
//                                   CLASSES
// ----------------------------------------------------------------------------

class CostFunctionProtocol;

//                         ===========================
//                         class CostFunctionProtocol
//                         ===========================

class CostFunctionProtocol {
protected:
  // PROTECTED CREATORS
  CostFunctionProtocol() = default;
  CostFunctionProtocol(const CostFunctionProtocol &) = default;
  CostFunctionProtocol(CostFunctionProtocol &&) noexcept = default;

  // PROTECTED MANIPULATORS
  auto operator=(const CostFunctionProtocol &)
      -> CostFunctionProtocol & = default;
  auto operator=(CostFunctionProtocol &&) noexcept
      -> CostFunctionProtocol & = default;

public:
  // CREATORS
  virtual ~CostFunctionProtocol() = default;

  // MANIPULATORS
  // virtual
};

} // namespace dec

#endif // DEC_COST_FUNCTION_PROTOCOL_HPP_INCLUDED
