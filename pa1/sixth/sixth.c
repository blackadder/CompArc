#include <stdio.h>

int main(int argc, char* argv[]){
  int i;

  if(argc < 2)
    printf("error");

  for(i=1; i<argc; i++){
    printf("%c", argv[i][0]);
  }

  putchar('\n');
  return 0;
}
