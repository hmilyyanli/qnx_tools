# Daily C++ - Ep 16 - Decorator

## Intent

Attach additional responsibilities to an object dynamically. Decorators provide
a flexible alternative to subclassing for extending functionality.

## Motivation

Sometimes we want to add responsibilities to individual objects, not to an
entire class. 

For example streams are a fundamental abstraction in most I/O facilities. A
stream can provide an interface for converting objects into a sequence of bytes
or characters. That lets us transcribe an object to a file or to a string in
memory for retrieval later. A straight forward way to do this is to define an
abstract stream class with subclasses MemoryStream and FileStream. But suppose
we also want to be able to do the following:

* Compress the stream data using different compression algorithms (runlenth
  encoding, Lempel-Ziv, etc)
* Reduce the stream data to 7-bit ASCII characters so that it can be
  transmitted over an ASCII communication channel.

This also can be solved by subclassing, but at the cost of high module
coupling.

The Decorator pattern gives us an elegant way to add these responsibilities to
streams without increasing module coupling. The diagram bellow shows one
solution to the problem:

![Stream example](stream.svg)

The Stream abstract class maintains an internal buffer and provides operations
for storing data onto the stream (PutString). Whenever the buffer is full,
Stream calls the abstract opertions HandleBufferFull, which does the actual
data transfer. The FileStream version of this operation overrides this
operation to transfer the buffer to a file.

The key class here is the StreamDecorator, which maintains a reference to a
component stream and forwards requests to it. StreamDecorator subclasses
override HandleBufferFull and perform additional actions before calling
StreamDecorators HandleBufferFull operation.

For example, the CompressingStream subclass compresses the data, and the
ASCII7Stream converts the data into 7-bit ASCII. Now, to create a FileStream
that compresses its data _and_ converts the compressed binary data to 7-bit
ASCII, we decorate a FileStream with a CompressingStream and an ASCII7Stream:
