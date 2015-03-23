#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
	if(argc!=2) {
		printf("Error. Pls supply argument (integer: pop size for example).\n");
		exit(EXIT_FAILURE);
	}

   int sz=atoi(argv[1]);
   int masktsz=sizeof(unsigned long); /* mask type size */
   int masz=1+sz/masktsz; /* mask array size */
   int pcsz=sz%masktsz; /* partial mask size */

   unsigned long ma=malloc(masz*sizeof(unsigned long));

   printf("Res_1: %s\n", "somedata");

   return 0;
}
