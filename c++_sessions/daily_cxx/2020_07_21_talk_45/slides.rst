Welcome to Daily C++ episode 45. The first C++ Bosch Tube channel for C++
developers by C++ developers. I'm your host Chris Power. In today's episode I
want to thank all listeners for supporting this show by watching, liking and
criticizing the content. In this episode I want like to respond to some
feedback. A lot of listeners have reported that the C++ knowledge level is
quite high. So I was searching for a beginner topic, which simultaneously is
not boring for more advanced programmers. The topic of this Daily C++ and the
next ones will be: "Writing a Program".

We start with a quote from Kristen Nygaard:

"Programming is understanding."

Why did we chose this topic? Writing a program involves gradually refining your
ideas of what you want to do and how you want to express it. In this lecture
and the next, we will develop a program from a first vague idea through states
of analysis, design, implementation testing, redesign, and
re-implementation. Our aim is to give you some idea of the kind of thinking
that goes on when you develop a piece of code. In the process we discuss
program organization, user-defined types, and input processing.

Writing a program starts with a problem; that is you have a problem that you'd
like a program to help solve. Understanding that problem is key to a good
program. As a exercise we choose: Writing a simple calculator. Why a
calculator? Because this

* illustrates design and programming techniques.
* It further, gives us a chance to explore the kinds of decisions that a
  programmer must make and the considerations that go into such decisions.
* It is complicated enough to require thought about its design,
* while allowing for many variations in its solution.
* It solves an easily understood problem,
* and solves a problem that's worth solving.
* And finally, it has a solution that is small enough to completely present and
  completely comprehend.

E.g. if we enter "2+3.1*4" the program should respond "14.4".

So how do we start? Basically, think a bit about the problem and how to solve
it. First think about what the program should do and how you'd like to interact
with it. Later, you can think about how the program could be written to do
that. Try writing down a brief sketch of an idea for a solution, and see what's
wrong with that first idea. Maybe discuss the problem and how to solve it with
a friend. Trying to explain something to a friend is a marvelous way of
figuring out what's wrong with idea, even better than writing them down; paper
(or a computer)  doesn't talk back at you and challenge your
assumptions. Ideally, design isn't a lonely activity.

Here are the stages of development:

- *Analysis*: Figure out what should be done and write a description of your
  (current) understanding of that. Such a description is called a *set of
  requirements* or a *specification*.
- *Design*: Create an overall structure for the system, deciding which parts
  the implementation should have and how those parts should communicate. As
  part of the design consider which tools - such as libraries - can help you
  structure the program.
- *Implementation*: Write the code, debug it, and test that it actually does
  what it is supposed to do.

Here are some strategies that help with many programming projects:

- What is the problem to be solved?
  - Is the problem statement clear? For real problems, it never is. There are
    two common pitfalls here: We solve the wrong problem and we ask for too
    much. It is almost always better to ask for less to make a program easier
    to specify, easier to understand, easier to use, and (hopefully) easier to
    implement. Once it works, we can always build a fancier "version 2.0" based
    on our experience.
  - Does the problem seem manageable given the time, skills, and tools
    available? If not, consider to acquire more resources (especially more
    time) or (best of all) modify the requirements to simplify your task.
- Try breaking the program into manageable parts. Even the smallest program for
  solving a real problem is large enough to be subdivided.
  - Do you know of any tools, libraries, etc. that might help?
  - Look for parts of a solution that can be separately described (and
    reused). This requires experience, but for know consider the following
    analogy: If we were to design a car, we would start by identifying parts,
    such as wheels, engine, seats, door handles, etc., on which we could work
    separately befor assembling the complete car. A real-world program is no
    different in that respect, except of course that the parts are
    code. Designing and implementing such parts is a major theme of software
    development in general.
- Build a small, limited version of the program that solves a key part of the
  problem. When we start, we rarely know the problem well. We often think we
  do (don't we know what a calculator program is?), but we don't. Only a
  combination of thinking about the problem (analysis) and experimentation
  (design and implementation) gives us the solid understanding that we need to
  write a good program. So, we build a small, limited version
  - To bring out problems in our understanding, ideas, and tools.
  - To see if details of the problem statement need changing to make the problem
    manageable.

    Sometimes, such a limited initial version aimed at experimentation is called a
    *prototype*. If (as is likely) our first version doesn't work or is so ugly and
    awkward that we don't want to work with it, we throw it away and make another
    limited version based on our experience. Repeat until we find a version that we
    are happy with. Do not proceed with a mess; messes just grow with time.
- Build a full-scale solution, ideally by using parts of the initial version.
    

Drill
1. Create a simple 'CMakeLists.txt' that adds your calculator program.

Review
1. What do we mean by "Programming is understanding"?
2. Write a short analysis of what the calculator should be able to do.
3. How do you break a problem up into smaller manageable parts?
4. Why is creating a small, limited version of a program a good idea?

Terms
- analysis
- design
- prototype
- implementation

Exercises
1. Recall the three stages of development. Try to apply them by restricting
   yourself to a prototype, which is only able to handle integer plus integer
   or integer minus integer. Use the suggested strategies for help.
