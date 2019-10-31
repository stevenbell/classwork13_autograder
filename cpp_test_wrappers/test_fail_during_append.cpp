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
    const int MAGIC = 100;
    const int LENGTH = 5;

    Array<int> a(LENGTH, MAGIC);
    memoryAllocFail = true;
    
    try {
          a.append(MAGIC);
    }
    catch (const std::exception& e){}
     
    if(a.size() != LENGTH){
        printf("###Size of array changed despite exception! Expected size of %d but got %d###", LENGTH, a.size());
        return(0);
    }

    for(int i = 0; i < a.size(); i++){
        if(a[i] != MAGIC){
            printf("###Value at %d was modified despite exception!###", i);
            return(0);
        }
    }

    printf("###PASS###");
}

