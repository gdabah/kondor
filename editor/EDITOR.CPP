#include <qunit.h>
#define TILES_FILE "kondor.dat"
#define PAL_FILE "kondor.pal"
#define WIN_W 19
#define WIN_H 12
#define TB_W 37 +16
#define TB_H (19 +(16 *3))
int scrllspdx = 1;
int scrllspdy = 1;
#define TILE_W 16
#define TILE_H 16
const int SCR_W = WIN_W *TILE_W;
const int SCR_H = WIN_H *TILE_H;
int MAP_W = 96;
int MAP_H = 96;
int scroll_x = 0, scroll_y = 0;
int wobj = 0, tbsprt = 0; //Scroll sprite num in tb!
int done = 0;
boolean tbl = true, tbr = true;
int tbx = 200, tby = 20;
unsigned char *scr, *scr2, *map;
#include "sprts.h"
void drawtb();
void drawscroll();
void putobjs();
void makepath();
void check4scroll();
void drawall();
struct tank_type
{
 int x, y, ang;
 double accel, turn_speed, cannon_turn_speed, maxspeed;
 unsigned int power;
};
tank_type tank;

int enemiesn = 0, EADD = 0;
#define MAXENEMIES 98
#define MAXSTEPS 30
enum etype {EMPTY, TURRET, CIRCLE, RANDOM, PATH_FIND, ANGLE, FOLLOW, PIPER, MIG};
struct enemy_type
{
 int x, y, ang;
 double speed, turn_speed;
 unsigned int power;
 unsigned char steps;
 pointtypei PATH[MAXSTEPS];
 etype behavior;
};
enemy_type enemies[MAXENEMIES];
#define MAXBASES 5
int basesn = 0, BADD = 0;
struct base_type
{
 int x, y, gap, power;
};
base_type bases[MAXBASES];
#define MAXOBJECTS 39
int objectsn = 0, OADD = 0;
struct object_type
{
 int x, y, type;
};
object_type objects[MAXOBJECTS];
char CAPTION[256] = "";
int LEVEL = 1;
int FLYERS = 0;
#include "map.h"
#include "files.h"
#include "menu.h"
#include "path.h"
void drawall()
{
 enemieshandle();
 if ((enemies[enemiesn].behavior == PATH_FIND) || (enemies[enemiesn].behavior == MIG)) drawpath();
 for (int i = 0; i <= BADD; i++)
	if ((bases[i].x -scroll_x > -(BASEW >> 1)) && (bases[i].y -scroll_y > -(BASEH >> 1)) && (bases[i].x > 0) && (bases[i].y > 0))
	 editordrawsprt(bases[i].x -scroll_x, bases[i].y -scroll_y, BASEW, BASEH, BASE_IMG);
 if ((tank.x -scroll_x > -(TANK_W >> 1)) && (tank.y -scroll_y > -(TANK_H >> 1)) && (tank.x > 0) && (tank.y > 0))
	editordrawrotsprt(tank.x -scroll_x, tank.y -scroll_y, TANK_W >> 1, TANK_H >> 1, tank.ang, TANK_W, TANK_H, tank_img);
 for (i = 0; i <= OADD; i++)
	if ((objects[i].x -scroll_x > -(OBJECTW >> 1)) && (objects[i].y -scroll_y > -(OBJECTH >> 1)) && (objects[i].x > 0) && (objects[i].y > 0))
	 editordrawrotsprt(objects[i].x -scroll_x,
										 objects[i].y -scroll_y,
										 OBJECTW >> 1,
										 OBJECTH >> 1,
										 0,
										 OBJECTW,
										 OBJECTH,
										 OBJECT_IMG);
}
void drawtb()
{
 //THIS will draw the tanks and objects too.
 drawall();
 setcolor(10);
 rectangle(tbx, tby, tbx +TB_W, tby +TB_H);
 setcolor(0);
 bar(tbx +1, tby +1, tbx +TB_W -1, tby +TB_H -1);
 setcolor(80);
 plotchar(tbx +2, tby +33, '<');
 plotchar(tbx +45, tby +33, '>');
 fdrawsprite(tbx +11, tby +2, TILE_W, TILE_H, &sprts[tbsprt << 8]);
 fdrawsprite(tbx +27, tby +2, TILE_W, TILE_H, &sprts[(tbsprt +1) << 8]);
 fdrawsprite(tbx +11, tby +2 +(TILE_H), TILE_W, TILE_H, &sprts[(tbsprt +2) << 8]);
 fdrawsprite(tbx +27, tby +2 +(TILE_H), TILE_W, TILE_H, &sprts[(tbsprt +3) << 8]);
 fdrawsprite(tbx +11, tby +2 +(TILE_H *2), TILE_W, TILE_H, &sprts[(tbsprt +4) << 8]);
 fdrawsprite(tbx +27, tby +2 +(TILE_H *2), TILE_W, TILE_H, &sprts[(tbsprt +5) << 8]);
 fdrawsprite(tbx +11, tby +2 +(TILE_H *3), TILE_W, TILE_H, &sprts[(tbsprt +6) << 8]);
 fdrawsprite(tbx +27, tby +2 +(TILE_H *3), TILE_W, TILE_H, &sprts[(tbsprt +7) << 8]);
}
void drawcell(int x, int y, int n)
{
 int sx = 0, sy = 0,
		 ex = 0, ey = 0, draw_x, draw_y;
 if (x < 0) sx = 0 -x;
 else if (x +TILE_W > SCR_W) ex = (x +TILE_W) -(SCR_W);
 if (y < 0) sy = 0 -y;
 else if (y +TILE_H > SCR_H) ey = (y +TILE_H) -(SCR_H);
 x += sx;
 draw_x = TILE_W -ex;
 draw_y = TILE_H -ey;
 for(int iy = sy, ty = 1 +y +sy; iy < draw_y; iy++, ty++)
	memcpy(&gbuffer[(ty <<8) +(ty <<6) +x +1],
				 &sprts[(n << 8) +(iy <<4) +sx], draw_x -sx);
}
void drawscroll()
{
 screenis(scr2);
 int x = scroll_x >>4,
		 y = scroll_y >>4,
		 left_x = scroll_x -((scroll_x >> 4) << 4),
		 left_y = scroll_y -((scroll_y >> 4) << 4);
 for(int ix = x, tx = -left_x; ix < (x +WIN_W +1); ix++, tx += TILE_W)
	for(int iy = y, ty = -left_y; iy < (y +WIN_H +1); iy++, ty += TILE_H)
	 drawcell(tx, ty, map[iy *MAP_W +ix]);
 screenis(scr);
}
void checkwobj()
{
 if ((wobj == 0) || (wobj == 1)) wobj = random(2);
 else
 if ((wobj >= 7) && (wobj <= 13)) wobj = random(7) +7;
 else
 if ((wobj >= 14) && (wobj <= 20)) wobj = random(7) +14;
}
void check4scroll()
{
 setcolor(16);
 int mx = getmousex(),
		 my = getmousey();
 if ((mx <= (WIN_W *TILE_W)) && (my <= 10) && (scroll_y > scrllspdy))
 {
	rectangle(0, 0, (WIN_W *TILE_W) +1, 10);
	scroll_y -= scrllspdy;
	tbr = false;
 }
 if ((mx <= (WIN_W *TILE_W) +1) && (my >= (WIN_H *TILE_H) -11) &&
		 (my <= (WIN_H *TILE_H) +1) && (scroll_y <= ((MAP_H -WIN_H) *TILE_H) -scrllspdy))
 {
	rectangle(0, (WIN_H *TILE_H) -11, (WIN_W *TILE_W) +1, (WIN_H *TILE_H) +1);
	scroll_y += scrllspdy;
	tbr = false;
 }
 if ((mx <= 10) && (my <= (WIN_H *TILE_H) +1) && (scroll_x > scrllspdx))
 {
	rectangle(0, 0, 10, (WIN_H *TILE_H) +1);
	scroll_x -= scrllspdx;
	tbr = false;
 }
 if ((mx >= (WIN_W *TILE_W) -11) && (my <= (WIN_H *TILE_H)) &&
		 (mx <= (WIN_W *TILE_W) +1) && (scroll_x < ((MAP_W -WIN_W) *TILE_W) -scrllspdx))
 {
	rectangle((WIN_W *TILE_W) -11, 0, (WIN_W *TILE_W) +1, (WIN_H *TILE_H) +1);
	scroll_x += scrllspdx;
	tbr = false;
 }
}
void checkscrll()
{
 mousewindow(1, 1, maxx, maxy);
 if (rightpressed())
 {
	if ((getmousex() <= (tbx +TB_W)) && (getmousey() <= (tby +TB_H)) &&
			(getmousex() >= tbx) && (getmousey() >= tby) && (tbr))
	{
	 int tx = getmousex() -tbx, ty = getmousey() -tby;
	 mousewindow(tx, ty, maxx -(TB_W -tx), maxy -(TB_H -ty));
	 while(rightpressed())
	 {
		copyscreen(scr, scr2);
		tbx = getmousex() -tx;
		tby = getmousey() -ty;
		drawtb();
		drawmouse();
		drawscreen(scr);
	 }
	 mousewindow(1, 1, maxx, maxy);
	 return;
	}
	mousewindow(1, 1, SCR_W, SCR_H);
	check4scroll();
 }
 else tbr = true;
}
boolean tblp = true;
void putobjs()
{
 int nx, ny;
 if (leftpressed())
 {
	mousewindow(1, 1, maxx, maxy);
	if ((getmousex() < (tbx +TB_W)) && (getmousey() < (tby +TB_H)) &&
			(getmousex() > tbx) && (getmousey() > tby) && (tbl))
	{
	 mousewindow(tbx +1, tby +1, tbx +TB_W -1, tby +TILE_H);
	 if (tblp)
	 {
		if (inrect(getmousex(), getmousey(), tbx +2, tby +33, tbx +8, tby +39))
		 if (tbsprt > 0) tbsprt -= 2;
		if (inrect(getmousex(), getmousey(), tbx +45, tby +33, tbx +51, tby +39))
		 if (tbsprt < SPRITES_NO -8) tbsprt += 2;
		if (inrect(getmousex(), getmousey(), tbx +11, tby +2, tbx +43, tby +2 +(TILE_H << 2)))
		{
		 nx = (getmousex() -tbx -11) >> 4;
		 ny = (getmousey() -tby -2) >> 4;
		}
		wobj = tbsprt +(nx +(ny << 1));
		tblp = false;
	 }
	 mousewindow(1, 1, maxx, maxy);
	}
	else
	if ((getmousex() <= (WIN_W << 4)) && (getmousey() <= (WIN_H << 4)))
	{
	 tbl = false;
	 //255 MEANS TANK POS, 254 MEANS ENEMIES[ENEMIESN] POS, 253 MEANS OBJECTS[OBJECTN] POS, 252 MEANS BASES[BASESN] POS.
	 if ((wobj >= 252) && (wobj <= 255))
	 {
		mousewindow(1, 1, SCR_W, SCR_H);
		while (leftpressed())
		{
		 copyscreen(scr, scr2);
		 switch (wobj)
		 {
			case 255:
			 tank.x = (getmousex() -1) +scroll_x;
			 tank.y = (getmousey() -1) +scroll_y;
			break;
			case 254:
			 enemies[enemiesn].x = (getmousex() -1) +scroll_x;
			 enemies[enemiesn].y = (getmousey() -1) +scroll_y;
			 if ((enemies[enemiesn].behavior == PATH_FIND) || (enemies[enemiesn].behavior == MIG))
			 {
				enemies[enemiesn].PATH[0].x = (getmousex() -1) +scroll_x;
				enemies[enemiesn].PATH[0].y = (getmousey() -1) +scroll_y;
			 }
			break;
			case 253:
			 objects[objectsn].x = (getmousex() -1) +scroll_x;
			 objects[objectsn].y = (getmousey() -1) +scroll_y;
			break;
			case 252:
			 bases[basesn].x = (getmousex() -1) +scroll_x +(BASEW >> 1);
			 bases[basesn].y = (getmousey() -1) +scroll_y;
			break;
		 }
		 check4scroll();
		 drawscroll();
		 drawtb();
		 drawmouse();
		 drawscreen(scr);
		}
		mousewindow(1, 1, maxx, maxy);
		return;
	 }
	 int left_x = scroll_x -((scroll_x >>4) <<4),
			 left_y = scroll_y -((scroll_y >>4) <<4),
			 nx = ((getmousex() -1 +left_x) >> 4), ny = ((getmousey() -1 +left_y) >> 4);
	 checkwobj();
	 map[(ny +(scroll_y >> 4)) *MAP_W +nx +(scroll_x >> 4)] = wobj;
	 mousewindow(1, 1, SCR_W, SCR_H);
	}
 }
 else
 {
	tbl = true;
	tblp = true;
 }
}
void getobjs()
{
 if (rightclicked())
 {
	for (int i = 0; i <= EADD; i++)
	 if (inrotrect(getmousex(), getmousey(), enemies[i].x -scroll_x, enemies[i].y -scroll_y, enemies[i].ang, ENEMY_W, ENEMY_H))
	 {
		wobj = 254;
		enemiesn = i;
		return;
	 }
	for (i = 0; i <= OADD; i++)
	 if (inrotrect(getmousex(), getmousey(), objects[i].x -scroll_x, objects[i].y -scroll_y, 0, OBJECTW, OBJECTH))
	 {
		wobj = 253;
		objectsn = i;
		return;
	 }
	for (i = 0; i <= BADD; i++)
	 if (inrect(getmousex(), getmousey(), bases[i].x -scroll_x, bases[i].y -scroll_y, bases[i].x -scroll_x +BASEW, bases[i].y -scroll_y +BASEH))
	 {
		setcolor(80);
		wobj = 252;
		basesn = i;
		return;
	 }
	if (inrotrect(getmousex(), getmousey(), tank.x -scroll_x, tank.y -scroll_y, tank.ang, TANK_W, TANK_H))
	{
	 wobj = 255;
	 return;
	}
 }
}
void main(int argc, char *argv[])
{
 for (int i = 0; i < MAXOBJECTS; i++)
 {
	objects[i].x = -20;
	objects[i].y = -20;
	objects[i].type = 0;
 }
 for (i = 0; i < MAXBASES; i++)
 {
	bases[i].x = -20;
	bases[i].y = -20;
	bases[i].gap = 0;
	bases[i].power = 0;
 }
 if (argc == 2)
	if (!loadmap(argv[1], &map))
	{
	 clrscr();
	 cout << "FILE NOT FOUND!!\n";
	 exit(0);
	}
 if (!loadsprites())
 {
	clrscr();
	cout << "NOT ENOUGH MEMORY!\n";
	exit(0);
 }
 init320x200();
 if (!loadpal(PAL_FILE))
 {
	closegraph();
	clrscr();
	cout << "FILE NOT FOUND!!\n";
	exit(0);
 }
 getskeys();
 getvirscr(&scr);
 getvirscr(&scr2);
 getgtimer();
 maketbls();
 randomize();
 setcolor(14);
 rectangle(0, 0, (WIN_W *TILE_W) +1, (WIN_H *TILE_H) +1);
 if (!map)
 {
	map = (unsigned char *)malloc(MAP_W *MAP_H);
	for (int i = 0; i < MAP_W *MAP_H; i++)
	 map[i] = random(2);
 }
 screenis(scr);
 char TYPE[256] = "";
 while(!done)
 {
	if (keydown(1))
	 if (isexit()) done = 1;
	if (keydown(24)) menu();
	if (keydown(20)) tankmenu();
	if (keydown(18)) enemymenu();
	if (keydown(57)) objectmenu();
	if (keydown(15)) levelmenu();
	if (keydown(48)) basemenu();
	if (keydown(33))
	{
	 setflyers();
	 clearskeys();
	}
	if (keydown(2))
	{
	 sound(10000);
	 delay(100);
	 nosound();
	 if (OADD < MAXOBJECTS)
	 {
		objectsn++;
		OADD++;
		objects[objectsn].x = (getmousex() -1) +scroll_x;
		objects[objectsn].y = (getmousey() -1) +scroll_y;
		switch(random(4))
		{
		 case 0: objects[objectsn].type = 0; break;
		 case 1: objects[objectsn].type = 1; break;
		 case 2: objects[objectsn].type = 2; break; //Except bonus no. 4 -lives..
		 case 3: objects[objectsn].type = 4; break;
		}
	 }
	 keypress[2] = 0;
	}
	if (keydown(3))
	{
	 objects[objectsn].type++;
	 objects[objectsn].type %= 4;
	 keypress[3] = 0;
	}
	if (keydown(4))
	{
	 sound(4000);
	 delay(200);
	 nosound();
	 if (EADD < MAXENEMIES)
	 {
		EADD++;
		enemiesn++;
		enemies[enemiesn].x = (getmousex() -1) +scroll_x;
		enemies[enemiesn].y = (getmousey() -1) +scroll_y;
		enemies[enemiesn].ang = 0;
		enemies[enemiesn].speed = 0;
		enemies[enemiesn].turn_speed = random(15) +30;
		enemies[enemiesn].power = random(10) +30;
		enemies[enemiesn].steps = 0;
		enemies[enemiesn].behavior = TURRET;
	 }
	 keypress[4] = 0;
	}
	if (keydown(5)) memset(map, 2, 96*96);
	copyscreen(scr, scr2);
	checkscrll();
	putobjs();
	getobjs();
	drawtb();
	drawscroll();
	drawmouse();
	switch(objects[objectsn].type)
	{
	 case 0: strcpy(TYPE, "ROCKET"); break;
	 case 1: strcpy(TYPE, "TURBO"); break;
	 case 2: strcpy(TYPE, "POWER"); break;
	 case 3: strcpy(TYPE, "LIVES"); break;
	 case 4: strcpy(TYPE, "SHIELD"); break;
	}
	writestrxy(0, 192, wobj);
	drawscreen(scr);
 }
 closegtimer();
 closevirscr(scr2);
 closevirscr(scr);
 closeskeys();
 mousewindow(0, 0, maxx, maxy);
 closegraph();
}
