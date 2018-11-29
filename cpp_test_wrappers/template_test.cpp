#include <cstdio>
#include "array.h"

#ifdef TEMPLATE_TYPE_INT
#define TEMPLATE_TYPE int
#endif
#ifdef TEMPLATE_TYPE_CLASS
#define TEMPLATE_TYPE TestClass
#endif
#ifdef TEMPLATE_TYPE_INTPTR
#define TEMPLATE_TYPE int*
#endif


// Do-nothing test class which is used the the template type
class TestClass
{
public:
  TestClass() { mValue = 8; }
  bool operator==(const TestClass& rhs) { return rhs.mValue == mValue; }

  int mValue;
};

int main(int arcg, char* argv[])
{

#ifdef TEMPLATE_TYPE_INT
  // Default constructor
  Array<int> arr1;

  // append two values
  arr1.append(10);
  arr1.append(20);

  // Length-pointer constructor
  int eightvals[] = {2, 4, 6, 8, 10, 12, 14, 16};
  Array<int> arr2(8, eightvals);

#endif // TEMPLATE_TYPE_INT

#ifdef TEMPLATE_TYPE_CLASS
  Array<TestClass> arr1;
  TestClass a, b;
  arr1.append(a);
  arr1.append(b);

  // Length-pointer constructor
  TestClass eightvals[8];
  Array<TestClass> arr2(8, eightvals);
#endif // TEMPLATE_TYPE_CLASS

#ifdef TEMPLATE_TYPE_INTPTR
  Array<int*> arr1;

  int a, b; // Real values... not that we actually use them, though.
  arr1.append(&a);
  arr1.append(&b);

  // Length-pointer constructor
  int* eightvals[8] = {0};
  Array<int*> arr2(8, eightvals);
#endif // TEMPLATE_TYPE_INTPTR

  // size
  int result = arr1.size();
  if(result != 2){
    printf("###default constructor + append(): Expected size of %d but got %d###", 2, result);
    return(0);
  }

  result = arr2.size();
  if(result != 8){
    printf("###length-value constructor: expected size of %d but got %d###", 8, result);
    return(0);
  }

  // copy constructor + indexing
  // TODO: also check the size?
  Array<TEMPLATE_TYPE> arr3 = arr1;
  for(int i = 0; i < arr3.size(); i++) {
    if(!(arr3[i] == arr1[i])){
      printf("###copy constructor: mismatch at index %d###", i);
      return(0);
    }
  }

  // assignment
  // TODO: also check the size?
  arr2 = arr1;
  for(int i = 0; i < arr2.size(); i++) {
    if(!(arr2[i] == arr1[i])){
      printf("###assignment: mismatch at index %d###", i);
      return(0);
    }
  }

  // append array
  arr3.append(arr2);

  // chained + for concatenation
  Array<TEMPLATE_TYPE> arr4 = arr1 + arr1 + arr1;

  // x = x + y
  arr1 = arr1 + arr2;

  printf("###PASS###");
  return(0);
}

