#include <dos.h>
#include <math.h> // only cos/sin/tan
#include <stdio.h>
#include <alloc.h>
#include <stdlib.h>
#include <string.h>
#define MAXKEYS 256
#define video_address 0xa000
#define PI 3.1415926535897932384626433832795
#define PI2 6.28318530717958647692528676655901
#define rad(x) (x *0.0174532925199432951)
struct pointtypei
{
 int x, y;
};
//VALUES SECTION!
int nextisext = 0;
unsigned char gcol = 15;
enum boolean{true = 1, false = 0};
char keypress[MAXKEYS];
unsigned int qpixels[200];
void interrupt key_interrupt(...);
void interrupt (*key_old_interrupt)(...);
unsigned int Base = 0x220, IRQ = 0;
unsigned char DMA = 0;
unsigned int sgbuffer, svidbuf;
unsigned char *gbuffer = NULL;
unsigned char *video_buffer = (unsigned char far *)0xA0000000L;
unsigned char far *rom_char_set = (unsigned char far *)0xF000FA6EL;
// COS|SIN TABLE!
const int TBL_BITS = 9;
const int TBL_SIZE = 1 << TBL_BITS;
const int TBL_LEFT = TBL_SIZE -1;
#define COS(x) (costbl[(int)x & TBL_LEFT])
#define SIN(x) (sintbl[(int)x & TBL_LEFT])
#define nrad(x) (x *M_PI /(TBL_SIZE /2))
#define qrad(x) (x /M_PI *(TBL_SIZE /2))
double costbl[TBL_SIZE];
double sintbl[TBL_SIZE];
// WAVE FORMAT!
typedef struct WaveData
{
 unsigned long length;
 unsigned char *data;
 unsigned long finishing;
};
void init320x200()
{
 svidbuf = FP_SEG(video_buffer);
 sgbuffer = FP_SEG(video_buffer);
 gbuffer = (unsigned char *)MK_FP(sgbuffer, 0);
 asm{
	mov ax, 0x13
	int 0x10
 }
}
void closegraph()
{
 asm{
	mov ax, 0x3
	int 0x10
 }
}
void qpixelstable()
{
 for (int i = 0; i < 200; i++)
	qpixels[i] = (i << 8) +(i << 6);
}
void setpal(char col, char r, char g, char b)
{
 asm{
	mov dx, 0x3C8
	mov al, col
	out dx, al
	inc dx
	mov al, r
	out dx, al
	mov al, g
	out dx, al
	mov al, b
	out dx, al
 }
}
void getpal(char col, char *red, char *green, char *blue)
{
 char r2, g2, b2;
 asm{
	mov dx, 0x3C7
	mov al, col
	out dx, al
	add dx, 2
	in al, dx
	mov r2, al
	in al, dx
	mov g2, al
	in al, dx
	mov b2, al
 }
 *red = r2;
 *green = g2;
 *blue = b2;
}
void waitretrace()
{
 asm mov dx, 0x3DA
l1:
 asm{
	in al, dx
	and al, 0x08
	jnz l1
 }
l2:
 asm{
	in al, dx
	and al, 0x08
	jz l2
 }
}
void fadeout()
{
 unsigned char pal[3];
 for (int c = 0; c < 64; c++)
 {
	waitretrace();
	for (int i = 0; i < 256; i++)
	{
	 getpal(i, &pal[0], &pal[1], &pal[2]);
	 if (pal[0] > 0) pal[0]--;
	 if (pal[1] > 0) pal[1]--;
	 if (pal[2] > 0) pal[2]--;
	 setpal(i, pal[0], pal[1], pal[2]);
	}
 }
}
void fadein(char *savedpal)
{
 unsigned char pal[3];
 for (int c = 0; c < 64; c++)
 {
	waitretrace();
	for (int i = 0; i < 256; i++)
	{
	 getpal(i, &pal[0], &pal[1], &pal[2]);
	 if ((pal[0] < 64) && (pal[0] < savedpal[(i *3)])) pal[0]++;
	 if ((pal[1] < 64) && (pal[1] < savedpal[(i *3) +1])) pal[1]++;
	 if ((pal[2] < 64) && (pal[2] < savedpal[(i *3) +2])) pal[2]++;
	 setpal(i, pal[0], pal[1], pal[2]);
	}
 }
}
void blackpal()
{
 for (int i = 0; i < 256; i++)
	setpal(i, 0, 0, 0);
}
void plotpixel(unsigned int x, unsigned int y, unsigned char color)
{
 asm{
	cmp x, 319
	ja end
	cmp y, 199
	ja end
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
void setcolor(unsigned char color)
{
 gcol = color;
}
void cleardevice()
{
 asm {
	push es
	push di
	xor ax, ax
	les di, gbuffer
	mov cx, 16000
	db 0x66
	rep stosw
	pop di
	pop es
 }
}
void swapint(int *num1, int *num2)
{
 int num3 = *num1;
 *num1 = *num2;
 *num2 = num3;
}
void swapdouble(double *num1, double *num2)
{
 double num3 = *num1;
 *num1 = *num2;
 *num2 = num3;
}
void verline(int x, int y, int y2)
{
 if (y > y2) swapint(&y, &y2);
 unsigned int h = (y2 -y) +1;
 asm{
	mov ax, [sgbuffer]
	mov es, ax
	mov ax, y
	mov di, y
	shl ax, 8
	shl di, 6
	add di, ax
	add di, x
	mov ah, gcol
	mov cx, h
 }
loopy:
 asm{
	mov [es:di], ah
	add di, 320
	loop loopy
 }
}
void horline(int y, int x, int x2)
{
 if (x > x2) swapint(&x, &x2);
 unsigned int w = (x2 -x) +1;
 asm{
	mov ax, [sgbuffer]
	mov es, ax
	mov ax, y
	mov di, y
	shl ax, 8
	shl di, 6
	add di, ax
	add di, x
	mov al, gcol
	mov cx, w
	rep stosb
 }
}
void bar(int x, int y, int x2, int y2)
{
 if (x > x2) swapint(&x, &x2);
 if (y > y2) swapint(&y, &y2);
 unsigned int w = (x2 -x) +1;
 unsigned int shortw = 320 -w;
 unsigned int h = (y2 -y) +1;
 asm{
	mov ax, [sgbuffer]
	mov es, ax
	mov ax, y
	mov di, y
	shl ax, 8
	shl di, 6
	add di, ax
	add di, x
	mov dx, h
	mov al, gcol
 }
loopy:
 asm{
	mov cx, w
	rep stosb
	add di, shortw
	dec dx
	jnz loopy
 }
done:
}
void drawsprite(int x, int y, int w, int h, unsigned char *sprt)
{
 for (int iy = 0; iy < h; iy++)
	for (int ix = 0; ix < w; ix++)
	 if (sprt[iy *w +ix]) plotpixel(x +ix, y +iy, sprt[iy *w +ix]);
}
void drawsprites(int x, int y, int w, int h, unsigned char *sprt)
{
 for (int iy = 0; iy < h; iy++)
	for (int ix = 0; ix < w; ix++)
	 if (sprt[iy *w +ix]) plotpixel(x +ix, y +iy, gcol);
}
void circle(int x, int y, int radius)
{
 for (int index = 0; index < 511; index++)
	plotpixel(x +(radius *COS(index)), y +(radius *SIN(index)), gcol);
}
void drawscreen(unsigned char *buf)
{
 unsigned int sbuf = FP_SEG(buf);
 asm{
	push ds
	mov ax, [svidbuf]
	mov es, ax
	xor di, di
	mov ax, [sbuf]
	mov ds, ax
	xor si, si
	mov cx, 16000
	db 0x66
	rep movsw
	pop ds
 }
}
void copyscreen(unsigned char *dest, unsigned char *src)
{
 unsigned int sdest = FP_SEG(dest);
 unsigned int ssrc = FP_SEG(src);
 asm{
	push ds
	push es
	push di
	push si
	mov ax, [sdest]
	mov es, ax
	xor di, di
	mov ax, [ssrc]
	mov ds, ax
	xor si, si
	mov cx, 16000
	db 0x66
	rep movsw
	pop si
	pop di
	pop es
	pop ds
 }
}
void screenis(unsigned char *buf)
{
 sgbuffer = FP_SEG(buf);
 gbuffer = (unsigned char *)MK_FP(sgbuffer, 0);
}
void closevirscr(unsigned char *buffer)
{
 free(buffer);
 screenis(video_buffer);
}
void maketbls()
{
 for(int i = 0; i < TBL_SIZE; i++)
 {
	costbl[i] = cos(nrad(i));
	sintbl[i] = sin(nrad(i));
 }
}
int loadpal(char *fname)
{
 FILE *fil;
 unsigned char pal[768];
 if ((fil = fopen(fname, "rb")) == NULL) return(0);
 fread(pal, 768, 1, fil);
 fclose(fil);
 for(int index = 0; index < 256; index++)
	setpal(index, pal[(index *3)], pal[(index *3) +1], pal[(index *3) +2]);
 free(pal);
 return(1);
}
void getskeys()
{
 memset(keypress, 0, MAXKEYS);
 key_old_interrupt = getvect(9);
 setvect(9, key_interrupt);
}
void interrupt key_interrupt(...)
{
 unsigned char ch, ext = 0;
 ch = inp(0x60);
 if (nextisext)
 {
	ext = 128;
	nextisext = 0;
 }
 if (ch == 224) nextisext = 1;
 keypress[(ch &127) +ext] = (ch < 128);
 outportb(0x20, 0x20);
}
int keydown(int nkey)
{
 if (keypress[nkey]) return(1);
 return(0);
}
int skeypressed()
{
 for (int i = 0; i < MAXKEYS; i++)
	if (keypress[i]) return(i);
 return(0);
}
void clearskeys()
{
 memset(keypress, 0, MAXKEYS);
}
void closeskeys()
{
 setvect(9, key_old_interrupt);
}
void WriteDSP(unsigned char value)
{
 while ((inportb(Base +0xC) & 0x80) == 0x80) ;
 outportb(Base +0xC, value);
}
int ResetDSP(unsigned int test)
{
 outportb(test +0x6, 1);
 delay(10);
 outportb(test +0x6, 0);
 delay(10);
 if (((inportb(test +0xE) & 0x80) == 0x80) && (inportb(test +0xA) == 0xAA))
 {
	Base = test;
	return(1);
 }
 else return(0);
}
unsigned char ReadDSP()
{
 while (!(inportb(Base +0xE) & 0x80)) ;
 return(inportb(Base +0xA));
}
int initsb()
{
 for (int i = 1; i < 9; i++)
 {
	if (i != 7)
	 if (ResetDSP(0x200 +(i << 4))) return(1);
 }
 return(0);
}
void closesb()
{
 WriteDSP(0xD0);
 WriteDSP(0xDA);
}
void plotchar(int x, int y, char c)
{
 char *work_char;
 unsigned char bit_mask = 0x80;
 work_char = rom_char_set +(c << 3);
 for (int y2 = 0; y2 < 8; y2++)
 {
	bit_mask = 0x80;
	for (int x2 = 0; x2 < 8; x2++)
	{
	 if ((*work_char & bit_mask))
		plotpixel(x +x2, y +y2, gcol);
	 bit_mask = (bit_mask >> 1);
	}
	work_char++;
 }
}
void writestrxy(int x, int y, char *string)
{
 for (int index = 0; string[index] != 0; index++)
	plotchar(x +(index << 3), y, string[index] &127);
}
void writestrxy(int x, int y, int number)
{
 char *string = "";
 itoa(number, string, 10);
 for (int index = 0; index < strlen(string); index++)
	plotchar(x +(index << 3), y, string[index]);
}
int getvirscr(unsigned char **buf)
{
 if ((*buf = (unsigned char *)malloc(64000)) == NULL) return(0);
 sgbuffer = FP_SEG(*buf);
 gbuffer = (unsigned char *)MK_FP(sgbuffer, 0);
 cleardevice();
 return(1);
}
int load32(char *fname)
{
 FILE *file3x2;
 if ((file3x2 = fopen(fname, "rb")) == NULL) return(0);
 fread((unsigned char *)gbuffer, 64000, 1, file3x2);
 fclose(file3x2);
 return(1);
}