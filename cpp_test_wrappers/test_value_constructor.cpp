#include "array.h"

int main(int arcg, char* argv[])
{
  Array arr(5, 0);
  
  if(arr.size() != 5){
      printf("###Expected copied array to have size of %d but got %d###", 5, arr.size());
      return(0);
  }

  for(int i = 0; i < 5; i++){
      if(arr[i] != 0){
          printf("###Initial value incorrect at index %d###", i);
          return(0);
      }
  }
  

  printf("###PASS###");
  return(0);
}

