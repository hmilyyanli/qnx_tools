# Daily C++ (#5)

## Why `std::move` for embedded? (Part 1)

## Resources in Programs

> A *resource* is something that has to be acquired and after some time has to
> be released.

## Examples

* Dynamic memory (new, delete resp. malloc, free)
* File (open, close)
* Threads (c'tor, join)
* mutex (lock, release)

## FVG3 Examples

* Daddy Receiver Ports (update, cleanup)
* Daddy Sender Ports (reserve, deliver)
* Assertion Handling (administrativeLock)

## RAII

Explicit resource is one of the most hardest programming tasks. For dynamic
memory there exists a workaround: garbage collector. Problem: Works only for
memory, not for Daddy resources. C++ generic solution is RAII.

> *Resource Acquisition Is Initialization* (RAII) is a programming technique
> which binds the life cycle of a resource to the lifetime of an object.

    void errorprone(){
        m_daddy.update();
        // do sth.
        m_daddy.cleanup()
    }   

    void better(){
        auto guard = makeUpdateGuard(m_daddy);
        // do sth.
    }

Observation:

  * RAII works with exceptions
  * RAII works with early return

Problem:

  * I have an object, but depndening on the situation, I want to release the
    resource earlier or later. => move assignemnt
    
