#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IPSZ 16 /* initial size of pop */
#define GBUF 2

typedef struct
{
    int il;
    int *ca;
    int casz;
} acixs;

void printpaip(acixs *pai, int start, int end) /* print a part of the pai container*/
{
    int i, j;
    for(i=start;i<end;++i) {
        printf("%d) parent %d: ", i, pai[i].il);
        for(j=0; j<pai[i].casz; j++)
            printf("%d ", pai[i].ca[j]);
        printf("\n"); 
    }
    printf("----------------------------\n"); 
}

void printpaip2(acixs *pai, int *apszs, int sz) /* print a part of the pai container*/
{
		int i, j, k;
		for(k=0;k<sz;++k) {
				for(i=apszs[k]; i<apszs[k+1]; ++i) {
						printf("%d) parent %d: ", i, pai[i].il);
						for(j=0; j<pai[i].casz; j++)
								printf("%d ", pai[i].ca[j]);
						printf("\n"); 
				}
				printf("----------------------------\n"); 
		}
}

void printpaip3(acixs *pai, int *apszs, int sz) /* print a part of the pai container*/
{
    int i, j, k;
    for(k=0;k<sz;++k) {
        printf("PrevGen %d ", k+1); 
        printf("(%d parents): ", apszs[k+1]-apszs[k]); 
        for(i=apszs[k]; i<apszs[k+1]; ++i) {
            printf("{p_%d: [", pai[i].il + apszs[k]);
            for(j=0; j<pai[i].casz; j++)
                printf("%d ", pai[i].ca[j]);
            printf("]} "); 
        }
        printf("\n"); 
    }
}

int main(int argc, char *argv[])
{
    int i, j, *ra, *pa;
    acixs *pai;
    int pgbuf=GBUF;
    int *pca=malloc(pgbuf*sizeof(int));
    int *apszs=calloc(pgbuf+1, sizeof(int)); /* array of pai sizes */
    int pcpc=0; /* parent child pair counter */
    pca[pcpc]=IPSZ;

    int paibuf=GBUF;
    pai=malloc(paibuf*sizeof(acixs));

    // while( (apszs[pcpc+1]-apszs[pcpc]) != 1) { // failed miserably
    while( pca[pcpc] > 1) {

        ra=malloc(pca[pcpc]*sizeof(int));
        pa=calloc(pca[pcpc], sizeof(int)); /* parent array .. the number of siblings */

        for(j=0; j<pca[pcpc]; j++) {
            ra[j]=(int)(pca[pcpc]*(((float)rand())/RAND_MAX));
            pa[ra[j]]++;
        }

        for(j=0; j<pca[pcpc]; j++)
            if(pa[j]) {
                if(apszs[pcpc+1] ==paibuf-1) {
                    paibuf += GBUF;
                    pai=realloc(pai, paibuf*sizeof(acixs));
                }
                pai[apszs[pcpc+1]].il=j;
                pai[apszs[pcpc+1]].casz=pa[j];
                pai[apszs[pcpc+1]].ca=malloc(pai[apszs[pcpc+1]].casz*sizeof(int));
                apszs[pcpc+1]++;
            }

        free(pa);
        int idx;
        for(i=apszs[pcpc];i<apszs[pcpc+1];++i) {
            idx=0;
            for(j=0; j<pca[pcpc]; j++)
                if(pai[i].il==ra[j])
                    pai[i].ca[idx++]=j;
        }

        free(ra);

        pcpc++; /* watch this guy .. divides th while in two */
        if(pcpc==pgbuf) {
            pgbuf += GBUF;
            pca=realloc(pca, pgbuf*sizeof(int));
            apszs=realloc(apszs, (pgbuf+1)*sizeof(int));
        }
        pca[pcpc]=apszs[pcpc]-apszs[pcpc-1];
        apszs[pcpc+1]=apszs[pcpc];
    }
    printpaip3(pai, apszs, pcpc);
    putchar('\n');
    printf("Pop size %d took %d gens to coalesce backwards to 1 MRCA.\n", IPSZ, pcpc); 
    for(i=0;i<=pcpc;++i) 
        printf("%2d ", pca[i]);
    printf("\n"); 
    for(i=0;i<=pcpc;++i) 
        printf("%2d ", apszs[i]);
    printf("\n"); 

    for(i=0;i<apszs[pcpc+1];++i)
        free(pai[i].ca);
    free(pai);

    free(pca);
    free(apszs);
    return 0;
}
