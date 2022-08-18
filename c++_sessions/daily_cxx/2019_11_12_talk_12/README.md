# Daily C++ Vol. 12 | 12.11.2019

## Iterator pattern

# Intend
provide a way to access the elemts of an aggregate object sequencially without exposing its internal implementation

# Example
aggregate object (list) (daddy mempools in fvg3)
access its elements without exposing its internal structure

# further we want:
* traverse the list in different ways, (conditions have different depth, for example:)
	* "give me all daddy ports, no matter if they have new data or not"
	* all ports who have new data, ignore old ports
	* must have data and data must be valid
* interface should stay small

# key idea
the pattern should take the responsibility for access and traversal out of the list object and put it into an iterator object
