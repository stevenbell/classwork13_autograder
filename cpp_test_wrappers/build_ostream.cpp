#include "array.h"
#include <iostream>

int main(int arcg, char* argv[])
{
  int values[] = {12, 13, 14, 15};
  Array arr(sizeof(values) / sizeof(values[0]), values);

  std::cout << "###" << arr << "###" << std::endl;
  
  return(0);
}

