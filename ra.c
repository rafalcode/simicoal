/* trying to do a rand bit caller, failing miserably */
#include <stdio.h> /* for printing */
#include <stdlib.h> /* contains the rand function */

typedef struct
{
    unsigned long *c; /* container */
    int nfc; /* number of full containers +1 for the partial */
    int npc; /* number of partials in final */
} rholder;

rholder *givmerbits(int quan) /* give me a number of rand bits */
{
   rholder *rh=malloc(sizeof(rholder));
   unsigned lsz=sizeof(long);
   rh->nfc=1+(quan-1)/lsz;
   rh->c=malloc(rh->nfc*lsz);
   rh->npc=quan%lsz;

   int f31s=1+(quan-1)/(sizeof(int)-1); /* most prob 31 */
   for(i=0;i<fsz;++i) {
   unsigned int r=rand();
   printf("drawn: %d from max %d\n", r, RAND_MAX);

   return rh;
}

int main(int argc, char *argv[])
{

   unsigned int r=rand();
   printf("drawn: %d from max %d\n", r, RAND_MAX);

   return 0;
}
