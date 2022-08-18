# Daily C++ Vol. 8 | 28.10.2019

# State Pattern

## Intent

> Allow an object to alter its behavior when its internal state changes. The
> object will appear to change its class.

## Motivation

We have a *TCPConnection* object has members open, synchronize, send and close.
Its behavior depends on whether the TCPConnection is established, listening or
closed. Key idea: Introduce abstract interface *TCPState*, which represents the
state of a TCPConnection.

## Applicability

- An oject's behavior depends on its state, and it must change its behavior at
  run-time depending on that state.
- You have the urge to use one or more enumerated constants to reflect some
  complicated state.

## ASCII Graph Creator

http://asciiflow.com/