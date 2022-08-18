# Daily C++ - Ep 14 - Static Initialization Order Fiasco

## Description

The static initialization order fiasco (SIOF) is a subtle way to crash your
program. It is a commonly misunderstood aspect of C++. Unfortunately it is very
hard to detect - the errors often occur before `main()` begins.

SIOF is a special type of unspecified behavior, which occurs if you try to
initialize a static object by using another static object.

Depending on the compiler there is a 50% change that your program gets
corrupted. The dangerous case is, if your program does not get corrupted and
you believe that everything is stable.

## Example 1

    class CSomeFiasco {  // vfc SI types fall here
      // DATA
      int m_x;
      int m_y;
    
    public:
      // CREATORS
      explicit CSomeFiasco(int f_z) : m_x{f_z}, m_y{2 * f_z} {}
    
      // ACCESSORS
      auto x() const -> int { return this->m_x; }
      auto y() const -> int { return this->m_y; }
    };
    
    const CSomeFiasco g_someFiasco1{10};
    const CSomeFiasco g_someFiasco2{g_someFiasco1.y()}; // oops

## Example 2

    #include <iostream>
    int f();  // forward declaration
    int g();  // forward declaration
    int x = f();
    int y = g();
    int f()
    {
      std::cout << "using 'y' (which is " << y << ")\n";
      return 3*y + 7;
    }
    int g()
    {
      std::cout << "initializing 'y'\n";
      return 5;
    }

## Solution 1: constexpr

The `constexpr` keyword grantees that there is no undefined behavior
allowed.

    class CNoFiasco {
      // DATA
      int m_x;
      int m_y;
    
    public:
      // CREATORS
      explicit constexpr CNoFiasco(int f_z) : m_x{f_z}, m_y{2 * f_z} {}
    
      // ACCESSORS
      constexpr auto x() const -> int { return this->m_x; }
      constexpr auto y() const -> int { return this->m_y; }
    };
    
    const CNoFiasco g_noFiasco{3};

* Pro
  - Very intuitive
  - Easy to implement
  - You get compile errors
  - Thread-safe
  - Can be used at compile time
* Con
  - Implies `const`
  - Works for modern classes.

## Solution 2: Construct on first use

Use a static variable inside a function or method to archive a similar effect:

    auto someFiasco3() -> const CSomeFiasco&{
        static const CSomeFiasco g_singelton{10};
        return g_singelton;
    }

* Pro
  - Easy to implement
  - Thread-safe for initialization
  - Can be mutable (non-const)
* Const
  - Has a minimal runtime overhead
  - Not thread-safe after initialization
  - Does not work with destructors with side effects.

## Solution 3: Niftly Counter Idiom

    // in header
    CSomeFiasco& g_someFiasco4;

    // some magic class here

* Pro
  - Can be mutable (non-const)
  - Has no runtime overhead
  - Works with destructors with side effects.
* Const
  - By default not thread-safe
  - Hard to implement


Full example will be shown in the next Daily C++.

## Literature

* https://isocpp.org/wiki/faq/ctors#static-init-order
* https://isocpp.org/wiki/faq/ctors#static-init-order-on-intrinsics
* https://stackoverflow.com/questions/36844393/c-nifty-counter-idiom-why
* https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Nifty_Counter
