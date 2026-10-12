#define CH_NO 62
#define CH_W  5
#define CH_H  5
#define GC_H 90

unsigned char *font;
unsigned char *regfont;

void convsprt(int w, int h, char *sprt)
{
 char *temp;
 if ((temp = (char *)malloc(w *h)) == NULL) memerr("цонжерт═спритес");
 int col = 0;
 for (int iy = 0; iy < h; iy++)
	for (int ix = 0; ix < w; ix++)
	{
	 if (ix > 0)
	 {
		if (iy > 0) col += sprt[(iy -1) *w +(ix -1)];
		col += sprt[iy *w +(ix -1)];
		if (iy < h -1) col += sprt[(iy +1) *w +(ix -1)];
	 }
	 if (iy > 0) col += sprt[(iy -1) *w +ix];
	 if (iy < h -1) col += sprt[(iy +1) *w +ix];
	 if (ix < w -1)
	 {
		if (iy > 0) col += sprt[(iy -1) *w +(ix +1)];
		col += sprt[iy *w +(ix +1)];
		if (iy < h -1) col += sprt[(iy +1) *w +(ix +1)];
	 }
	 col += sprt[iy *w +ix] * 8;
	 col /= 16;
	 temp[iy *w +ix] = GC_H +col;
	}
 memcpy(sprt, temp, w *h);
 free(temp);
}

void drawchar(int x, int y, char ch, unsigned char *fnt = font)
{
 ch -= '!';
 if ((ch >= 0) && (ch < CH_NO))
	drawsprite(x, y, CH_W, CH_H, &fnt[ch *CH_W *CH_H]);
}

void drawcharreg(int x, int y, char ch, unsigned char *fnt = regfont)
{
 ch -= '!';
 if ((ch >= 0) && (ch < CH_NO))
	drawsprites(x, y, CH_W, CH_H, &fnt[ch *CH_W *CH_H]);
}

void drawstring(int x, int y, char *str, unsigned char *fnt = font)
{
 strupr(str);
 for(int chi = 0; chi < strlen(str); chi++)
	drawchar(x +chi *(CH_W +1), y, str[chi] & 127, fnt);
}

void drawstring(int x, int y, unsigned long n, unsigned char *fnt = font)
{
 char str[10] = "";
 ultoa(n, str, 10);
 for(int chi = 0; chi < strlen(str); chi ++)
	drawchar(x +chi *(CH_W +1), y, str[chi] & 127, fnt);
}

void drawstringreg(int x, int y, char *str, unsigned char *fnt = regfont)
{
 strupr(str);
 for(int chi = 0; chi < strlen(str); chi++)
	drawcharreg(x +chi *(CH_W +1), y, str[chi] & 127, fnt);
}

void drawstringreg(int x, int y, unsigned long n, unsigned char *fnt = regfont)
{
 char str[10] = "";
 ultoa(n, str, 10);
 for(int chi = 0; chi < strlen(str); chi ++)
	drawcharreg(x +chi *(CH_W +1), y, str[chi], fnt);
}

void load_font(char *filename)
{
 FILE *in;
 if ((in = fopen(filename, "r+")) == NULL) filerr();
 fread(font, CH_NO, CH_W *CH_H, in);
 fclose(in);
 memcpy(regfont, font, CH_NO *CH_W *CH_H);
 for (int fi = 0; fi < CH_NO; fi ++)
	convsprt(CH_W, CH_H, &font[fi *CH_W *CH_H]);
}
/*void save_font(char *filename)
{
 FILE *out;
 if ((out = fopen(filename, "w+")) == NULL) filerr();
 fwrite(font, CH_NO, CH_W *CH_H, out);
 fclose(out);
}*/
void set_font_pal()
{
 for(int i = 0; i < 16; i++)
 {
	gamepal[(i +GC_H) *3] = i *4;
	gamepal[(i +GC_H) *3 +1] = i *4;
	gamepal[(i +GC_H) *3 +2] = i *4;
 }
}
void init_font()
{
 if ((font = (unsigned char *)malloc(CH_NO *CH_W *CH_H)) == NULL) memerr("фонт");
 if ((regfont = (unsigned char *)malloc(CH_NO *CH_W *CH_H)) == NULL) memerr("фонт");
 load_font(FONT_FILE);
 set_font_pal();
}

void close_font()
{
 free(font);
 free(regfont);
}