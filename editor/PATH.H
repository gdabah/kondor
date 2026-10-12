void drawpath()
{
 if (enemies[enemiesn].steps == 0) return;
 for (int i = 0; i < (enemies[enemiesn].steps -1); i++)
 {
	setcolor(0);
	editline(enemies[enemiesn].PATH[i].x -scroll_x, enemies[enemiesn].PATH[i].y -scroll_y,
					 enemies[enemiesn].PATH[i +1].x -scroll_x, enemies[enemiesn].PATH[i +1].y -scroll_y);
	setcolor(14);
	editrectangle(enemies[enemiesn].PATH[i].x -2 -scroll_x, enemies[enemiesn].PATH[i].y -2 -scroll_y,
								enemies[enemiesn].PATH[i].x +2 -scroll_x, enemies[enemiesn].PATH[i].y +2 -scroll_y);
 }
 setcolor(0);
 editline(enemies[enemiesn].PATH[0].x -scroll_x, enemies[enemiesn].PATH[0].y -scroll_y,
					enemies[enemiesn].PATH[i].x -scroll_x, enemies[enemiesn].PATH[i].y -scroll_y);
 setcolor(14);
 editrectangle(enemies[enemiesn].PATH[i].x -2 -scroll_x, enemies[enemiesn].PATH[i].y -2 -scroll_y,
							 enemies[enemiesn].PATH[i].x +2 -scroll_x, enemies[enemiesn].PATH[i].y +2 -scroll_y);
}
void addstep()
{
 if (enemies[enemiesn].steps < (MAXSTEPS -1))
 {
	enemies[enemiesn].PATH[enemies[enemiesn].steps].x = getmousex() -1 +scroll_x;
	enemies[enemiesn].PATH[enemies[enemiesn].steps].y = getmousey() -1 +scroll_y;
	enemies[enemiesn].steps++;
 }
}
void moveit()
{
 for (int i = 0; i < enemies[enemiesn].steps; i++)
	if (inrect(getmousex(), getmousey(), enemies[enemiesn].PATH[i].x -2 -scroll_x, enemies[enemiesn].PATH[i].y -2 -scroll_y, enemies[enemiesn].PATH[i].x +2 -scroll_x, enemies[enemiesn].PATH[i].y +2 -scroll_y))
	{
	 mousewindow(1, 1, (WIN_W *TILE_W), (WIN_H *TILE_H));
	 while(leftpressed())
	 {
		copyscreen(scr, scr2);
		drawscroll();
		enemies[enemiesn].PATH[i].x = getmousex() -1 +scroll_x;
		enemies[enemiesn].PATH[i].y = getmousey() -1 +scroll_y;
		if (rightpressed()) check4scroll();
		drawall();
		drawmouse();
		drawscreen(scr);
	 }
	 break;
	}
}
void delit()
{
 for (int i = 0; i < enemies[enemiesn].steps; i++)
	if (inrect(getmousex(), getmousey(), enemies[enemiesn].PATH[i].x -2 -scroll_x, enemies[enemiesn].PATH[i].y -2 -scroll_y, enemies[enemiesn].PATH[i].x +2 -scroll_x, enemies[enemiesn].PATH[i].y +2 -scroll_y))
	{
	 enemies[enemiesn].PATH[i] = enemies[enemiesn].PATH[enemies[enemiesn].steps -1];
	 if (enemies[enemiesn].steps > 0) enemies[enemiesn].steps--;
	 break;
	}
}
void makepath()
{
 while(!keydown(28))
 {
	copyscreen(scr, scr2);
	enemies[enemiesn].x = enemies[enemiesn].PATH[0].x;
	enemies[enemiesn].y = enemies[enemiesn].PATH[0].y;
	if (leftclicked()) addstep();
	if (leftpressed()) moveit();
	if (rightclicked()) delit();
	if (rightpressed()) check4scroll();
	drawscroll();
	drawall();
	drawmouse();
	drawscreen(scr);
 }
 clearskeys();
}