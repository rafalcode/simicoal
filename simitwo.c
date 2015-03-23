#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IPSZ 22 /* initial size of pop */
#define GBUF 2

typedef struct
{
    int il;
    int *ca;
    int casz;
} acixs;


int main(int argc, char *argv[])
{
    int i, j, *ra, *pa;
    acixs *pai;
    int npcps=10; /* number of parent child pairs */
    int pgbuf=GBUF;
    int *pca=malloc(pgbuf*sizeof(int));
    int pcpc=0; /* parent child pair counter */
    pca[pcpc]=IPSZ;

    int pszc, gbuf;

    while(pca[pcpc]>1) {

        ra=malloc(pca[pcpc]*sizeof(int));
        pa=calloc(pca[pcpc], sizeof(int)); /* parent array .. the number of siblings */

        for(j=0; j<pca[pcpc]; j++) {
            ra[j]=(int)(pca[pcpc]*(((float)rand())/RAND_MAX));
            pa[ra[j]]++;
        }

        pszc=0; /* parent array size counter */
        gbuf=GBUF;
        pai=malloc(gbuf*sizeof(acixs));

        for(j=0; j<pca[pcpc]; j++)
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
            for(j=0; j<pca[pcpc]; j++)
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
        printf("----------------------------\n"); 

        for(i=0;i<pszc;++i)
            free(pai[i].ca);
        free(pai);

        pcpc++;
        if(pcpc==pgbuf) {
            pgbuf += GBUF;
            pca=realloc(pca, pgbuf*sizeof(int));
        }
        pca[pcpc]=pszc;
    }

    free(pca);
    return 0;
}
