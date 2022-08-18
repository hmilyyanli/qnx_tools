# Daily C++ (#7)

## Object Oriented Programming

1. What is Object Oriented Programming (OOP)?
2. Why should we use OPP?
3. How can I write elegant OOP?

## What is OOP?

> OOP is the usage of inheritance, run-time polymorphism and encapsulation.

1. Inheritance = derivation
2. Run-Time Polymorphism (dynamic dispatch, run-time dispatch) = virtual
   function
3. Encapsulation = private and protected members (protect access of
   implementation details)

## Why should we use OOP?

OOP gives us

1. Implementation inheritance (derived class can use facilities in the base
   class)
2. Interface inheritance (program against interfaces not implementations)

The last point is critical: We can add new implementations without modifying
existing code. This is the holy grail of software design/ development/
maintenance!

By using OOP correctly we can eliminate a link and compile dependency to any
implementation.

## How can I write elegant OOP?

Own experience or by examples of other people:

> Design Patterns - Elements of Reusable Object-Oriented Software - Erich
> Gamma, Richard Helm, Ralph Johnson, John Vlissides

> John Lakos - Large-Scale C++ Software Design

The former book describes simple and elegant solutions to specific problems in
OO software design. 

There are three major categories of patterns:

  1. Creational Patterns - Abstract the instantiation process.
  2. Structural Patterns - How to compose classes and objects to form larger
     structures. 
  3. Behavioral Patterns - Shift focus away from control flow to how objects
     are interconnected.
