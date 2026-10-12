boolean scrollmove = true;
unsigned char *map = NULL;
unsigned char *minmap = NULL;
unsigned char *tiles = NULL;
unsigned int kpixels[MAP_H];
char IMAGES_FNAME[14] = "";
int loadsprites()
{
 if ((tiles = (unsigned char *)malloc(TILE_W *TILE_H *SPRITES_NO)) == NULL)	memerr("лоадспритес");
 memset(tiles, 0, MAP_W *MAP_H *SPRITES_NO);
 FILE *fload;
 if ((fload = fopen(TILES_FILE, "rb")) == NULL) filerr();
 fread(tiles, SPRITES_NO, TILE_W *TILE_H, fload);
 fclose(fload);
 return(1);
}
void setimagesfile(char *str)
{
 strcpy(IMAGES_FNAME, str);
}
int loadimg(int n, unsigned char **img)
{
 FILE *fil;
 int w, h;
 if ((fil = fopen(IMAGES_FNAME, "rb")) == NULL) filerr();
 for (int i = 0; i <= n; i++)
 {
	fread(&w, 1, sizeof(int), fil);
	fread(&h, 1, sizeof(int), fil);
	if (i == n)
	{
	 free(*img);
	 if ((*img = (unsigned char *)malloc(w *h)) == NULL) memerr("имагес");
	 fread(*img, 1, w *h, fil);
	 fclose(fil);
	 return(1);
	}
	for (int fs = 0; fs < w *h; fs++) fgetc(fil);
 }
 return(-1);
}
void loadimages()
{
 //Items Images...
 setimagesfile(IMAGES_FILE);
 if (!loadimg(0, &bullet_img)) filerr();
 bullets_sprts[0].set(0, 0, BULLETW >> 1, BULLETH >> 1, 0, BULLETW, BULLETH, bullet_img, true);
 loadimg(1, &tank_img);
 loadimg(2, &cannon_img);
 loadimg(3, &expl1);
 loadimg(4, &expl2);
 loadimg(5, &expl3);
 loadimg(6, &expl4);
 loadimg(7, &texpl1);
 loadimg(8, &texpl2);
 loadimg(9, &texpl3);
 loadimg(10, &texpl4);
 loadimg(11, &texpl5);
 loadimg(12, &skey_img);
 loadimg(13, &cross_img);
 loadimg(14, &rocket_img);
 bullets_sprts[1].set(0, 0, 8, 5, 0, 15, 9, rocket_img, true);
 loadimg(15, &shield_img);
 loadimg(16, &fly_img);
 loadimg(17, &turpad_img);
 loadimg(18, &mig_img);
 loadimg(19, &fshoe_img);
 loadimg(20, &turcan_img);
 //Menu Sprites...
 setimagesfile(MENU_IMGS_FILE);
 if (!loadimg(0, &start_s)) filerr();
 loadimg(1, &startc_s);
 loadimg(2, &resume_s);
 loadimg(3, &resumec_s);
 loadimg(4, &options_s);
 loadimg(5, &optionsc_s);
 loadimg(6, &help_s);
 loadimg(7, &helpc_s);
 loadimg(8, &exit_s);
 loadimg(9, &exitc_s);
 loadimg(10, &gameover_s);
 loadimg(11, &missacco_s);
 loadimg(12, &scores_s);
 loadimg(13, &scoresc_s);
}
void closeimages()
{
 free(bullet_img);
 free(tank_img);
 free(cannon_img);
 free(expl1);
 free(expl2);
 free(expl3);
 free(expl4);
 free(texpl1);
 free(texpl2);
 free(texpl3);
 free(texpl4);
 free(texpl5);
 free(skey_img);
 free(cross_img);
 free(rocket_img);
 free(shield_img);
 free(fly_img);
 free(turpad_img);
 free(mig_img);
 free(fshoe_img);
 free(turcan_img);
 free(start_s);
 free(startc_s);
 free(resume_s);
 free(resumec_s);
 free(options_s);
 free(optionsc_s);
 free(help_s);
 free(helpc_s);
 free(exit_s);
 free(exitc_s);
 free(gameover_s);
 free(missacco_s);
 free(scores_s);
 free(scoresc_s);
}
//a byte per a loop.
void qmemcpy(unsigned char *dest, unsigned char *src, int size)
{
 asm{
	push ds
	push es
	push di
	push si
	les di, dest
	lds si, src
	mov cx, size
	rep movsw
	pop si
	pop di
	pop es
	pop ds
 }
}
//4 bytes per a loop.
void kmemcpy(unsigned char *dest, unsigned char *src, int size)
{
 asm{
	push ds
	push es
	push di
	push si
	les di, dest
	lds si, src
	mov cx, size
	db 0x66
	rep movsw
	pop si
	pop di
	pop es
	pop ds
 }
}
void ldrawcell(int y, int n, int left)
{
 int draw_x = TILE_W -left;
 for(int iy = 0, ty = WINDOW_Y +y; iy < TILE_H; iy++, ty++)
	_fmemcpy(&gbuffer[qpixels[ty]],
				 &tiles[(n << 8) +(iy << 4) +left], draw_x);
}
void rdrawcell(int y, int n, int left)
{
 int start_x = SCREEN_W -left;
 for(int iy = 0, ty = WINDOW_Y +y; iy < TILE_H; iy++, ty++)
	_fmemcpy(&gbuffer[qpixels[ty] +start_x],
				 &tiles[(n << 8) +(iy << 4)], left);
}
void udrawcell(int x, int n, int left)
{
 for(int iy = left, ty = WINDOW_Y; iy < TILE_H; iy++, ty++)
	_fmemcpy(&gbuffer[qpixels[ty] +x],
				 &tiles[(n << 8) +(iy << 4)], TILE_W);
}
void ddrawcell(int x, int n, int left)
{
 for(int iy = 0, ty = SCREEN_H -left; iy < left; iy++, ty++)
	_fmemcpy(&gbuffer[qpixels[ty] +x],
				 &tiles[(n << 8) +(iy << 4)], TILE_W);
}
void fdrawcell(int x, int y, int n)
{
 for(int iy = 0, ty = WINDOW_Y +y; iy < TILE_H; iy++, ty++)
	kmemcpy(&gbuffer[qpixels[ty] +x],
					&tiles[(n << 8) +(iy << 4)], 4); //16/4 -bytes per loop
}
void drawcell(int x, int y, int n)
{
 int sx = 0, sy = 0,
		 ex = 0, ey = 0;
 if (x < WINDOW_X) sx = WINDOW_X -x;
 else if (x +TILE_W > SCREEN_W) ex = (x +TILE_W) -SCREEN_W;
 if (y < WINDOW_Y) sy = WINDOW_Y -y;
 else if (y +TILE_H > SCREEN_H) ey = (y +TILE_H) -SCREEN_H;
 x += WINDOW_X +sx;
 for(int iy = sy, ty = WINDOW_Y +y +sy; iy < (TILE_H -ey); iy++, ty++)
	_fmemcpy(&gbuffer[qpixels[ty] +x],
				 &tiles[(n << 8) +(iy *TILE_W) +sx], TILE_W -ex -sx);
}
void drawmap()
{
 int x, y, left_x, left_y;
 int ix, iy, tx, ty;
 asm {
	mov ax, scroll_x
	mov left_x, ax
	mov x, ax
	shr x, 4
	mov ax, scroll_y
	mov left_y, ax
	mov y, ax
	shr y, 4
	and left_x, 0xf
	and left_y, 0xf
 }
 for(ix = x +1, tx = -left_x +TILE_W; ix < (x +WINDOW_W); ix++, tx += TILE_W)
	for(iy = y +1, ty = -left_y +TILE_H; iy < (y +WINDOW_H); iy++, ty += TILE_H)
	 fdrawcell(tx, ty, map[kpixels[iy] +ix]);
 for(ix = x +1, tx = -left_x +TILE_W; ix < (x +WINDOW_W); ix++, tx += TILE_W)
 {
	udrawcell(tx, map[kpixels[y] +ix], left_y);
	ddrawcell(tx, map[kpixels[y +WINDOW_H] +ix], left_y);
 }
 for(iy = y +1, ty = -left_y +TILE_H; iy < (y +WINDOW_H); iy++, ty += TILE_H)
 {
	ldrawcell(ty, map[kpixels[iy] +x], left_x);
	rdrawcell(ty, map[kpixels[iy] +x +WINDOW_W], left_x);
 }
 drawcell(-left_x, -left_y,
					map[kpixels[y] +x]);
 drawcell(-left_x +SCREEN_W, -left_y,
					map[kpixels[y] +x +WINDOW_W]);
 drawcell(-left_x, -left_y +SCREEN_H,
					map[(y +WINDOW_H) *MAP_W +x]);
 drawcell(-left_x +SCREEN_W, -left_y +SCREEN_H,
					map[(y +WINDOW_H) *MAP_W +x +WINDOW_W]);
}
void set_map(int x, int y, int val)
{
 map[kpixels[y] +x] = val;
}
void checkwater(int offset)
{
 unsigned char c = map[offset];
 if (c < 2) if (map[offset]++ >= 1) map[offset] = 0;
 if ((c >= 21) && (c <= 28)) map[offset] += 8;
 if ((c >= 29) && (c <= 36)) map[offset] -= 8;
 if ((c >= 37) && (c <= 44)) map[offset] += 8;
 if ((c >= 45) && (c <= 52)) map[offset] -= 8;
 if ((c >= 53) && (c <= 60)) map[offset] += 8;
 if ((c >= 61) && (c <= 68)) map[offset] -= 8;
 if ((c >= 85) && (c <= 92)) map[offset] += 8;
 if ((c >= 93) && (c <= 100)) map[offset] -= 8;
}
void movewater()
{
 int x, y;
 asm {
	mov ax, scroll_x
	mov x, ax
	shr x, 4
	mov ax, scroll_y
	mov y, ax
	shr y, 4
 }
 for(int i = x; i < x +WINDOW_W; i++)
	for(int j = y; j < y +WINDOW_H; j++)
	 checkwater(kpixels[j] +i);
 if (x < MAP_W -WINDOW_W)
	for(j = y; j < y +WINDOW_H; j++)
	 checkwater(kpixels[j] +x +WINDOW_W);
 if (y < MAP_H -WINDOW_H)
	for(int i = x; i < x +WINDOW_W; i++)
	 checkwater(kpixels[y +WINDOW_H] +i);
}
int water(unsigned char value)
{
 if (value <= 1 || ((value >= 21) && (value <= 52))) return (1);
 return (0);
}
int waterxy(int x, int y)
{
 return(water(map[kpixels[y] +x]));
}
int blocking(unsigned char value)
{
 if (((value > 100) && (value < 115)) || (value == 255)) return(1);
 return 0;
}
int blockingxy(int x, int y)
{
 return(blocking(map[kpixels[y] +x]));
}
int minblocking(unsigned char value)
{
 return (value == 100 || value == 0 || value == 72);
}
int minblockingxy(int x, int y)
{
 return(minblocking(minmap[kpixels[y] +x]));
}
unsigned char getmapcol(unsigned char tile)
{
 if (tile == 0 || tile == 1)
 {
	switch (random(5))
	{
	 case 0: return(4);
	 case 1: return(5);
	 case 2: return(7);
	 case 3: return(10);
	 case 4: return(11);
	}
 }
 switch(tile)
 {
	case 7: return(29);
	case 8: return(30);
	case 9: return(31);
	case 10: return(32);
	case 11: return(33);
	case 12: return(30);
	case 13: return(32);
	case 14: return(44);
	case 15: return(50);
	case 16: return(52);
	case 17: return(47);
	case 18: return(58);
	case 19: return(59);
	case 20: return(55);
	case 253: return(33);
	case 254: return(11);
	case 255: return(72);
 }
 if (((tile >= 21) && (tile <= 36)) ||
		 ((tile >= 53) && (tile <= 68)) ||
		 ((tile >= 69) && (tile <= 76))) return (160);
 if (((tile >= 37) && (tile <= 52)) ||
		 ((tile >= 85) && (tile <= 100)) ||
		 ((tile >= 77) && (tile <= 84))) return(183);
 if (tile >= 101) return(100);
 return(0);
}
void setminmap()
{
 for (int i = 0; i < MAP_W *MAP_H; i++)
	minmap[i] = getmapcol(map[i]);
}
void clearminmap(int x2, int y2)
{
 int x, y, offset;
 x = x2 >> 4;
 y = y2 >> 4;
 offset = kpixels[y] +x;
 minmap[offset -MAP_W] = getmapcol(map[offset -MAP_W]);
 minmap[offset -1] = getmapcol(map[offset -1]);
 minmap[offset] = getmapcol(map[offset]);
 minmap[offset +1] = getmapcol(map[offset +1]);
 minmap[offset +MAP_W] = getmapcol(map[offset +MAP_W]);
}
void drawonminmap(int x2, int y2, int col, int ccol)
{
 int x, y, offset;
 x = x2 >> 4;
 y = y2 >> 4;
 offset = kpixels[y] +x;
 minmap[offset -MAP_W] = col;
 minmap[offset -1] = col;
 minmap[offset] = ccol;
 minmap[offset +1] = col;
 minmap[offset +MAP_W] = col;
}
void initminmap()
{
 if ((minmap = (unsigned char *)malloc(MAP_W *MAP_H)) == NULL) memerr("мини═мап");
}
void kpixelstable()
{
 for (int i = 0; i < MAP_H; i++)
	kpixels[i] = (i << 5) +(i << 6);
}
void closeminmap()
{
 free(minmap);
}
void drawminmap()
{
 int sx = (scroll_x >> 4) -16, sy = (scroll_y >> 4) -16;
 if (sx < 1) sx = 1;
 if (sy < 1) sy = 1;
 if (sx > MAP_W -48 -1) sx = MAP_W -48 -1;
 if (sy > MAP_H -48 -1) sy = MAP_H -48 -1;
 for(int ix = 0; ix < 48; ix ++)
	for(int iy = 0; iy < 48; iy ++)
	 plotpixel(ix +SCREEN_W +7, 8 +iy, minmap[kpixels[sy +iy] +sx +ix]);
}
void drawscroll()
{
 screenis(bkg);
 drawmap();
 scrollmove = false;
 screenis(buffer);
}
void check4scroll()
{
 double x = tank.layers.x, y = tank.layers.y;
 if ((x -scroll_x > SCREEN_W -SCRRANGE) && (scroll_x < ((MAP_W -WINDOW_W) << 4)))
 {
	scroll_x += (x -scroll_x) -(SCREEN_W -SCRRANGE) +1;
	scrollmove = true;
 }
 if ((x -scroll_x < SCRRANGE) && (scroll_x > 0))
 {
	scroll_x += (x -scroll_x) -SCRRANGE;
	scrollmove = true;
 }
 if ((y -scroll_y > SCREEN_H -SCRRANGE) && (scroll_y < ((MAP_H -WINDOW_H) << 4)))
 {
	scroll_y += (y -scroll_y) -(SCREEN_H -SCRRANGE) +1;
	scrollmove = true;
 }

 if ((y -scroll_y < SCRRANGE) && (scroll_y > 0))
 {
	scroll_y += (y -scroll_y) -SCRRANGE;
	scrollmove = true;
 }
 if (scroll_x < 0) scroll_x = 0;
 if (scroll_x > ((MAP_W - WINDOW_W) << 4)) scroll_x = ((MAP_W -WINDOW_W) << 4);
 if (scroll_y < 0) scroll_y = 0;
 if (scroll_y > ((MAP_H -WINDOW_H) << 4)) scroll_y = ((MAP_H -WINDOW_H) << 4);
 if (scrollmove)
	drawscroll();
}