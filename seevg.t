[?1049h[?1h=[1;38r[?12;25h[?12l[?25h[27m[m[H[2J[?25l[38;1H"simitwo2.c" 99L, 2591C[1;1H[33m  1 [m[35m#include [m[33m<stdio.h>
  2 [m[35m#include [m[33m<stdlib.h>
  3 [m[35m#include [m[33m<string.h>
  4 
  5 [m[35m#define IPSZ [m[33m10[m[35m [m[36m/* initial size of pop */[m
[33m  6 [m[35m#define GBUF [m[33m2
  7 
  8 [m[32mtypedef[m [32mstruct[m
[33m  9 [m{
[33m 10 [m    [32mint[m il;
[33m 11 [m    [32mint[m *ca;
[33m 12 [m    [32mint[m casz;
[33m 13 [m} acixs;
[33m 14 
 15 [m[32mvoid[m printpaip(acixs *pai, [32mint[m start, [32mint[m end) [36m/* print a part of the pai container*/[m
[33m 16 [m{
[33m 17 [m    [32mint[m i, j;
[33m 18 [m    [33mfor[m(i=start;i<end;++i) {
[33m 19 [m[7C printf([33m"[m[35m%d[m[33m) parent [m[35m%d[m[33m: "[m, i, pai[i].il);
[33m 20 [m[7C [33mfor[m(j=[33m0[m; j<pai[i].casz; j++)
[33m 21 [m[11C printf([33m"[m[35m%d[m[33m "[m, pai[i].ca[j]);
[33m 22 [m[7C printf([33m"[m[35m\n[m[33m"[m);
[33m 23 [m    }
[33m 24 [m    printf([33m"----------------------------[m[35m\n[m[33m"[m);
[33m 25 [m}
[33m 26 
 27 [m[32mint[m main([32mint[m argc, [32mchar[m *argv[])
[33m 28 [m{
[33m 29 [m    [32mint[m i, j, *ra, *pa;
[33m 30 [m    acixs *pai;
[33m 31 [m    [32mint[m pgbuf=GBUF;
[33m 32 [m    [32mint[m *pca=malloc(pgbuf*[33msizeof[m([32mint[m));
[33m 33 [m    [32mint[m *apszs=calloc(pgbuf, [33msizeof[m([32mint[m)); [36m/* array of pai sizes */[m
[33m 34 [m    [32mint[m pcpc=[33m0[m; [36m/* parent child pair counter */[m
[33m 35 [m    pca[pcpc]=IPSZ;
[33m 36 
 37 [m    [32mint[m paibuf=GBUF;[38;132H1,1[10CTopp[1;5H[?12l[?25h[?25l[38;1H[K[38;1H:[?12l[?25hQ[?25l[?12l[?25h![?25l[?12l[?25h[?25l[1m[37m[41mE492: Inte ett redigerarkommando: Q![m[95C1,1[10CTopp[1;5H[?12l[?25h[?25l[38;1H[K[38;1H:[?12l[?25hQ[?25l[?12l[?25h[?25l[38;2H[K[38;2H[?12l[?25hq[?25l[?12l[?25h[?25l[38;1H[K[38;1H[?1l>[?12l[?25h[?1049l