# Daily C++ Vol. 10 | 07.11.2019

## Motivation
Decouple sender and receiver of a request by setting up a handler which provides different possibilities to handle the request before aborting.

## Setting
We have a visu and want to provide a help method

## Requirements
The help information depends on the context. For example a "select sequence"-window provides different information than a "plot"-window. If no specific help information exists than the help system gives a general message.

## Problem
The object which starts the request (help) does not know who will handle it.

## Idea
Decouple senders and receiver by giving multiple objects a chance to handle the request (implicit receiver)

## Applicability
Use the chain of responsibility when more than one object may handle a request, and the handler isn't known a priori. The handler should be ascertained automatically. You want to issue a request to one or several objects without specifying the receiver explicitly. The set of objects that can handle a request should be specified dynamically.