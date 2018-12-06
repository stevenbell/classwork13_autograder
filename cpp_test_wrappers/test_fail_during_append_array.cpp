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
    Array<int> b(10, 0);
    memoryAllocFail = true;
    
    try {
        a.append(b);
    }
    catch (const std::exception& e){}
     
    if(a.size() != 5){
        printf("###Expected size of %d but got %d###", 5, a.size());
        return(0);
    }

    for(int i = 0; i < a.size(); i++){
        if(a[i] != 0){
            printf("###Couldn't access value %d###", i);
            return(0);
        }
    }   

    printf("###PASS###");
}

