#include "array.h"

int main(int arcg, char* argv[])
{
  Array one(10, 1);
  Array two(10, 2);
  Array three;

  three = one + two;

  return(0);
}

