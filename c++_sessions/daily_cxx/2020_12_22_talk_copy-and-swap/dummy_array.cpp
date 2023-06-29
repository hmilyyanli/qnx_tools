#include "dummy_array.h"
//copy-constractor
Dummy_Array::Dummy_Array(const Dummy_Array& other)
{
    std::cout << "in Dummy_Array::Dummy_Array(const Dummy_Array& other)"<<std::endl;
    mSize=other.mSize;
    mArray=mSize? new int[mSize] : nullptr;
    std::copy(other.mArray, other.mArray + mSize, mArray);
}
/*
 *  a naive implementation has following issues:
 *  1) in most of time the self-assignment test is not needed and is a waste.
 *  2) if new int[mSize] fails, *this will have been modified.
 *  3) code duplication.
 */
#if 0
Dummy_Array& Dummy_Array::operator=(const Dummy_Array& other)
{
    std::cout << "in Dummy_Array::operator=(Dummy_Array& other)"<<std::endl;
    if (this != &other) // (1)
    {
        // get rid of the old data...
        delete [] mArray; // (2)
        mArray = nullptr; // (2) *(see footnote for rationale)

        // ...and put in the new
        mSize = other.mSize; // (3)
        mArray = mSize ? new int[mSize] : nullptr; // (3)
        std::copy(other.mArray, other.mArray + mSize, mArray); // (3)
    }
    return *this;
}
#else
 Dummy_Array& Dummy_Array::operator=(Dummy_Array other)
 {
     std::cout << "in Dummy_Array::operator=(Dummy_Array other)"<<std::endl;
     swap(*this, other); // (2)
     return *this;
 }
#endif
int& Dummy_Array::operator[](std::size_t index)
{
    return mArray[index];
}

void swap(Dummy_Array& first, Dummy_Array& second) // nothrow
{
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;
        // by swapping the members of two objects,
        // the two objects are effectively swapped
        swap(first.mSize, second.mSize);
        swap(first.mArray, second.mArray);
}

