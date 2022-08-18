#include <type_traits>
#include <concepts>

using namespace std;

template <class, class = void> struct is_incrementable : false_type {};

template <class T>
struct is_incrementable<T, void_t<decltype(++declval<T&>())>> : true_type {};

template <class T>
inline constexpr bool is_incrementable_v = is_incrementable<T>::value;

template<class T>
concept Incrementable = is_incrementable_v<T>; // using already existing TMP

template <class T>
concept PseudoIterator =
is_pointer_v<T> ||
(is_class_v<T> && Incrementable<T>);

class MyPtr {
public:
	auto operator++() -> MyPtr& { return *this; }
	operator int() { return 1; }
};

template <PseudoIterator T> auto nnext(T iter) -> T {
	return ++iter;
}

template<class T>
concept Iterator = requires(T iter) {
	typename T::type;
	{ ++iter } -> ::std::convertible_to<T>;
	{ *iter } -> ::std::convertible_to<typename T::type>;
};

template <Iterator T> auto next(T iter) -> T {
	return ++iter;
}

class RealIter {
public:
	using type = double;
	auto operator++() -> RealIter& { return *this; }
	auto operator*() -> double { return 13.; }
	operator int() { return 1; }
};

int main() {
	RealIter iter;
	return next(iter);
}