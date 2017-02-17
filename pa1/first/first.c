#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
  int n;
  int i;

  if(argc<2){		//Checks if there is an argument
    printf("error\n");
    return 0;
  }

  n = atoi(argv[1]);

  if(n<2){		//Checks if arugment is prime
    printf("no\n");
  }
  else{
    for(i=2; i<=n-1; i++){
      if(n%i==0){
        printf("no\n");
        return(0);
      }
    }
    printf("yes\n");
  }
  return 0;
}

