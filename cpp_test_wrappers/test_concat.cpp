#include "array.h"

int main(int arcg, char* argv[])
{
  Array one(10, 1);
  Array two(10, 2);
  Array three;

  three = one + two;

  int result = three.size();
  if(result == 10 + 10){
      printf("###PASS###");
  }
  else{
      printf("###Expected size of %d but got %d###", 10 + 10, result);
  }

  return(0);
}

