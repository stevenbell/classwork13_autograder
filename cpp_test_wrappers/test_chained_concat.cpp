#include "array.h"

int main(int arcg, char* argv[])
{
  Array one(10, 1);
  Array two(10, 2);
  Array three(3, 3);
  Array four;

  four = one + two + three;
  
  int result = four.size();
  if(result == 10 + 10 + 3){
      printf("###PASS###");
  }
  else{
      printf("###Expected size of %d but got %d###", 10 + 10 + 3, result);
  }


  return(0);
}

