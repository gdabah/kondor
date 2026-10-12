#include "images.h"
#include "coll.h"
#include "kgraph.h"
#include "layers.h"
#include "types.h"
#include "slots.h"
sprite_type bullets_sprts[2];
#include "scroll.h"
#include "bullets.h"
#include "ai.h"
#include "expl.h"
#include "enemies.h"
#include "objects.h"
#include "ptank.h"
#include "frames.h"
#include "bonus.h"
#include "loadmap.h"
#include "airforce.h"
#include "bases.h"
void load_side_bar(); //FORWARD;
#include "end.h"
#include "misc.h"
void load_side_bar()
{
 screenis(bkg);
 if (!load32(SIDE_BAR_FILE)) filerr();
 setcolor(0);
 drawslotrect(262, 70, 284, 90);
 drawslotrect(291, 70, 313, 90);
 drawslotrect(262, 100, 284, 120);
 drawslotrect(291, 100, 313, 120);
 drawstringreg(((SCREEN_W -strlen(MSG) *6) >> 1), SCREEN_H +2, MSG);
 setcolor(45);
 bar(263, 131, 263 +(tank.power /204), 134);
 screenis(buffer);
 for (int i = 0; i < MAX_SLOTS; i++)
	if (slots.data[i].amount) slots.drawsprt(i);
 drawslots(80);
}
void drawNhandle()
{
 tank.handle();
 check4scroll();
 handlecounter();
 expls.handle();
 copyscreen(buffer, bkg);
 bullets.handle();
 air_enemies.handle();
 bases.handle();
 enemies.handle();
 objects.draw();
 bullets.draw();
 enemies.draw();
 bases.draw();
 tank.draw();
 expls.draw();
 air_enemies.draw();
 drawminmap();
 slots.draw();
 setcolor(86);
 drawstringreg(284, 145, tank.lives);
 waitretrace();
 drawscreen(buffer);
}
void start_game()
{
 clearskeys();
 set_game_pal();
 load_side_bar();
 drawscroll();
 gameloop = 0;
 while(!gameloop)
 {
	if (keydown(arrowdown)) tank.speed -= tank.accel;
	if (keydown(arrowup)) tank.speed += tank.accel;
	if ((!keydown(arrowdown)) && (!keydown(arrowup))) tank.speed -= 0.03 *tank.speed;
	if (tank.speed > tank.maxspeed) tank.speed = tank.maxspeed;
	if (tank.speed < -tank.maxspeed) tank.speed = -tank.maxspeed;
	//left arrow--+
	//right arrow |_-->in tank.handle
	if (keydown(keylside))
	{
	 drawslots(0);
	 current_slot--;
	 if (current_slot == -1) current_slot = 3;
	 drawslots(80);
	 keypress[keylside] = 0;
	}
	if (keydown(keyrside))
	{
	 drawslots(0);
	 current_slot++;
	 if (current_slot == 4) current_slot = 0;
	 drawslots(80);
	 keypress[keyrside] = 0;
	}
	if (keydown(keyrotcanr)) tank.turn_cannon(tank.cannon_turn_speed);
	if (keydown(keyrotcanl)) tank.turn_cannon(-tank.cannon_turn_speed);
	if (keydown(breakskey)) tank.speed *= 0.9; // Breaks
	if (keydown(firekey)) shoot();
	else canshoot = true;
	if (tank.height <= -tank.halfwidth_3)
	 tank.height = -tank.halfwidth_3;
	if (keydown(skeyESC)) gameloop = 1;
	if (keydown(itemkey)) usebonus();
	else canuseitem = true;
	drawNhandle();
 }
}