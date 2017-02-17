#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  int i, j, k, m, n, o, p, sum;
  sum = 0;

  FILE *fp;
  fp = fopen(argv[1], "r");
  //char *line = NULL;
  //size_t len = 0;

  if(argc < 2){
    return -1;
  }
  
  //First Matrix Size
  fscanf(fp, "%d %d", &m, &n);
  int ma1[m][n];

  //Pluggin in Matrix 1's elements
  for(i=0; i<m; i++)
    for(j=0; j<n; j++)
      fscanf(fp, "%d", &ma1[i][j]);

  //Second Matrix Size
  fscanf(fp, "%d %d", &o, &p);

  if(n != o){
    printf("error\n");
    return(-1);
  }

  //Declares Remaining Matrices
  int ma2[o][p];
  int product[m][p];


  //Plugging in Matrix 2's elements
  for(i=0; i<o; i++)
    for(j=0; j<p; j++)
      fscanf(fp, "%d", &ma2[i][j]);

  //Gives the product matrix a null value
  //to make debugging easier
  for(i=0; i<m; i++)
    for(j=0; j<p; j++)
      product[i][j] = 0;


  for(i=0; i<m; i++){
    for(j=0; j<p; j++){
      for(k=0; k<o; k++){
	sum = sum + (ma1[i][k] * ma2[k][j]);
      }
      product[i][j] = sum;
      sum = 0;
    }
  }
  
  //prints product matrix
  for(i=0; i<m; i++){
    for(j=0; j<p; j++){
      printf("%d\t", product[i][j]);
    }
    putchar('\n');
  }

  putchar('\n');
  return 0;
}
