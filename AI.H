//This header will handle the ai of the enemies.
#define MAX_STEPS_AI 500
unsigned char step;
unsigned char *dirmap;
pointtypei *PList[2];
void findtheway(int sx, int sy, int tx, int ty, pointtypei *path, int *steps_no)
{
 memset(dirmap, 0, MAP_W *MAP_H);
 if (waterxy(sx, sy)
 || waterxy(tx, ty)
 || minblockingxy(sx, sy)
 || minblockingxy(tx, ty))
 {
	*steps_no = 0;
	return;
 }
 pointtypei newpos, Shpos;
 unsigned char dir, InL, OutL;
 int PCnt[2];
 boolean goalreached = false;
 PCnt[0] = 1;
 PCnt[1] = 0;
 PList[0][0].x = tx;
 PList[0][0].y = ty;
 OutL = 0;
 InL = 1;
 newpos.x = tx;
 newpos.y = ty;
 step = 1;
 do{
	step++;
	PCnt[InL] = 0;
	for (int ai = 0; ai < PCnt[OutL]; ai++)
	{
	 newpos = PList[OutL][ai];
	 dir = 2;
	 newpos.y--;
	 for (int bi = 0; bi < 7; bi++)
	 {
		if ((!dirmap[(newpos.y << 6) +(newpos.y << 5) +newpos.x]) && (!minblockingxy(newpos.x, newpos.y)) && (!waterxy(newpos.x, newpos.y)) && (newpos.x >= 0) && (newpos.y >= 0) && (newpos.x < MAP_W) && (newpos.y < MAP_H))
		{
		 dirmap[(newpos.y << 6) +(newpos.y << 5) +newpos.x] = dir;
		 PList[InL][PCnt[InL]] = newpos;
		 PCnt[InL]++;
		}
		if ((newpos.x == sx) && (newpos.y == sy))
		{
		 boolean dirput = true;
		 step = 0;
		 newpos.x = sx;
		 newpos.y = sy;
		 while ((newpos.x != tx) || (newpos.y != ty))
		 {
			if (dir == dirmap[newpos.x +(newpos.y << 6) +(newpos.y << 5)]) dirput = false;
			else dirput = true;
			dir = dirmap[newpos.x +(newpos.y << 6) +(newpos.y << 5)];
			if (dirput)
			{
			 path[step].x = (newpos.x << 4) +8;   //8=TILE_W/2
			 path[step].y = (newpos.y << 4) +8;
			 step++;
			}
			switch(dir)
			{
			 case 3 :  newpos.x++;     newpos.y++; break;
			 case 2 :                  newpos.y++; break;
			 case 6 :  newpos.x--;     newpos.y++; break;
			 case 4 :  newpos.x--;                 break;
			 case 12 : newpos.x--;     newpos.y--; break;
			 case 8 :                  newpos.y--; break;
			 case 9 :  newpos.x++;     newpos.y--; break;
			 case 1 :  newpos.x++;                 break;
			}
		 }
		 path[step].x = (newpos.x << 4) +8;   //8=TILE_W/2
		 path[step].y = (newpos.y << 4) +8;
		 step++;
		 *steps_no = step;
		 return;
		}
		switch(dir)
		{
		 case 3 :  newpos.x += 2;                  dir = 6; break;
		 case	2 :  newpos.x++;    newpos.y++;      dir = 4; break;
		 case	6 :                 newpos.y += 2;   dir = 12; break;
		 case	4 :  newpos.x--;    newpos.y++;      dir = 8; break;
		 case 12 : newpos.x -= 2;                  dir = 9; break;
		 case	8 :  newpos.x--;    newpos.y--;      dir = 1; break;
		 case	9 :  newpos.x++;    newpos.y -= 2;   dir = 2; break;
		 case	1 :                 newpos.y--;      dir = 3; break;
		}
	 }
	}
	OutL = !OutL;
	InL = !InL;
 }while ((!goalreached) && (PCnt[OutL]!=0));
 *steps_no = 0;
}
void init_ai()
{
 if ((dirmap = (unsigned char *)malloc(MAP_W *MAP_H)) == NULL) memerr("AI'S Map[1]");
 memset(dirmap, 0, MAP_W *MAP_H);
 if ((PList[0] = (pointtypei *)malloc(MAX_STEPS_AI *sizeof(pointtypei))) == NULL) memerr("AI'S Map[2]");
 if ((PList[1] = (pointtypei *)malloc(MAX_STEPS_AI *sizeof(pointtypei))) == NULL) memerr("AI'S Map[3]");
 if ((!PList[0]) || (!PList[1])) memerr("AI'S Map[4]");
}
void close_ai()
{
 free(dirmap);
 free(PList[0]);
 free(PList[1]);
}