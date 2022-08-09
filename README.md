# CppDriver

A simple driver written in C++, which implements IOCTL communication to track a specific module's usage and address in the system.
 
The driver does *not* use any external libraries, instead it implements some of the standard classes, like:
1. string
2. vector
3. dictionary

# Why C++?
Nonetheless C is the most popular language for kernel development, but C++, even when stripped off of standard libraries and of the
new/delete keywords, can still be very powerful. 
Most importantly C++ gives you access to templates, which makes it possible to create a vector.

# Extra notes
Classes implemented in this driver have a completely custom implementation. 
For intance vector is a doubly linked list, and this choice was due to the need for a very rudimental
garbage collector, which keeps track of allocated and deallocated memory pools, and during driver unload
frees any unfreed memory region, then deletes itself, leaving 0 memory leaks behind even in the worst case scenario.

# Why?
This simple driver can be used a skeleton to create a very simple/complex driver.
This project was done for research purposes and nothing else.
