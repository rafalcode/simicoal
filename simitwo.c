#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IPSZ 10 /* initial size of pop */
#define GBUF 2

typedef struct /* acixs type: ca an array of ints, casz its size and int il ??? */
{
    int il;
    int *ca;
    int casz;
} acixs;

void printpaip(acixs *pai, int pszc) /* print a part of the pai container*/
{
    int i, j;
    for(i=0;i<pszc;++i) {
        printf("%d) parent %d: ", i, pai[i].il);
        for(j=0; j<pai[i].casz; j++)
            printf("%d ", pai[i].ca[j]);
        printf("\n"); 
    }
    printf("----------------------------\n"); 
}

int main(int argc, char *argv[])
{
    int i, j, *ra=NULL, *pa=NULL;
    acixs *pai;
    int pgbuf=GBUF;
    int *pca=malloc(pgbuf*sizeof(int));
    int *apszs=malloc((1+pgbuf)*sizeof(int)); /* array of pai sizes */
    int pcpc=0; /* parent child pair counter */
    pca[pcpc]=IPSZ; /* an initial value for member 0 */
    apszs[0]=0;

    int pszc, gbuf;
#ifdef DBG
        printf("Initial size of pop is %i\n", IPSZ); 
#endif

    while(pca[pcpc]>1) {

        ra=malloc(pca[pcpc]*sizeof(int));
        pa=calloc(pca[pcpc], sizeof(int)); /* parent array .. the number of siblings */

        /* Go through each individ, and randomly select which parpair is may have come from
         * Note a more naive appraoch would have risked having parpairs responsible for more
         * than the current pop size, which would be incorrect */
        for(j=0; j<pca[pcpc]; j++) {
            /* ra[j] to be a random int btwn 0 and pca[pcpc],
             * this is a way of having the current individ say which
             * parpair it came from */
            ra[j]=(int)(pca[pcpc]*(((float)rand())/RAND_MAX));
            pa[ra[j]]++; 
        }
#ifdef DBG
        printf("An array pa[] has been built.\n"); 
        printf("each member holds the number of times its index coincided with a random integer.\n");
        for(j=0; j<pca[pcpc]; j++)
            printf("%i ", pa[j]); 
        printf("\n"); 
#endif

        pszc=0; /* parent array size counter */
        gbuf=GBUF;
        pai=malloc(gbuf*sizeof(acixs));

        for(j=0; j<pca[pcpc]; j++)
            if(pa[j]) { /* i.e. a parent-pair that had at least one offspring */
                if(pszc ==gbuf-1) {
                    gbuf += GBUF;
                    pai=realloc(pai, gbuf*sizeof(acixs));
                }
                pai[pszc].il=j; /* index of the parpair */
                pai[pszc].casz=pa[j]; // number of offspring for this parpair
                pai[pszc].ca=malloc(pai[pszc].casz*sizeof(int)); // preallocate their offspring array
                pszc++; // total number of parpairs that produced at least 1 offspring
            }

        /* time to free pa[] ... it also had the parpairs that did not reproduce, which 
            is no longer of any interest, and it's all transferred to pai[], so: get rid of */
        free(pa);

        /* now we have to assign which offspring each of the reproducing parpairs were responsible for.
         * ra[] still hasa */
        int idx;
        for(i=0;i<pszc;++i) { /* essentially, this is a new index for the parpairs */
            idx=0;
            for(j=0; j<pca[pcpc]; j++) 
                /* Now, ra[j] still has the parpair choice each individ made
                 * so, somewhat the reverse action of before, we select the individ for that parent */
                if(pai[i].il==ra[j]) 
                    pai[i].ca[idx++]=j;
        }

        free(ra);
        printpaip(pai, pszc);

        /* we could store this, but for the time being, delete it */
        for(i=0;i<pszc;++i)
            free(pai[i].ca);
        free(pai);

        pcpc++; // advance our generation
        if(pcpc==pgbuf) {
            pgbuf += GBUF;
            pca=realloc(pca, pgbuf*sizeof(int));
            apszs=realloc(apszs, (pgbuf+1)*sizeof(int));
        }
        pca[pcpc]=pszc;
        apszs[pcpc]=apszs[pcpc-1]+pszc;
    }
    putchar('\n');
    printf("Pop size %d took %d gens to coalesce backwards to 1 MRCA.\n", IPSZ, pcpc); 
    for(i=0;i<=pcpc;++i) 
        printf("%d ", apszs[i]);
    printf("\n"); 

    free(pca);
    free(apszs);
    return 0;
}
