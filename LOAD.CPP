#include <qunit.h>
#include "define.h"
#include "images.h"
int loadimg(int n, int *w, int *h, unsigned char **img)
{
 FILE *fil;
 fil = fopen("kondor3.dat", "rb");
 if (fil == NULL) return(0);
 int t, t2;
 for (int i = 0; i < n; i++)
 {
	fread(&t, 1, sizeof(int), fil);
	fread(&t2, 1, sizeof(int), fil);
	for (int fs = 0; fs < t *t2; fs++) fgetc(fil);
 }
 fread(&t, 1, sizeof(int), fil);
 fread(&t2, 1, sizeof(int), fil);
 *img = (unsigned char *)malloc(t *t2);
 fread(*img, 1, t *t2, fil);
 *w = t;
 *h = t2;
 fclose(fil);
 return(1);
}
void err()
{
 closegraph();
 cout << "i/o error!";
 exit(0);
}
void main(int argc, char *argv[])
{
 clrscr();
 init320x200();
 int w = 0, h = 0;
 unsigned char *img;
 if (!loadimg(atoi(argv[1]), &w, &h, &img)) err();
 loadpal("kondor.pal");
 drawsprite(0, 0, w, h, img);
 free(img);
 getch();
 closegraph();
}