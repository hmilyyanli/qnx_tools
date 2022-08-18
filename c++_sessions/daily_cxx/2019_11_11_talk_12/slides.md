# Daily C++ - Ep 12 - Iterator Pattern

## Intent

> Provide a way to access the elements of an aggregate object sequentially
> without exposing its underlying representation.

## Motivation

An aggregate object such as a list should give you a way to access its elements
without exposing its internal structure. Further, we want

- to traverse the list in different ways,
- to keep the interface minimal (no bloat of the list interface).

The key idea in this pattern is to take the responsibility for access and
traversal out of the list object and put it into an iterator object.

## Applicability

Use the iterator pattern

- to access an aggregate object's content without exposing its internal
  representation.
- to support multiple traversals of aggregate objects.
- to provide a uniform interface for traversing different aggregate structures
  (that is, to support polymorphic iteration).

## Consequences

The iterator pattern has three important consequences:

1. It supports variations in the traversal of an aggregate.
2. Iterators simplify the Aggregate interface.
3. More than one traversal can be pending on an aggregate.
