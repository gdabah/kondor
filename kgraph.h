void kplotpixel(unsigned int x, unsigned int y, unsigned char color)
{
 asm{
	cmp x, SCREEN_W
	jae end
	cmp y, SCREEN_H
	jae end
	mov ax, [sgbuffer]
	mov es, ax
	mov bx, y
	shl bx, 1
	mov bx, word ptr qpixels[bx]
	add bx, x
	mov ah, color
	mov [es:bx], ah
 }
end:
}
void krotsprite(int x, int y, int cx, int cy, int ang, int w, int h, unsigned char *sprt)
{
 float x_step = COS(ang),
			 y_step = SIN(ang),
			 x_step2 = COS(ang +128),
			 y_step2 = SIN(ang +128),
			 start_x = x -(cx *x_step +cy *x_step2),
			 start_y = y -(cx *y_step +cy *y_step2),
			 temp_x,
			 temp_y;
 x_step /= 2;
 y_step /= 2;
 int offset = 0;
 for (int iy = 0; iy < h; iy++)
 {
	temp_x = start_x;
	temp_y = start_y;
	for(int ix = 0; ix < w; ix++)
	{
	 for (int i = 0; i < 2; i++)
	 {
		if (sprt[offset])
		 kplotpixel(temp_x, temp_y, sprt[offset]);
		temp_x += x_step;
		temp_y += y_step;
	 }
	 offset++;
	}
	start_x += x_step2;
	start_y += y_step2;
 }
}
void kdrawsprite(int x, int y, int w, int h, unsigned char *sprt)
{
 for (int iy = 0; iy < h; iy++)
	for (int ix = 0; ix < w; ix++)
	 if (sprt[iy *w +ix]) kplotpixel(x +ix, y +iy, sprt[iy *w +ix]);
}
void drawsink(int x, int y, int cx, int cy, int ang, int w, int h, unsigned char *sprt, int sink_w1, int sink_w2, int sink_h1, int sink_h2)
{
 unsigned char c;
 float x_step = COS(ang),
			 y_step = SIN(ang),
			 x_step2 = COS(ang +128),
			 y_step2 = SIN(ang +128),
			 start_x = x -(cx *x_step +cy *x_step2),
			 start_y = y -(cx *y_step +cy *y_step2),
			 temp_x,
			 temp_y;
 unsigned int asmx, asmy;
 x_step /= 2;
 y_step /= 2;
 int offset = 0;
 for (int iy = 0; iy < h; iy++)
 {
	temp_x = start_x;
	temp_y = start_y;
	for(int ix = 0; ix < w; ix++)
	{
	 offset = iy *w +ix;
	 for (int i = 0; i < 2; i++)
	 {
		if (sprt[offset])
		{
		 // Substract 4 from offset for segment stuff.
		 if ((ix < sink_w1) || (ix > w -sink_w2) ||
				 (iy < sink_h1) || (iy > h -sink_h2))
					c = buffer[qpixels[(int)temp_y] +(int)temp_x -4] | 128;
		 else c = sprt[offset];
		 kplotpixel(temp_x, temp_y, c);
		}
		temp_x += x_step;
		temp_y += y_step;
	 }
	}
	start_x += x_step2;
	start_y += y_step2;
 }
}
void khorline(int y, int x, int x2)
{
 if (x > x2) swapint(&x, &x2);
 if (x2 < 0) return;
 if (x > SCREEN_W) return;
 if (y >= SCREEN_H) return;
 if (x2 >= SCREEN_W) x2 = SCREEN_W -1;
 if (y < 0) return;
 unsigned int w = (x2 -x) +1;
 if (x <= 0)
 {
	w = x2 +1;
	x = 0;
 }
 asm{
	mov ax, [sgbuffer]
	mov es, ax
	mov di, y
	shl di, 1
	mov di, word ptr qpixels[di]
	add di, x
	mov al, gcol
	mov cx, w
	rep stosb
 }
}
void kverline(int x, int y, int y2)
{
 if (y > y2) swapint(&y, &y2);
 if (y2 < 0) return;
 if (y >= SCREEN_H) return;
 if (x >= SCREEN_W) return;
 if (y2 >= SCREEN_H) y2 = SCREEN_H -1;
 if (x < 0) return;
 unsigned int h = (y2 -y) +1;
 if (y <= 0)
 {
	h = y2 +1;
	y = 0;
 }
 asm{
	mov ax, [sgbuffer]
	mov es, ax
	mov bx, y
	shl bx, 1
	mov bx, word ptr qpixels[bx]
	add bx, x
	mov al, gcol
	mov cx, h
 }
loopy:
 asm{
	mov [es:bx], al
	add bx, 320
	loop loopy
 }
}