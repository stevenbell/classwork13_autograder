#include <cstdio> 
#include "array.h"

#define LEN 5

int main(int arcg, char* argv[])
{
  Array one(LEN, 0);
  Array two = one;

  // Check that arr has same length 
  if(two.size() != LEN){
      printf("###Expected copied array to have size of %d but got %d###", LEN, two.size());
      return(0);
  }

  // Check that the values are right
  for(int i = 0; i < LEN; i++){
      if(two[i] != one[i]){
          printf("###Copied value doesn't match at index %d###", i);
          return(0);
      }
  }

  // Now modify 
  for(int i = 0; i < LEN; i++){
      two[i] = i;
  }

  // Make sure original array was not modified
  for(int i = 0; i < LEN; i++){
      if(one[i] != 0){
          printf("###Original array was modified by copy at index %d###", i);
          return(0);
      }
  }


  printf("###PASS###");


  return(0);
}


