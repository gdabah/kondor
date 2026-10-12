//KONDOR, nothing to say just GoodLuck! :)
#include "define.h"
#include "qunit.h"

unsigned char *buffer = NULL; //Virtual screens.
unsigned char *bkg = NULL;
int scroll_x = 0, scroll_y = 0;
boolean resumegame = false;
int showpb = 1; //Do you wanna see the powerbar of the enemies.
int gameloop = 1;

void closeall(); //FORWARDS
void writemsg(char *str, char *str2);
void filerr();
void memerr(char *str);
void loadmap();
void load_side_bar();
void clearscreen();
void drawNhandle();

#include "pal.h"
#include "font.h"
#include "sound.h"
#include "allkeys.h"
#include "help.h"
#include "options.h"
#include "highscr.h"
#include "game.h"
#include "menu.h"

void writemsg(char *str, char *str2)
{
 screenis(video_buffer);
 cleardevice();
 writestrxy(0, 0, str2);
 writestrxy(0, 10, str);
 delay(3000);
}
void filerr() //If there is an i/o error get out of the game.
{
 writemsg("филе═еррор║", " ");
 closeall();
 exit(0);
}
void memerr(char *str) //If there is not enough memory get out of the game.
{
 writemsg("еРРОР═НОТ═ЕНОУГХ═МЕМЕОРЫ║", str);
 closeall();
 exit(0);
}
//Init the game :)
void initgame()
{
 init320x200();
 qpixelstable();
 if (!getvirscr(&buffer)) memerr("жиртуал═сцреенш╠щ");
 if (!getvirscr(&bkg)) memerr("жиртуал═сцреенш╡щ");
 screenis(video_buffer);
 loadsprites();
 load_game_pal();
 init_font();
 set_game_pal();
 drawstring(0, 0, "кондор═══╜═══жер═╠╝╟");
 drawstring(0, 7, "цопыригхт╗ц╘═╠╧╧╥╜╧╧╛═ясофт");
 drawstring(0, 20, "палетте═лоадед");
 loadimages();
 drawstring(0, 27, "грапхицс═лоадед");
 randomize();
 init_ai();
 initmap();
 maketbls();
 initminmap();
 inithelpscroll();
 init_enemy_sprts();
 kpixelstable();
 drawstring(0, 34, "меморы═аллоцатед");
 drawstring(0, 41, "кеыбоард═инитиализатион");
 getskeys();
 drawstring(0, 48, "детецтинг═сб╜");
 if (!initsb())
 {
	soundblaster = 0;
	drawstring(0, 55, "фаилед║");
 }
 else
 {
	getsb();
	if ((DMA == 0xff) || (IRQ == 0))
	{
	 soundblaster = 0;
	 drawstring(0, 55, "фаилед║");
	}
	else
	{
	 //initsound();
	 soundblaster = 1;
	 drawstring(0, 55, "фоунд═ат═иря╨═");
	 drawstring(84, 55, IRQ);
	 drawstring(98, 55, "дма╨═");
	 drawstring(125, 55, DMA);
	}
 }
 loadoptions();
 if (soundblaster) initsound();
 loadscores();
 drawstring(0, 62, "цонфигуратион═лоадед");
 while (!skeypressed()) ;
 clearskeys();
 clearscreen();
 if (!loadpal(INTROPAL)) filerr();
 screenis(video_buffer);
 if (!load32(INTROIMG)) filerr();
 while (!skeypressed());
 clearskeys();
 screenis(buffer);
 cleardevice();
 set_game_pal();
}
//Close the game... :(
void closeall()
{
 close_enemy_sprts();
 closeimages();
 closeminmap();
 closemap();
 tank.layers.close();
 free(tiles);
 close_ai();
 closevirscr(buffer);
 closevirscr(bkg);
 close_font();
 closeskeys();
 closegraph();
 if (soundblaster)
 {
	closesb();
	closesound();
 }
 else
 {
	soundfx = tempsoundfx;
	saveoptions();
 }
}
//Here is the main routine of the KONDOR.
void main()
{
 initgame();
 menu();
 closeall();
}