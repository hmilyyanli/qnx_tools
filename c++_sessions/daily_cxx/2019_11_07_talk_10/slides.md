# Daily C++ - Ep 10 - Chain of Responsibility

## Intent

> Avoid coupling the sender of a request to its receiver by giving more than
> one object a chance to handle the request. Chain the receiving objects and
> pass the request along the chain until an object handles it.

## Motivation

I have a visualization application (visu) and want to provide a help method. A
user clicks on 'help' and the help information depends on the context; for
example a 'select input' window provides a different help, then a 'plot'
window. If no specific help information exists, then the help system gives a
general message.

We want to organize help information according to its generality.

Problem: The object who starts the request (help) does not know who will handle
it.

Idea: Decouple senders and receivers by giving multiple objects a chance to
handle a request (implicit receiver).

## Applicability

Use the Chain of Responsibility when

- more than one object may handle a request, and the handler isn't known a
  priori. The handler should be ascertained automatically.
- you want to issue a request to one of several objects without specifying the
  receiver explicitly
- the set of objects that can handle a request should be specified
  dynamically.
