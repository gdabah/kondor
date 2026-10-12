//This header handles the Windows, inputs and menu's...
float cy, cx = 0.4, dx = 0.02; //Cursor position
char input[256] = ""; //String
double ninput;        //Number
#define CTITLE 80
#define CSTRING 56
#define CCURSOR 33
#define CENEMIES 33
void window(int x, int y, int w, int h, char *title)
{
 if ((strlen(title) *8) > w) w = strlen(title) *8;
 w += 10;
 setcolor(25);
 horline(y +1, x +3, x +w -3);
 horline(y +2, x +2, x +w -2);
 horline(y +3, x +1, x +w -1);
 for (int j = 4; j <= (h -4); j++)
	horline(y +j, x +1, x +w -1);
 horline(y +h -1, x +3, x +w -3);
 horline(y +h -2, x +2, x +w -2);
 horline(y +h -3, x +1, x +w -1);
 setcolor(14);
 //crectangle(x, y, x +w, y +h);
 setcolor(56);
 horline(y +10, x +1, x +w -1);
 setcolor(CTITLE);
 writestrxy(x +(w /2) -(strlen(title) *8) /2 +2, y +2, title);
}
char getkey2ch(int keyn)
{
 switch(keyn)
 {
	case 2: return('1');
	case 3: return('2');
	case 4: return('3');
	case 5: return('4');
	case 6: return('5');
	case 7: return('6');
	case 8: return('7');
	case 9: return('8');
	case 10: return('9');
	case 11: return('0');
	case 12: return('-');
	case 13: return('=');
	case 16: return('Q');
	case 17: return('W');
	case 18: return('E');
	case 19: return('R');
	case 20: return('T');
	case 21: return('Y');
	case 22: return('U');
	case 23: return('I');
	case 24: return('O');
	case 25: return('P');
	case 26: return('[');
	case 27: return(']');
	case 30: return('A');
	case 31: return('S');
	case 32: return('D');
	case 33: return('F');
	case 34: return('G');
	case 35: return('H');
	case 36: return('J');
	case 37: return('K');
	case 38: return('L');
	case 39: return(':');
	case 40: return(char(39));
	case 41: return('`');
	case 43: return('\\');
	case 44: return('Z');
	case 45: return('X');
	case 46: return('C');
	case 47: return('V');
	case 48: return('B');
	case 49: return('N');
	case 50: return('M');
	case 51: return(',');
	case 52: return('.');
	case 53: return('/');
	default: return('\0');
 }
}
void drawcur(int x, int y, int il = 0)
{
 setcolor(CCURSOR);
 if (cx > 3) { dx *= (-1); cy = 0; }
 if (cx < 0) { dx *= (-1); cy = 1; }
 cx += dx;
 horline(y +cy, x +cx +(il *8), x +3 +cx +(il *8));
}
int getinput(int x, int y, int h, char *title, char *string, int MAXSTR = 255)
{
 int bl = 0,//biggest length
 scrllstrx = 0,//scroll of text position
 idone = 0,
 il = 0, //screen position
 sk = 0, //scankey value
 kb = 1; //is the user pressing
 if (strlen(string) > strlen(title)) bl = strlen(string);
 else bl = strlen(title);
 memset(input, 0, 256);
 clearskeys();
 while(!idone)
 {
	copyscreen(scr, scr2);
	if (keydown(28)) idone = 1;
	if (keydown(1))
	{
	 ninput = (-1);
	 return(0);
	}
	drawtb();
	window(x, y, strlen(string) *8 +10, h, title);
	setcolor(CSTRING);
	writestrxy(x +3, y +12, string);
	sk = skeypressed();
	if (sk)
	{
	 if (kb)
	 {
		kb = 0;
		char c = getkey2ch(sk);
		if ((sk == 14) && (scrllstrx +il > 0))
		{
		 if ((il +scrllstrx) != -1) il--;
		 input[scrllstrx +il] = '\0';
		 input[scrllstrx +(il +1)] = '\0';
		}
		if (sk == 57) input[scrllstrx +(il++)] = ' ';
		if (c != '\0')
		{
		 if (il +scrllstrx < MAXSTR)
			input[scrllstrx +il++] = c;
		}
		if (keydown(203)) il--;
		if ((keydown(205)) && (input[scrllstrx +il] != '\0')) il++;
		if (il == (bl +1))
		{
		 if (scrllstrx < MAXSTR) scrllstrx++;
		 il--;
		}
		if (il == -1)
		{
		 if (scrllstrx > 0) scrllstrx--;
		 il++;
		}
	 }
	}
	else kb = 1;
	for (int dstr = scrllstrx; dstr <= scrllstrx +bl; dstr++)
	 plotchar(x +8 +(dstr *8) -(scrllstrx *8), y +h -13, input[dstr]);
	drawcur(x +6, y +h -7, il);
	drawscreen(scr);
 }
 ninput = _atold(input);
 if ((ninput == 0) && (input[0] != '0')) ninput = (-1);
 clearskeys();
 delay(60);
 return(1);
}
/*
 MENU TABLE
/----------/
SPEED
CLEAR
REPLACE
CHANGE W/H
SAVE
LOAD
*/
void success(char *title)
{
 copyscreen(scr, scr2);
 window(80, 60, (strlen(title) *8), 30, "SUCCESSFUL");
 setcolor(CTITLE);
 writestrxy(83, 75, title);
 drawscreen(scr);
 delay(700);
}
void changespd()
{
 int sdone = 0, m = 0;
 while(!sdone)
 {
	copyscreen(scr, scr2);
	if (keydown(28))
	{
	 clearskeys();
	 switch(m)
	 {
		case 0: scrllspdx = 1; scrllspdy = 1; sdone = 1; break;
		case 1: scrllspdx = 3; scrllspdy = 3; sdone = 1; break;
		case 2: scrllspdx = 5; scrllspdy = 5; sdone = 1; break;
		case 3: scrllspdx = 10; scrllspdy = 10; sdone = 1; break;
		case 4: sdone = 1; break;
	 }
	}
	if (keydown(208))
	{
	 if (m < 4) m++;
	 else m = 0;
	 clearskeys();
	}
	if (keydown(200))
	{
	 if (m > 0) m--;
	 else m = 4;
	 clearskeys();
	}
	drawtb();
	window(100, 60, 90, 65, "SCROLL SPEED");
	drawcur(103, 78 +(m *10));
	setcolor(CSTRING);
	writestrxy(113, 75, "SLOW");
	writestrxy(113, 85, "MEDUIM");
	writestrxy(113, 95, "FAST");
	writestrxy(113, 105, "FASTEST");
	writestrxy(113, 115, "EXIT");
	drawscreen(scr);
 }
 scroll_x = 0;
 scroll_y = 0;
 drawscroll();
}
void clearmap()
{
 char YESTR[256] = "Y";
 if (!getinput(80, 60, 40, "CLEAR MAP", "Are you sure?", 1)) return;
 if (!strcmp(input, YESTR))
 {
	success("CLEARING!");
	memset(map, 0, MAP_W *MAP_H);
	for (int i = 0; i < MAXOBJECTS; i++)
	{
	 objects[i].x = 0;
	 objects[i].y = 0;
	 objects[i].type = 0;
	}
	for (i = 0; i < MAXENEMIES; i++)
	{
	 enemies[i].behavior = EMPTY;
	 enemies[i].x = 0;
	 enemies[i].y = 0;
	 enemies[i].ang = 0;
	 enemies[i].speed = 0;
	 enemies[i].turn_speed = 0;
	 enemies[i].power = 0;
	 enemies[i].steps = 0;
	 for (int j = 0; j < MAXSTEPS; j++)
	 {
		enemies[i].PATH[j].x = 0;
		enemies[i].PATH[j].y = 0;
	 }
	}
	EADD = 0;
	tank.x = 0;
	tank.y = 0;
	enemiesn = 0;
	objectsn = 0;
	drawscroll();
 }
}
void replace()
{
 getinput(80, 60, 40, "REPLACE", "Enter dest: ", 2);
 int d = ninput;
 getinput(80, 60, 40, "REPLACE", "Enter source: ", 2);
 int s = ninput;
 if ((s >= SPRITES_NO) || (d >= SPRITES_NO)) return;
 if ((s == (-1)) || (d == (-1))) return;
 for (int i = 0; i < MAP_W *MAP_H; i++)
	if (((d == 0) || (d == 1)) || ((d >= 7)
		&& (d <= 13)) || ((d >= 14) && (d <= 20)))
	{
	 if ((d == 0) || (d == 1)) map[i] = random(2);
	 else if ((d >= 7) && (d <= 13)) map[i] = random(7) +7;
		else if ((d >= 14) && (d <= 20)) map[i] = random(7) +14;
	}
 success("REPLACING!");
 drawscroll();
}
//This routine checks the directory and if the name of the file is legal!
int getpfile(char *fpath)
{
 int p = 0;
 boolean pp;
 for (int i = 0; i < strlen(fpath); i++)
	if (fpath[i] == '\\') p = i;
 for (i = p, p = 0; i < strlen(fpath); i++)
 {
	pp = true;
	if (fpath[i] != '.') pp = false;
	if (pp) p = i;
 }
 if (!p) return(0);
 for (i = p +4; i <= strlen(fpath); i++)
	fpath[i] = '\0';
 if (fpath[strlen(fpath) -1] == '.') return(0);
 return(1);
}
void savemap()
{
 if (!getinput(80, 60, 40, "SAVE", "Enter a file name: ", 255)) return;
 if (getpfile(input))
 {
	savemap(input, map);
	success("SAVING!");
 }
}
void loadmap()
{
 if (!getinput(80, 60, 40, "LOAD", "Enter a file name: ", 255)) return;
 if (getpfile(input))
	if (fileexist(input))
	{
	 if (!loadmap(input, &map))
	 {
		if (map) free(map);
		closevirscr(scr2);
		closevirscr(scr);
		closeskeys();
		closegraph();
		cout << "BAD FORMAT!";
		exit(0);
	 }
	 success("LOADING!");
	 drawscroll();
	}
}
void menu()
{
 int mdone = 0, m = 0;
 while(!mdone)
 {
	copyscreen(scr, scr2);
	if (keydown(28))
	{
	 clearskeys();
	 switch(m)
	 {
		case 0: changespd(); break;
		case 1: clearmap(); break;
		case 2: replace(); break;
		case 3: drawmap(); break;
		case 4: savemap(); break;
		case 5: loadmap(); break;
		case 6: mdone = 1; break;
	 }
	}
	if (keydown(208))
	{
	 if (m < 6) m++;
	 else m = 0;
	 clearskeys();
	}
	if (keydown(200))
	{
	 if (m > 0) m--;
	 else m = 6;
	 clearskeys();
	}
	drawtb();
	window(100, 60, 90, 85, "MENU!");
	drawcur(103, 78 +(m *10));
	setcolor(CSTRING);
	writestrxy(113, 75, "SET SCROLL");
	writestrxy(113, 85, "CLEAR MAP");
	writestrxy(113, 95, "REPLACE");
	writestrxy(113, 105, "WATCH MAP");
	writestrxy(113, 115, "SAVE MAP");
	writestrxy(113, 125, "LOAD MAP");
	writestrxy(113, 135, "EXIT");
	drawscreen(scr);
 }
}
//Tank menu
void tsp()
{
 success("PRESS ON POS!");
 wobj = 255;
}
void tcannonrot()
{
 if (!getinput(60, 60, 40, "TANK", "Enter cannon turn speed: ", 5)) return;
 tank.cannon_turn_speed = ninput;
}
void tspd()
{
 if (!getinput(80, 60, 40, "TANK", "Enter accel: ", 5)) return;
 tank.accel = ninput;
}
void trotspd()
{
 if (!getinput(80, 60, 40, "TANK", "Enter rot speed: ", 5)) return;
 tank.turn_speed = ninput;
}
void taccl()
{
 if (!getinput(80, 60, 40, "TANK", "Enter max speed: ", 5)) return;
 tank.maxspeed = ninput;
}
void tpwr()
{
 if (!getinput(80, 60, 40, "TANK", "Enter power ", 4)) return;
 tank.power = ninput;
}
void tang()
{
 if (!getinput(80, 60, 40, "TANK", "Enter angle ", 4)) return;
 tank.ang = ninput;
}
void tankmenu()
{
 int t = 0, tdone = 0;
 while(!tdone)
 {
	copyscreen(scr, scr2);
	if (keydown(28))
	{
	 clearskeys();
	 switch(t)
	 {
		case 0: tsp(); break;
		case 1: tspd(); break;
		case 2: tcannonrot(); break;
		case 3: trotspd(); break;
		case 4: tpwr(); break;
		case 5: taccl(); break;
		case 6: tang(); break;
		case 7: tdone = 1; break;
	 }
	}
	if (keydown(208))
	{
	 if (t < 7) t++;
	 else t = 0;
	 clearskeys();
	}
	if (keydown(200))
	{
	 if (t > 0) t--;
	 else t = 7;
	 clearskeys();
	}
	drawtb();
	window(100, 60, 90, 95, "TANK SETTING");
	drawcur(103, 78 +(t *10));
	setcolor(CSTRING);
	writestrxy(113, 75, "START POS");
	writestrxy(113, 85, "ACCEL");
	writestrxy(113, 95, "CANNON ROT");
	writestrxy(113, 105, "ROT SPEED");
	writestrxy(113, 115, "POWER");
	writestrxy(113, 125, "MAX SPEED");
	writestrxy(113, 135, "ANGLE");
	writestrxy(113, 145, "EXIT");
	drawmouse();
	drawscreen(scr);
 }
}
//Enemies handle, this draws all enemies
void enemieshandle()
{
 for (int i = 0; i <= EADD; i++)
	if ((enemies[i].x -scroll_x > -(ENEMY_W >> 1))
	&& (enemies[i].y -scroll_y > -(ENEMY_H >> 1))
	&& (enemies[i].x > 0) && (enemies[i].y > 0))
	{
	 switch(enemies[i].behavior)
	 {
		case TURRET:
		 editordrawrotsprt(enemies[i].x -scroll_x, enemies[i].y -scroll_y,
											 TURPADW >> 1, TURPADH >> 1, 0,
											 TURPADW, TURPADH, TURPAD_IMG);
		break;
		case PIPER:
		 editordrawrotsprt(enemies[i].x -scroll_x, enemies[i].y -scroll_y,
											 FLYW >> 1, FLYH >> 1, enemies[i].ang,
											 FLYW, FLYH, FLY_IMG);
		break;
		case MIG:
		 editordrawrotsprt(enemies[i].x -scroll_x, enemies[i].y -scroll_y,
											 MIGW >> 1, MIGH >> 1, enemies[i].ang,
											 MIGW, MIGH, MIG_IMG);
		break;
		default:
		editordrawrotsprt(enemies[i].x -scroll_x, enemies[i].y -scroll_y,
										 ENEMY_W >> 1, ENEMY_H >> 1, enemies[i].ang,
										 ENEMY_W, ENEMY_H, enemy_img);
	 }
	}
}
//Enemies menu
void ebehavior()
{
 int ebdone = 0, t = 0;
 while(!ebdone)
 {
	copyscreen(scr, scr2);
	if (keydown(28))
	{
	 clearskeys();
	 switch(t)
	 {
		case 0: enemies[enemiesn].behavior = TURRET; ebdone = 1; break;
		case 1: enemies[enemiesn].behavior = CIRCLE; ebdone = 1; break;
		case 2: enemies[enemiesn].behavior = RANDOM; ebdone = 1; break;
		case 3: enemies[enemiesn].behavior = PATH_FIND; ebdone = 1; break;
		case 4: enemies[enemiesn].behavior = ANGLE; ebdone = 1; break;
		case 5: enemies[enemiesn].behavior = FOLLOW; ebdone = 1; break;
		case 6: enemies[enemiesn].behavior = PIPER; ebdone = 1; break;
		case 7: enemies[enemiesn].behavior = MIG; ebdone = 1; break;
		case 8: ebdone = 1; break;
	 }
	}
	if (keydown(208))
	{
	 if (t < 8) t++;
	 else t = 0;
	 clearskeys();
	}
	if (keydown(200))
	{
	 if (t > 0) t--;
	 else t = 8;
	 clearskeys();
	}
	drawtb();
	window(100, 60, 60, 115, "BEHAVIOR");
	setcolor(CENEMIES);
	plotchar(120, 75, '[');
	writestrxy(128, 75, enemiesn +1);
	plotchar(144, 75, ']');
	setcolor(CSTRING);
	writestrxy(113, 85, "TURRET");
	writestrxy(113, 95, "CIRCLE");
	writestrxy(113, 105, "RANDOM");
	writestrxy(113, 115, "PATH");
	writestrxy(113, 125, "ANGLE");
	writestrxy(113, 135, "FOLLOW");
	writestrxy(113, 145, "PIPER");
	writestrxy(113, 155, "MIG");
	writestrxy(113, 165, "EXIT");
	drawcur(103, 88 +(t *10));
	drawmouse();
	drawscreen(scr);
 }
}
void estartpos()
{
 switch(enemies[enemiesn].behavior)
 {
	case EMPTY:
	 copyscreen(scr, scr2);
	 window(80, 60, 185, 30, "START POS");
	 setcolor(CTITLE);
	 writestrxy(103, 75, "DEFINE A BEHAVIOR!");
	 drawscreen(scr);
	 delay(2000);
	 clearskeys();
	 break;
	case TURRET: success("PRESS ON POS!"); wobj = 254; break;
	case CIRCLE: success("PRESS ON POS!"); wobj = 254; break;
	case RANDOM: success("PRESS ON POS!"); wobj = 254; break;
	case PATH_FIND: makepath(); break;
	case ANGLE: success("PRESS ON POS!"); wobj = 254; break;
	case FOLLOW: success("PRESS ON POS!"); wobj = 254; break;
	case PIPER: success("PRESS ON POS!"); wobj = 254; break;
	case MIG: makepath(); break;
 }
}
void emaxspd()
{
 if (!getinput(80, 60, 40, "ENEMY", "Enter speed: ", 5)) return;
 enemies[enemiesn].speed = ninput;
}
void erotspd()
{
 if (!getinput(80, 60, 40, "ENEMY", "Enter rot speed: ", 5)) return;
 enemies[enemiesn].turn_speed = ninput;
}
void eangle()
{
 if (!getinput(80, 60, 40, "ENEMY", "Enter angle: ", 5)) return;
 enemies[enemiesn].ang = ninput;
}
void epower()
{
 if (!getinput(80, 60, 40, "ENEMY", "Enter power: ", 4)) return;
 enemies[enemiesn].power = ninput;
}
void setenemy()
{
 int t = 0;
 int sedone = 0;
 while(!sedone)
 {
	copyscreen(scr, scr2);
	if (keydown(28))
	{
	 clearskeys();
	 switch(t)
	 {
		case 0: ebehavior(); break;
		case 1: estartpos(); break;
		case 2: emaxspd(); break;
		case 3: erotspd(); break;
		case 4: eangle(); break;
		case 5: epower(); break;
		case 6: sedone = 1; break;
	 }
	}
	if (keydown(208))
	{
	 if (t < 6) t++;
	 else t = 0;
	 clearskeys();
	}
	if (keydown(200))
	{
	 if (t > 0) t--;
	 else t = 6;
	 clearskeys();
	}
	drawtb();
	window(100, 60, 85, 85, "SETTING");
	setcolor(CENEMIES);
	plotchar(160, 135, '[');
	writestrxy(168, 135, enemiesn +1);
	plotchar(184, 135, ']');
	setcolor(CSTRING);
	writestrxy(113, 75, "BEHAVIOR");
	writestrxy(113, 85, "START POS");
	writestrxy(113, 95, "MAX SPEED");
	writestrxy(113, 105, "ROT SPEED");
	writestrxy(113, 115, "ANGLE");
	writestrxy(113, 125, "POWER");
	writestrxy(113, 135, "EXIT");
	drawcur(103, 78 +(t *10));
	drawmouse();
	drawscreen(scr);
 }
}
void delenemy()
{
 if ((EADD > 0) && (enemiesn > 0))
 {
	enemies[enemiesn] = enemies[EADD];
	EADD--;
	if (enemiesn >= EADD) enemiesn = EADD;
 }
}
void enemymenu()
{
 int t = 0;
 int edone = 0;
 while(!edone)
 {
	copyscreen(scr, scr2);
	if (keydown(28))
	{
	 clearskeys();
	 switch(t)
	 {
		case 0:
		 if (EADD < MAXENEMIES)
		 {
			EADD++;
			if (enemiesn < EADD) enemiesn++;
			enemies[enemiesn].x = 0;
			enemies[enemiesn].y = 0;
		 }
		break;
		case 1: delenemy(); break;
		case 2: setenemy(); break;
		case 3: if (enemiesn < EADD) enemiesn++; break;
		case 4: if (enemiesn > 0) enemiesn--; break;
		case 5: edone = 1; break;
	 }
	}
	if (keydown(208))
	{
	 if (t < 5) t++;
	 else t = 0;
	 clearskeys();
	}
	if (keydown(200))
	{
	 if (t > 0) t--;
	 else t = 5;
	 clearskeys();
	}
	drawtb();
	window(100, 60, 70, 75, "ENEMIES");
	setcolor(CENEMIES);
	plotchar(150, 75, '[');
	writestrxy(158, 75, enemiesn +1);
	plotchar(174, 75, ']');
	setcolor(CSTRING);
	writestrxy(113, 75, "ADD");
	writestrxy(113, 85, "DEL");
	writestrxy(113, 95, "SET");
	writestrxy(113, 105, "NEXT");
	writestrxy(113, 115, "PREVIOUS");
	writestrxy(113, 125, "EXIT");
	drawcur(103, 78 +(t *10));
	drawmouse();
	drawscreen(scr);
 }
}
//Objects menu
void otype()
{
 int otdone = 0, t = 0;
 while(!otdone)
 {
	copyscreen(scr, scr2);
	if (keydown(28))
	{
	 clearskeys();
	 switch(t)
	 {
		case 5: otdone = 1; break;
		default: objects[objectsn].type = t; otdone = 1;
	 }
	}
	if (keydown(208))
	{
	 if (t < 5) t++;
	 else t = 0;
	 clearskeys();
	}
	if (keydown(200))
	{
	 if (t > 0) t--;
	 else t = 5;
	 clearskeys();
	}
	drawtb();
	window(100, 60, 60, 85, "BEHAVIOR");
	setcolor(CENEMIES);
	plotchar(120, 75, '[');
	writestrxy(128, 75, objectsn +1);
	plotchar(144, 75, ']');
	setcolor(CSTRING);
	writestrxy(113, 85, "ROCKET");
	writestrxy(113, 95, "NITRO");
	writestrxy(113, 105, "POWER");
	writestrxy(113, 115, "LIVES");
	writestrxy(113, 125, "SHIELD");
	writestrxy(113, 135, "EXIT");
	drawcur(103, 88 +(t *10));
	drawmouse();
	drawscreen(scr);
 }
}
void ostartpos()
{
 success("PRESS ON POS!");
 wobj = 253;
}
void setobject()
{
 int t = 0;
 int sodone = 0;
 while(!sodone)
 {
	copyscreen(scr, scr2);
	if (keydown(28))
	{
	 clearskeys();
	 switch(t)
	 {
		case 0: otype(); break;
		case 1: ostartpos(); break;
		case 2: sodone = 1; break;
	 }
	}
	if (keydown(208))
	{
	 if (t < 2) t++;
	 else t = 0;
	 clearskeys();
	}
	if (keydown(200))
	{
	 if (t > 0) t--;
	 else t = 2;
	 clearskeys();
	}
	drawtb();
	window(100, 60, 85, 45, "SETTING");
	setcolor(CENEMIES);
	plotchar(160, 95, '[');
	writestrxy(168, 95, objectsn +1);
	plotchar(184, 95, ']');
	setcolor(CSTRING);
	writestrxy(113, 75, "TYPE");
	writestrxy(113, 85, "START POS");
	writestrxy(113, 95, "EXIT");
	drawcur(103, 78 +(t *10));
	drawmouse();
	drawscreen(scr);
 }
}
void delobject()
{
 if ((OADD > 0) && (objectsn > 0))
 {
	objects[objectsn] = objects[OADD];
	OADD--;
	if (objectsn >= OADD) objectsn = OADD;
 }
}
void objectmenu()
{
 int t = 0;
 int odone = 0;
 while(!odone)
 {
	copyscreen(scr, scr2);
	if (keydown(28))
	{
	 clearskeys();
	 switch(t)
	 {
		case 0:
		 if (OADD < MAXOBJECTS)
		 {
			OADD++;
			if (objectsn < OADD) objectsn++;
		 }
		break;
		case 1: delobject(); break;
		case 2: setobject(); break;
		case 3: if (objectsn < OADD) objectsn++; break;
		case 4: if (objectsn > 0) objectsn--; break;
		case 5: odone = 1; break;
	 }
	}
	if (keydown(208))
	{
	 if (t < 5) t++;
	 else t = 0;
	 clearskeys();
	}
	if (keydown(200))
	{
	 if (t > 0) t--;
	 else t = 5;
	 clearskeys();
	}
	drawtb();
	window(100, 60, 70, 75, "OBJECTS");
	setcolor(CENEMIES);
	plotchar(150, 75, '[');
	writestrxy(158, 75, objectsn +1);
	plotchar(174, 75, ']');
	setcolor(CSTRING);
	writestrxy(113, 75, "ADD");
	writestrxy(113, 85, "DEL");
	writestrxy(113, 95, "SET");
	writestrxy(113, 105, "NEXT");
	writestrxy(113, 115, "PREVIOUS");
	writestrxy(113, 125, "EXIT");
	drawcur(103, 78 +(t *10));
	drawmouse();
	drawscreen(scr);
 }
}
int isexit()
{
 int t = 0;
 while(1)
 {
	copyscreen(scr, scr2);
	if (keydown(28))
	{
	 clearskeys();
	 return(t);
	}
	if (keydown(208))
	{
	 if (t < 1) t++;
	 else t = 0;
	 clearskeys();
	}
	if (keydown(200))
	{
	 if (t > 0) t--;
	 else t = 1;
	 clearskeys();
	}
	drawtb();
	window(100, 60, 40, 35, "EXIT?");
	setcolor(CSTRING);
	writestrxy(113, 75, "NO");
	writestrxy(113, 85, "YES");
	drawcur(103, 78 +(t *10));
	drawmouse();
	drawscreen(scr);
 }
}
void levelmenu()
{
 int t = 0;
 while(1)
 {
	copyscreen(scr, scr2);
	if (keydown(28))
	{
	 switch (t)
	 {
		case 0:
		 if (!getinput(80, 60, 40, "CAPTION", "Enter level caption: ", 50)) return;
		 strcpy(CAPTION, input);
		break;
		case 1:
		 if (!getinput(80, 60, 40, "LEVEL", "Enter level number: ", 2)) return;
		 if (ninput == 0) return;
		 LEVEL = ninput;
		break;
		case 2: return;
	 }
	 clearskeys();
	}
	if (keydown(208))
	{
	 if (t < 2) t++;
	 else t = 0;
	 clearskeys();
	}
	if (keydown(200))
	{
	 if (t > 0) t--;
	 else t = 2;
	 clearskeys();
	}
	drawtb();
	window(100, 60, 40, 45, "LEVEL MENU");
	setcolor(CSTRING);
	writestrxy(113, 75, "STRING");
	writestrxy(113, 85, "LEVEL #");
	writestrxy(113, 95, "EXIT");
	drawcur(103, 78 +(t *10));
	drawmouse();
	drawscreen(scr);
 }
}
void bgap()
{
 if (!getinput(80, 60, 40, "BASES", "Enter gap: ", 4)) return;
 bases[basesn].gap = ninput;
}
void bpower()
{
 if (!getinput(80, 60, 40, "BASES", "Enter power: ", 4)) return;
 bases[basesn].power = ninput;
}
void bstartpos()
{
 success("PRESS ON POS!");
 wobj = 252;
}
void setbase()
{
 int t = 0;
 int bdone = 0;
 while(!bdone)
 {
	copyscreen(scr, scr2);
	if (keydown(28))
	{
	 clearskeys();
	 switch(t)
	 {
		case 0: bgap(); break;
		case 1: bpower(); break;
		case 2: bstartpos(); break;
		case 3: bdone = 1; break;
	 }
	}
	if (keydown(208))
	{
	 if (t < 3) t++;
	 else t = 0;
	 clearskeys();
	}
	if (keydown(200))
	{
	 if (t > 0) t--;
	 else t = 3;
	 clearskeys();
	}
	drawtb();
	window(100, 60, 85, 55, "SETTING");
	setcolor(CENEMIES);
	plotchar(160, 105, '[');
	writestrxy(168, 105, basesn +1);
	plotchar(184, 105, ']');
	setcolor(CSTRING);
	writestrxy(113, 75, "SET GAP");
	writestrxy(113, 85, "POWER");
	writestrxy(113, 95, "START POS");
	writestrxy(113, 105, "EXIT");
	drawcur(103, 78 +(t *10));
	drawmouse();
	drawscreen(scr);
 }
}
void delbase()
{
 if ((BADD > 0) && (basesn > 0))
 {
	bases[basesn] = bases[BADD];
	BADD--;
	if (basesn >= BADD) basesn = BADD;
 }
}
void basemenu()
{
 int t = 0;
 int bdone = 0;
 while(!bdone)
 {
	copyscreen(scr, scr2);
	if (keydown(28))
	{
	 clearskeys();
	 switch(t)
	 {
		case 0:
		 if (BADD < MAXBASES)
		 {
			BADD++;
			if (basesn < BADD) basesn++;
		 }
		break;
		case 1: delbase(); break;
		case 2: setbase(); break;
		case 3: if (basesn < BADD) basesn++; break;
		case 4: if (basesn > 0) basesn--; break;
		case 5: bdone = 1; break;
	 }
	}
	if (keydown(208))
	{
	 if (t < 5) t++;
	 else t = 0;
	 clearskeys();
	}
	if (keydown(200))
	{
	 if (t > 0) t--;
	 else t = 5;
	 clearskeys();
	}
	drawtb();
	window(100, 60, 70, 75, "BASES");
	setcolor(CENEMIES);
	plotchar(150, 75, '[');
	writestrxy(158, 75, basesn +1);
	plotchar(174, 75, ']');
	setcolor(CSTRING);
	writestrxy(113, 75, "ADD");
	writestrxy(113, 85, "DEL");
	writestrxy(113, 95, "SET");
	writestrxy(113, 105, "NEXT");
	writestrxy(113, 115, "PREVIOUS");
	writestrxy(113, 125, "EXIT");
	drawcur(103, 78 +(t *10));
	drawmouse();
	drawscreen(scr);
 }
}
void setflyers()
{
 if (!getinput(80, 60, 40, "AIR PLANES", "Enter number of Planes: ", 3)) return;
 FLYERS = ninput;
}