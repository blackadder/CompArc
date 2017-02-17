/**
 * Be sure to add terminal commands,
 * along with file input.
 *
 */
#include <stdio.h> 
#include <stdlib.h>

int main(int argc, char** argv){
    int i, j, m, n;

    FILE *fp;
    fp = fopen(argv[1], "r");
    char *line = NULL;
    size_t len = 0;
    //ssize_t read;

    getline(&line, &len, fp);
    sscanf(line, "%d %d", &m, &n);
    int m1[m][n], m2[m][n], sum[m][n];
    
    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
	    fscanf(fp, "%d", &m1[i][j]);
                 
    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
	    fscanf(fp, "%d", &m2[i][j]);
                
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            sum[i][j] = m1[i][j] + m2[i][j];
            printf("%d\t", sum[i][j]);
        }
	if(i!=m-1)
	  printf("\n");
    }      
    putchar('\n');
    return 0;
}
