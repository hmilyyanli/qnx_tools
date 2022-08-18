# Daily C++ (#1) 27.09.2019

## Introduction

* Template Meta Programming (TMP)
* Meta Programming: Manipulating program entities, such as classes and
  functions.
* Templates are like generators.
* TMP: two-level programming, multilevel programming, generative programming
* Why TMP:

  - Improved type safety.
  - Improved run-time performance.

* Common critics:

  - Code looks very different (TMP is a language within C++) 
  - Code is very hard to read and understand.

## Problem

* Example for improved type saftety: We want

      T next(T iter), 

  where 'T' is a pointer or a class with 'operator++()'.
* How do we restrict 'T'? C.f. 'template_meta_programming.cpp'.

## Basics

* Unknown keywords:

  - decltype(...)                               (C++11)
  - template<class T> inline constexpr bool ... (C++17)
  - true_type, false_type                       (C++11)
  - void_t                                      (C++14)
  - declval()                                   (C++11)

* 'decltype' is a built-in keyword.

      decltype(expression)

  is the type of the expression. E.g. 'decltype(1 + 1.)' has the type
  'double'. The expression is not going to be evaluated at run-time. Roughly
  the following code is equivalent:

      decltype(1 + 1.) var1 = 1 + 1.;
      auto             var2 = 1 + 1.;

* 'void_t' can be implemented using (C++11) as follows:

      template<class...> using void_t = void;

   A better name for 'void_t' would be perhaps 'try_to_instantiate'. In some
   sense it is a 'static_cast<void>()' for TMP.

* 'true_type' and 'false_type' are type, which represent the value 'true' and
  'false' as a class. The implementation is based on the following class

      template<class T, T v>
      struct integral_constant {
          static constexpr T value = v;
          using value_type = T;
          using type = integral_constant;
          constexpr operator T() const noexcept { return value; }
          constexpr T operator()() const noexcept { return value; }
      };

      using true_type = integral_constant<bool, true>;
      using false_type = integral_constant<bool, false>;
