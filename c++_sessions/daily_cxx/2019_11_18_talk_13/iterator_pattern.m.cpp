#include <array>
#include <iostream>

#include "iterator_protocol.hpp"

// #include "vaddons/iterator/vad_iter_interface_input_iterator.hpp"

auto summation(TIteratorProtocol<int> &iter) -> int {
  int result = 0;
  for (iter.reset(); iter.hasValue(); ++iter) {
    result += *iter;
  }
  return result;
}

class SomeAggregateIterator;

class SomeAggregate {
  int m_value1;
  ::std::array<int, 10> m_value2;

  friend class SomeAggregateIterator;

public:
  explicit SomeAggregate(int value1, ::std::array<int, 10> value2)
      : m_value1{value1}, m_value2{value2} {}

  auto makeIterator() -> SomeAggregateIterator;
};

class SomeAggregateIterator final : public TIteratorProtocol<int> {
  const SomeAggregate *m_data_p{nullptr};
  int m_member{0};
  int m_idx{0};

public:
  explicit SomeAggregateIterator(const SomeAggregate &f_data)
      : m_data_p{&f_data} {}

  // MANIPULATORS
  auto reset() -> SomeAggregateIterator & final {
    this->m_member = 0;
    this->m_idx = 0;
    return *this;
  }
  auto operator++() -> SomeAggregateIterator & final {
    if (this->m_member == 0) {
      ++this->m_member;
    } else {
      ++this->m_idx;
    }
    return *this;
  }

  // ACCESSORS
  auto operator*() const -> const int & final {
    return this->m_member == 0 ? this->m_data_p->m_value1
                               : this->m_data_p->m_value2.at(this->m_idx);
  }
  auto hasValue() const -> bool final {
	  bool b2 = this->m_data_p->m_value2.size() > this->m_idx;

    return (this->m_data_p->m_value2.size() > this->m_idx);
  }
};

auto SomeAggregate::makeIterator() -> SomeAggregateIterator {
  return SomeAggregateIterator{*this};
}

auto main() -> int {

  auto someAggregate = SomeAggregate{10, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}; // 65
  auto iter = someAggregate.makeIterator();
  auto v = summation(iter);
  v += summation(iter);

  ::std::cout << "Hello World!\n" << v << "\n";
}
