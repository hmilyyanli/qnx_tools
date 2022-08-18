# Daily C++ (#3) 1.10.2019

## Recap

* Template Meta Programming (TMP)
* Improved type safety example by defining a predicate and using 'enable_if'.

## What is a C++ concepts?

* A concepts represents a fundamental entity of an application field.
* Lots of concepts exists in mathematics (Algebra)
* E.g. Vector Space, Semigroup, Field
* Concepts are semantics (compile time interface for template parameters)

## Why C++ concepts?

* 'enable_if', 'decltype', 'declval' are workarounds.
* Concepts is the build in (future) solution.
* TMP functions can be used to define concepts

## Compiler Support?

* Visual Studio 2019 version 16.3 (10th September) supports concepts.

## Syntax

* If you have TMP type safety functions you can easily reuse them

    template <class T>
    inline constexpr bool is_incrementable_v = is_incrementable<T>::value;

    template<class T>
    concept Incrementable = is_incrementable_v<T>; // using already existing TMP

* Concepts are composable:

    template <class T>
    concept PseudoIterator =
    is_pointer_v<T> ||
    (is_class_v<T> && Incrementable<T>);

* Concepts vs enable_if

    template <PseudoIterator T> auto nnext(T iter) -> T {
        return ++iter;
    }

* Concepts can do more

    template<class T>
    concept Iterator = requires(T iter) {
        typename T::type;
        { ++iter } -> ::std::convertible_to<T>;
        { *iter } -> ::std::convertible_to<typename T::type>;
    };

    template <Iterator T> auto next(T iter) -> T {
        return ++iter;
    }