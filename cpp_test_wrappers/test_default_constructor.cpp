#include "array.h"

#define SIZE 0

int main(int arcg, char* argv[])
{
  Array arr;

  int result = arr.size();
  if(result == SIZE){
    printf("###PASS###");
  }
  else{
    printf("###Expected size of %d but got %d###", SIZE, result);
  }

  return(0);
}

