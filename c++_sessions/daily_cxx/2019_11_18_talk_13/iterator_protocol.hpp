template <class ValueType> class TIteratorProtocol {
protected:
  TIteratorProtocol() = default;
  TIteratorProtocol(const TIteratorProtocol &) = default;
  TIteratorProtocol(TIteratorProtocol &&) noexcept = default;

  auto operator=(const TIteratorProtocol &) -> TIteratorProtocol & = default;
  auto operator=(TIteratorProtocol &&) noexcept
      -> TIteratorProtocol & = default;

public:
  // CREATORS
  virtual ~TIteratorProtocol() = default;

  // MANIPULATORS
  virtual auto reset() -> TIteratorProtocol & = 0;
  virtual auto operator++() -> TIteratorProtocol & = 0;

  // ACCESSORS
  virtual auto operator*() const -> const ValueType & = 0;
  virtual auto hasValue() const -> bool = 0;
};
