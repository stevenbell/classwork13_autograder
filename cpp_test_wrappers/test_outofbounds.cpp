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
    const int LENGTH = 5;
    Array<int> a(LENGTH, 0);

    // Access the end of the array; this should work
    try {
        std::cout << a[LENGTH-1] << std::endl;
    }
    catch (const std::exception& e){
        std::cout << "###Test failed: legal index threw exception: " << e.what() << "###" << std::endl;
        return(0); // Test failed, just quit now
    }


    // Access before beginning of array; this should throw an exception
    try {
        std::cout << a[-1] << std::endl;
        std::cout << "###Test failed: indexing out of bounds didn't throw exception!###" << std::endl;
        return(0); // Test failed, just quit now
    }
    catch (const OutOfBoundsException& e){
        // All good so far
        std::cout << "Caught OutOfBoundsException" << std::endl;
    }
    catch (const std::exception& e){
        std::cout << "###Test failed: indexing out of bounds threw other exception: " << e.what() << "###" << std::endl;
        return(0); // Test failed, just quit now
    }


    // Access after end of array; this should throw an exception
    try {
        std::cout << a[LENGTH] << std::endl;
        std::cout << "###Test failed: indexing out of bounds didn't throw exception!###" << std::endl;
        return(0); // Test failed, just quit now
    }
    catch (const OutOfBoundsException& e){
        // So far, so good
        // Print out the "what", which will be checked in the test fixture
        std::cout << "###" << e.what() << "###" << std::endl;
    }
    catch (const std::exception& e){
        std::cout << "###Test failed: indexing out of bounds threw other exception: " << e.what() << "###" << std::endl;
        return(0); // Test failed, just quit now
    }

    return(0);
}

