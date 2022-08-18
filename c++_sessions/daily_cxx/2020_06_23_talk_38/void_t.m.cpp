#include <iostream>
#include <type_traits>

template <class...> struct make_void { using type = void; };
template <class... T> using void_t = typename make_void<T...>::type;

// ==========

template <class F, class T>
using ReturnTypeOfCallable_t =
    decltype(::std::declval<F>()(::std::declval<T>()));

template <class, class, class = void_t<>>
struct IsCallable : ::std::false_type {};

template <class F, class T>
struct IsCallable<F, T, ::void_t<::ReturnTypeOfCallable_t<F, T>>>
    : ::std::true_type {};

template <class F, class T>
constexpr bool IsCallable_v = ::IsCallable<F, T>::value;

// ==========

// template <class F, class T, bool>
// struct IsEndomorphismHelper : ::std::false_type {};
//
// template <class F, class T>
// struct IsEndomorphismHelper<F, T, true>
//     : ::std::is_same<ReturnTypeOfCallable_t<F, T>, T> {};

template <class, class>
constexpr auto isEndomorphismHelper(::std::false_type) -> bool {
  return false;
}

template <class F, class T>
constexpr auto isEndomorphismHelper(::std::true_type) -> bool {
  return ::std::is_same_v<ReturnTypeOfCallable_t<F, T>, T>;
}

template <class F, class T>
constexpr bool
    IsEndomorphism_v = ::isEndomorphismHelper<F, T>(::IsCallable<F, T>{});
//    ::IsEndomorphismHelper<F, T, IsCallable_v<F, T>>::value;

// ==========

template<class F, class T>
concept IsEndomorphism = IsEndomorphism_v<F,T>;
// requires(F f, T t){
//   {f(t)} -> T;
// };

// ==========

struct S1 {};
struct S2 {};

auto f1 = [](S1) { return S2{}; };
auto f2 = [](S1 s) { return s; };

auto main() -> int {
  using f1_t = decltype(f1);
  using f2_t = decltype(f2);
  ::std::cout << "f1(S1): " << ::IsEndomorphism<f1_t, ::S1> << "\n"
              << "f2(S1): " << ::IsEndomorphism<f2_t, ::S1> << "\n";
}
