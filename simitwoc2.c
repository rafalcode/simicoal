#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cairo/cairo.h>

#define GBUF 2

typedef struct
{
    int il;
    int *ca;
    int casz;
    float hp, vp;
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
						printf("p_%d/idx_%d: ", i, pai[i].il);
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

void print2png(int width, int height, acixs *pai, int *apszs, int sz)
{
    int i, j, k;
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cairo_t *cr = cairo_create (surface);
    cairo_rectangle (cr, 0, 0, width, height); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);

    /* hpos first because they are easy */
    float vbarsz=(float)width/(sz+1);
    float *hpos=calloc((sz+1), sizeof(float));
    hpos[0]=(float)vbarsz/2.;
    for(i=1;i<(sz+1);++i) 
        hpos[i]=hpos[i-1]+vbarsz;

    /* now vpos */
    float hbarsz;
    for(k=0;k<sz;++k) {
        hbarsz=(float)height/(apszs[k+1]-apszs[k]);
        pai[apszs[k]].vp=(float)hbarsz/2.;
        pai[apszs[k]].hp=hpos[k+1];
        for(i=apszs[k]+1; i<apszs[k+1]; ++i) {
            pai[i].vp=pai[i-1].vp+hbarsz;
            pai[i].hp=hpos[k+1];
        }
    }

    cairo_set_source_rgba(cr, 1.0, 0.6, 1.0, 0.9);
    for(k=0;k<sz;++k) {
        for(i=apszs[k]; i<apszs[k+1]; ++i) {
#ifdef DBG
            printf("(%2.2f,%2.2f) ", pai[i].hp, pai[i].vp);
#endif
            cairo_arc(cr, pai[i].hp, pai[i].vp, 2, 0, 2 * M_PI);
            cairo_fill(cr);
        }
#ifdef DBG
        printf("\n"); 
#endif
    }

    cairo_set_source_rgba(cr, 0.65, 0.8, 0.45, 0.6);
    for(k=1;k<sz;++k) {
        for(i=apszs[k]; i<apszs[k+1]; ++i) {
            for(j=0; j<pai[i].casz; ++j) {
                cairo_move_to(cr, pai[i].hp, pai[i].vp);
                cairo_line_to(cr, pai[pai[i].ca[j]].hp, pai[pai[i].ca[j]].vp);
                cairo_stroke(cr);
            }
        }
    }

    cairo_surface_write_to_png (surface, "simidots.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);
    free(hpos);
}

int main(int argc, char *argv[])
{
		/* argument accounting: remember argc, the number of arguments, _includes_ the executable */
		if(argc!=4) {
				printf("Error. Pls supply 3 arguments 1) currPopSz 2) imgWidth 3) imgHeight.\n");
				exit(EXIT_FAILURE);
		}
		int i, j, *ra, *pa;
		acixs *pai;
		int pgbuf=GBUF;
		int *pca=malloc(pgbuf*sizeof(int));
		int *apszs=calloc(pgbuf+1, sizeof(int)); /* array of pai sizes */
		int pcpc=0; /* parent child pair counter */
		int IPSZ=atoi(argv[1]);
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
										pai[i].ca[idx++]=(pcpc>0)? j+apszs[pcpc-1] : j;
						/* ref. indices for a parent's children: How has it come to this you may ask? Well pcpc==0 is the initial children of the generation,
						 * and they must be treated seperately, they are not parents. And pcpc==1? well shouldn make a difference. */
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
		printpaip2(pai, apszs, pcpc);
		print2png(atoi(argv[2]), atoi(argv[3]), pai, apszs, pcpc);
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
