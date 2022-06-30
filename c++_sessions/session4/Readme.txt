### function parameters and return value
f1: passed by value
a) parameter a is initialized by temparay object A(), no copy constructor method applied
b) move constructor in return statement to initialize a1, because a is a xvalue expression, it immediately goes out of scope
c) But no RVO applied

f2,f3 call by L-Value reference, f4 call be const reference
a) parameter a is associated with a1, no copy constructor
b) f2,f4 copy constructor is used in return statement to initialize a2,a4; f3 move constructor is used in return statement to init a3.

f5 f6 call by R-Value reference, 
a) parameter a is associated with temprary value A(), no copy constructor
b) f5 copy constructor is used in return value; f6 move constructor is used in return value.


