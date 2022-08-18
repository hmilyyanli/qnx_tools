#include <type_traits>

using namespace std;

template <class, class = void> struct is_incrementable : false_type {};

template <class T>
struct is_incrementable<T, void_t<decltype(++declval<T &>())>> : true_type {};

template <class T>
inline constexpr bool is_incrementable_v = is_incrementable<T>::value;

template <class T>
struct IsIterator
    : integral_constant<bool, is_pointer_v<T> ||
                                  (is_class_v<T> && is_incrementable_v<T>)> {};

template <class T> inline constexpr bool isIterator_v = IsIterator<T>::value;

class MyPtr {
public:
  auto operator++() -> MyPtr & { return *this; }
  operator int() { return 1; }
};

template <class T> auto increment(T iter) -> enable_if_t<isIterator_v<T>, T> {
  return ++iter;
}

template <class T> auto increment(T iter) -> enable_if_t<is_integral_v<T>, T> {
  return 0;
}

int main() {
  MyPtr p;
  return increment(1);
}
