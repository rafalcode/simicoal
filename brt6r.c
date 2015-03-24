/*============================================================
program: RootedTree.c                                        
continuing on from brt1, I wanted to print out node characteristics,
but including the two children, whether they be leaves or internal nodes.

The whole idea here is to let sequence order also be chronological order.

However, things also started getting a little bit complicated. In fact, me the expert was getting confused 
however, it did seem to be working. 
Felt I need to start visualing them in cairo ... cure brt3.c
==============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cairo/cairo.h>

#define MaxSize 64  /* max size of the tree */
#define NPINST 6

int n,                             /* number of nodes in a tree */
    par[MaxSize],                  /* parent position of i */
    lev[MaxSize],                    /* level of node i      */
    num,                          /* total number of trees */
    mc,                            /* max number of children */
    chi[MaxSize],                  /* number of children of a node */
    nextp[MaxSize],                /* next good pos to add nodes */
    rChi[MaxSize],                 /* the right most child of node i */
    levnum,                        /* specifies the number of levels in the tree */
    omit;                          /* a flag to omit unwanted tree */

int *levact, *culev, *cucul1;

typedef struct {
    int l, i, p, sc, /* sum of children which are internal nodes */ c[2] /* left child first, right child second */;
    float ip[2], c0p[2], c1p[2];
} innode;

void prinmat (innode *nar) /* print inode array matrix style,in "generated" order */
{
    int i, j;
    int **mat=malloc(NPINST*sizeof(int *));
    for(i=0; i<NPINST; i++)
        mat[i]= calloc(n, sizeof(int));

    for(j=0; j<n; j++) {
        mat[1][j] = nar[j].l;
        mat[0][j] = nar[j].i;
        mat[2][j] = nar[j].p;
        mat[3][j] = nar[j].sc;
        mat[4][j] = nar[j].c[0];
        mat[5][j] = nar[j].c[1];
    }

    printf("Our nodes in matrix arrangement:\n"); 
    for(i=0; i<NPINST; i++ ) {
        switch(i) {
            case 0: printf("I: "); break;
            case 1: printf("L: "); break;
            case 2: printf("P: "); break;
            case 3: printf("SC: "); break;
            case 4: printf("C0: "); break;
            case 5: printf("C1: "); break;
        }
        for(j=0; j<n; j++)
            printf("%02i ", mat[i][j]);
        printf("\n"); 
    }

    for(i=0; i<NPINST; i++)
        free(mat[i]);
    free(mat);
}

void setlevarrs(void)
{
    int i, j;

    for(i=0; i<=levnum; i++)
        for(j=1;j<=n;j++)
            if(lev[j]==i)
                levact[lev[j]]++; /* or lev[i]++, same thing */

    for(i=1;i<=levnum+1;++i) 
        culev[i] = culev[i-1]+levact[i-1];

    for(i=1;i<=levnum+2;++i) 
        cucul1[i] = cucul1[i-1]+culev[i-1]+1;

    printf("levact: "); 
    for(i=0;i<=levnum;++i) 
        printf("%i ", levact[i]);
    printf("culev: "); 
    for(i=0;i<=levnum+1;++i) 
        printf("%i ", culev[i]);
    printf("cucul1: "); 
    for(i=0;i<=levnum+2;++i) 
        printf("%i ", cucul1[i]);
    printf("\n"); 
}

void dealwithlev(char *fn, innode **ins)
{
    int i, j, wi=480, hi=480; 
    innode *tins= *ins;
    /* OK, start the hbars */
    float hbwid=(float)wi/(levnum+2);
    float *hpos=calloc(levnum+2, sizeof(float));
    hpos[0] = hbwid/2.;
    for(i=1;i<levnum+2;++i) 
        hpos[i] = hpos[i-1] + hbwid;

    /* And now the vbars */
    int vbxes; /* placeholder for number of vboxes in each hbar */
    float vbhei; /* place holder for height of each box int hat particular strip */
    float *vpos=calloc(cucul1[levnum+2], sizeof(float));
    for(i=1;i<levnum+3;++i) {
        vbxes=cucul1[i] - cucul1[i-1];
        vbhei = hi/vbxes;
        vpos[cucul1[i-1]] = vbhei/2;
        for(j=cucul1[i-1]+1; j<cucul1[i]; j++)
            vpos[j] = vpos[j-1] + vbhei;
    }

    int k, m;
    for(i=levnum+1; i>=1; --i) {
        k=m=1; /* one downmarker for the inode, and one for the two children. Easier to deal with this way */
        for(j=culev[i-1]; j<culev[i]; j++) {
            printf("%i:%i,%i|", tins[j].i, tins[j].c[0], tins[j].c[1]);
            tins[j].ip[0] = hpos[i-1];
            tins[j].c0p[0] = tins[j].c1p[0] = hpos[i];
            tins[j].ip[1] = vpos[cucul1[i]-k++];
            tins[j].c0p[1] = vpos[cucul1[i+1]-m++];
            tins[j].c1p[1] = vpos[cucul1[i+1]-m++];
            printf("h:%3.2f,v:%3.2f|", tins[j].ip[0], tins[j].ip[1]);
            printf("h:%3.2f,v:%3.2f|", tins[j].c0p[0], tins[j].c0p[1]);
            printf("h:%3.2f,v:%3.2f|", tins[j].c1p[0], tins[j].c1p[1]);
        }
        printf("\n"); 
    }

    /* OK, ready to go, you can stick in the cairo in here. */
    cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, wi, hi);
    cairo_t *cr = cairo_create (surface);
    cairo_rectangle (cr, 0, 0, wi, hi); /* arg explan: topleftcorner and size of shape  */
    cairo_set_source_rgba (cr, 0, 0, 0, 0.95); /*  final number is alpha, 1.0 is opaque */
    cairo_fill (cr);
    /* test concerns */
    cairo_select_font_face (cr, "Monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_font_extents_t fe;
    cairo_text_extents_t te;
    cairo_set_font_size (cr, 12.0);

    cairo_set_source_rgba(cr, 0.65, 0.8, 0.45, 0.6);
    
    char lab[3];
    for(i=levnum+1; i>=1; --i)
        for(j=culev[i-1]; j<culev[i]; j++) {
            cairo_arc(cr,tins[j].c0p[0], tins[j].c0p[1], 3, 0, 2*M_PI);
            cairo_fill(cr);
            cairo_move_to(cr,tins[j].c0p[0]+5, tins[j].c0p[1]);
            sprintf(lab, "%02i", tins[j].c[0]);
            cairo_text_extents (cr, lab, &te);
            cairo_show_text (cr, lab);
            cairo_move_to(cr,tins[j].c0p[0], tins[j].c0p[1]);
            cairo_line_to(cr,tins[j].ip[0], tins[j].ip[1]);
            cairo_line_to(cr,tins[j].c1p[0], tins[j].c1p[1]);
            cairo_move_to(cr,tins[j].c1p[0]+5, tins[j].c1p[1]);
            sprintf(lab, "%02i", tins[j].c[1]);
            cairo_text_extents (cr, lab, &te);
            cairo_show_text (cr, lab);
            cairo_stroke(cr);
        }

    cairo_surface_write_to_png (surface, fn);
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    free(vpos);
    free(hpos);
}

void sortinnodarr(innode **ins)/* and now sort on levels using rough insertion sort */
{
    int i, j;
    innode *tmp=calloc(1,sizeof(innode)), *tins = *ins;
    for(i=1; i<n; i++) {
        memcpy((void *)tmp, (void *)(tins+i), sizeof(innode));
        j = i-1;
        while(tmp->l < tins[j].l && j>=0) {
            memcpy((void *)(tins+j+1), (void *)(tins+j), sizeof(innode));
            j--;
        }
        memcpy((void *)(tins+j+1), (void *)tmp, sizeof(innode));
    }
    free(tmp);
}

void tostruct(innode **ins)
{ 
    innode *tins=*ins;
    int i, j, k, m, l;
    num = num+1;  
    if (num == 1 && omit ) {
        omit=0;
        num--;
    } else {
        for(i=n;i>=1;i--) {
            tins[i-1].l = lev[i];
            tins[i-1].i = i;
            tins[i-1].p = par[i]; /* tried: par[i]+1, but there's a trick there: the node itself by cardinal (not index) num */
            tins[i-1].sc = chi[i];
            switch (tins[i-1].sc) {
                case 1: tins[i-1].c[0] = i+1; break;
                case 2: tins[i-1].c[0] = i+1; tins[i-1].c[1] = rChi[i]; break;
            }
            //        i--;
        }

        prinmat(tins);
        sortinnodarr(ins);

        printf("\n>>> See innode array before sorting:\n"); 
        k=n+1;
        for(i=levnum+1; i>=1; --i) {
            // for(j=culev[i]-1; j>=culev[i-1]; j--) {
            for(j=culev[i-1]; j<culev[i]; j++) {
                switch (tins[j].sc) {
                    case 0: tins[j].c[0] = k++; tins[j].c[1] = k++; break;
                    case 1: tins[j].c[1] = k++; break;
                }
                printf("Idx:%i L:%i I:%i SC:%i C01:%i,%i|", j, tins[j].l, tins[j].i, tins[j].sc, tins[j].c[0], tins[j].c[1]);
            }
        printf("\n"); 
        }
    }
}

void Gen( int p, int s, int cL )
{ 
    int i, np, temp;
    char fn[16];
    innode *ins;

    if (p > n) { /* we have finished a certain tree */
        ins=calloc(n, sizeof(innode));
        setlevarrs();
        tostruct(&ins);
        sprintf(fn, "%03i.png", num);
        dealwithlev(fn, &ins); /* amazingly works it all out from the lev array!, now labels of course */
        memset(levact,0,(levnum+1)*sizeof(int));
        memset(culev,0,(levnum+2)*sizeof(int));
        memset(cucul1,0,(levnum+3)*sizeof(int));
        free(ins);
    } else {
        if (cL==0 && p <= levnum+2 )
            par[p] = lev[p] = p-1; 
        else  
            if (par[p-cL] < s) {
                par[p] = par[s];
                lev[p] = lev[s]; 
            } else { 
                par[p] = cL + par[p-cL];
                lev[p] = 1+lev[par[p]];
            } 

        ++chi[par[p]]; 
        temp = rChi[par[p]];
        if (chi[par[p]] <= mc) {
            rChi[par[p]] = p;
            nextp[p] = chi[par[p]] < mc ? par[p] : nextp[par[p]];
            Gen( p+1, s, cL );               /* <==== recursive call */    
            rChi[par[p]] = temp;
        } 
        --chi[par[p]];

        nextp[p] = nextp[par[p]];
        np = nextp[p];
        while (np >= 1) {
            par[p] = np;  
            lev[p] = 1 + lev[np];
            ++chi[np]; 
            temp = rChi[np];  
            rChi[np] = p;
            if (chi[np] >= mc)
                nextp[p] = nextp[np];
            Gen( p+1, temp, p-temp );         /* <==== recursive call */
            --chi[np]; 
            rChi[par[p]] = temp;
            /* move up one */
            np = nextp[np];
            nextp[p] = np;
        }
    }
} 

void printhelp()
{
    printf( "Two args required:\n" );
    printf( "1st: n is the number of nodes in the tree.\n" );
    printf( "2rd: levnum is the number of levels tree should have\n");
    printf( "MaxChild is the maximum number of children of a node, hardset at 2.\n" );
    printf( "Frank Ruskey, 1995, 2000. Mods Ramon Fallon 2011.\n" );
}

int main( int argc, char *argv[] )
{
    int i;

    if(argc!=3) {
        printhelp();
        exit(EXIT_FAILURE);/* first set all the parameters */
    }
    n=atoi(argv[1]);
    levnum=atoi(argv[2]);
    levact=calloc(levnum+1,sizeof(int));
    culev=calloc(levnum+2,sizeof(int));
    cucul1=calloc(levnum+3,sizeof(int));

    mc=2; /* always binary trees: used to be max children */

    num = 0;
    /* mc = n; */ 
    for( i=1; i<=n; i++)
        chi[i]=0;
    if (levnum > n || n > MaxSize-1)
        printf("Error: Either levnum is too high, or number of nodes are too many.\n");
    else
        /* now start the program  */
        for (i=1; i<=levnum+1; i++) {
            par[i] = lev[i] = nextp[i] = i-1;
            rChi[i] = i+1;
            chi[par[i]] = 1;
        }
    rChi[levnum+1] = 0;

    /* void Gen( int p, int s, int cL ) */
    Gen(levnum+2, levnum+1, 1);

    printf("Total trees = %3i\n", num); 
    free(levact);
    free(culev);
    free(cucul1);

    return( 0 );
}
