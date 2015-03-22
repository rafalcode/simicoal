#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NG 20 /* number of generations */
#define PSZ 20 /* size of pop */

int main(int argc, char *argv[])
{
   int i, j;
   int **ra=malloc(NG*sizeof(int*));
   for(i=0; i<NG; i++)
       ra[i]=malloc(PSZ*sizeof(int));

   for(i=0; i<NG; i++)
   		for(j=0; j<PSZ; j++)
			ra[i][j]=(int)(PSZ*(((float)rand())/RAND_MAX));

   for(i=0; i<NG; i++) {
   		for(j=0; j<PSZ; j++)
			printf("%02d ", ra[i][j]);
		printf("\n");
	}


   for(i=0; i<NG; i++)
		free(ra[i]);
	free(ra);

   return 0;
}
