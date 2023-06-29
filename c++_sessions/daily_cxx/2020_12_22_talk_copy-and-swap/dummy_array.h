#include <iostream>
#ifndef _DUMMY_ARRAY_H_
#define _DUMMY_ARRAY_H_
class Dummy_Array
{
private:
    std::size_t mSize;
    int* mArray;
public:
    //default constractor
    Dummy_Array(std::size_t size=0):mSize(size),mArray(mSize ? new int[mSize]() : nullptr)
    {
        std::cout << "in Dummy_Array(std::size_t size=0)"<<std::endl;
    }
    //copy-constractor
    Dummy_Array(const Dummy_Array &other);
    //assigment
    //Dummy_Array& operator=(const Dummy_Array& other);
    Dummy_Array& operator=(Dummy_Array other);
    //move-constructor
    Dummy_Array(Dummy_Array&& other) noexcept : Dummy_Array()//fist create a default one and then swap with rvalue reference.
    {
        std::cout << "in Dummy_Array::Dummy_Array(Dummy_Array&& other)"<<std::endl;
        swap(*this,other);
    }
    ~Dummy_Array()
    {
        delete [] mArray;
    }
    int& operator[](std::size_t index);

    friend void swap(Dummy_Array& first, Dummy_Array& second);
};
#endif
