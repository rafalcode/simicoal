#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PSZ 10 /* size of pop */
#define GBUF 4

typedef struct
{
    int il;
    int *ca;
    int casz;
} acixs;


int main(int argc, char *argv[])
{
    int i, j;
    int *ra=malloc(PSZ*sizeof(int));

    int *pa=calloc(PSZ, sizeof(int)); /* parent array .. the number of siblings */

    for(j=0; j<PSZ; j++) {
        ra[j]=(int)(PSZ*(((float)rand())/RAND_MAX));
        pa[ra[j]]++;
    }

    int pszc=0; /* parent array size counter */
    int gbuf=GBUF;
    acixs *pai=malloc(gbuf*sizeof(acixs));

    for(j=0; j<PSZ; j++)
        if(pa[j]) {
            if(pszc ==gbuf-1) {
                gbuf += GBUF;
                pai=realloc(pai, gbuf*sizeof(acixs));
            }
            pai[pszc].il=j;
            pai[pszc].casz=pa[j];
            pai[pszc].ca=malloc(pai[pszc].casz*sizeof(int));
            pszc++;
        }

    free(pa);
    int idx;
    for(i=0;i<pszc;++i) {
        idx=0;
        for(j=0; j<PSZ; j++)
           if(pai[i].il==ra[j])
               pai[i].ca[idx++]=j;
    }

    free(ra);

    for(i=0;i<pszc;++i) {
        printf("%d) parent %d: ", i, pai[i].il);
        for(j=0; j<pai[i].casz; j++)
            printf("%d ", pai[i].ca[j]);
        printf("\n"); 
    }

    for(i=0;i<pszc;++i)
        free(pai[i].ca);
    free(pai);

    return 0;
}
