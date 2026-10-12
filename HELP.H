//This include handles the "HELP"......how to play.......
#define MAXTERRAINX 40
#define MINTERRAINX 10
#define MAXTERRAINY 900
int terrainy[MAXTERRAINY];
int hhelpscroll_y = 6;
int done = 0;
char helplines[MAXTERRAINY /6][40] = {
"╜╜╜",
"велцоме═то═кондор║",
"",
"",
"",
"",
"",
"",
"",
"цредитс╨",
"══программерс╨",
"═══орен═бецкер",
"═══гил═дабах",
"",
"═маны═тханкс═то╨",
"══стежен═дон═анд═ари═фелдман",
"┴══фор═хелпинг║═║═║",
"",
"",
"фор═упдатес═анд═нев═гамес═плеасе",
"═жисит═оур═вебсите╨",
"══ясофт╝цйб╝цом",
"",
"иф═ыоу═хаже═аны═цомментс╛",
"┴═суггестионс═ор═цомплаинтс",
"┴┴феел═фрее═то═е╜маил╨",
"┴═══вебмастерюясофт╝цйб╝цом"};
void inithelpscroll()
{
 int tempx = 20;
 for (int index = 0; index < MAXTERRAINY; index++)
 {
	switch(random(2))
	{
	 case 0: if (tempx < MAXTERRAINX) tempx++; break;
	 case 1: if (tempx > MINTERRAINX) tempx--; break;
	}
	terrainy[index] = tempx;
 }
}
void drawhelpscroll()
{
 setcolor(107);
 for (int id = hhelpscroll_y; id < hhelpscroll_y +200; id++)
 {
	horline(id -hhelpscroll_y, 0, terrainy[id]);
	plotpixel(terrainy[id] +1, id -hhelpscroll_y, 106);
	horline(id -hhelpscroll_y, 319 -terrainy[id] +1, 319);
	plotpixel(319 -terrainy[id], id -hhelpscroll_y, 106);
 }
 int starty = hhelpscroll_y /8;
 for (id = starty; id < starty +26; id++)
	drawstring(MAXTERRAINX +10, (id *8) -hhelpscroll_y, helplines[id]);
}
void gamehelp()
{
 screenis(buffer);
 cleardevice();
 blackpal();
 hhelpscroll_y = 6;
 drawhelpscroll();
 drawscreen(buffer);
 fadein(gamepal);
 done = 0;
 while(!done)
 {
	cleardevice();
	if (keydown(200)) if (hhelpscroll_y > 6) hhelpscroll_y--;
	if (keydown(208)) if (hhelpscroll_y < MAXTERRAINY -200) hhelpscroll_y++;
	if (keydown(1)) done = 1;
	drawhelpscroll();
	waitretrace();
	drawscreen(buffer);
 }
 fadeout();
}