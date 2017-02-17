#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
  int i, j, length;

  for(i=1; i<argc; i++){
    length = strlen(argv[i]);
    for(j=0; j!=length-1; j++){}
     printf("%c", argv[i][j]);
  }

  putchar('\n');
  return 0;
}
