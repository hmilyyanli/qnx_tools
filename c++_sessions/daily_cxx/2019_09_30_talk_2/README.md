# Daily C++ (#2) 30.09.2019

## Recap

* Template Meta Programming (TMP)
* Improved type safety example:

      template<class T> T next(T iter)

  only if 'T' is a pointer or class with 'operator++'.
* 1. Step: (Own Predicate)

      template<class T> inline constexpr bool is_incrementable_v = ...

## 2. Step: (enable_if)

* 'enable_if' resp. 'enable_if_t' provides the semantic of a *conditional
  definition*.
* It is easy to use:

      template<class T>
      enable_if_t<is_incrementable_v<T>, T> next(T iter);

  or more readable

      template<class T>
      auto next(T iter) -> enable_if_t<is_incrementable_v<T>, T>;

* This means: 'next' is only available if 'is_incrementable_v<T>' is 'true'.
* We can concatenate predicates to get our goal predicate:

      template<class T>
      struct is_iterator : integral_constant<bool,
             is_pointer_v<T> || (is_class_v<T> && is_incrementable_v<T>)> {};
      template<class T>
      inline constexpr bool is_iterator_v = is_iterator<T>::value;

* Goal achieved with:

      template<class T>
      auto next(T iter) -> enable_if_t<is_iterator_v<T>, T>{ return ++iter; }

## How does 'enable_if' works?

       template<bool B, class T = void>
       struct enable_if{ using type = t; };

       template<class T>
       struct enable_if<false, T>{};

       template<bool B, class T = void>
       struct enable_if_t = typename enable_if<B, T>::type;
