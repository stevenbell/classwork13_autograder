// Implement a version of `new` that fails on command
// Based on https://stackoverflow.com/questions/1923664/simulating-low-memory-using-c
#include <cstdlib>
#include <iostream>
#include "array.h"
// Global flag that sets whether or not `new` will fail
bool memoryAllocFail = false; // Succeed by default

// Custom implementation of new
void* operator new(std::size_t size)
{
    std::cout << "New allocation of size " << size << std::endl;
    if (memoryAllocFail)
    {
       throw std::bad_alloc();
    }

    return malloc(size);
}

void operator delete(void* block)
{
    std::cout << "Freed allocation" << std::endl;
    free(block);
}

int main(int argc, char* argv[])
{
    Array<int> a(5, 0);
    try {
          std::cout << a[10] << std::endl;
          std::cout << "Index is out of bounds -- should throw exception" << std::endl;
    }
    catch (const std::exception& e){
          std::cout << e.what() << std::endl;
    }
    return(0);
}

