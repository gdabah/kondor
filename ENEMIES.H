sprt_layers_type enemy_sprts[9];
double dist(double x1, double y1, double x2, double y2)
{
 if (tank.height < 0)	return(100000);
 return((x1 -x2) *(x1 -x2) +(y1 -y2) *(y1 -y2));
}
int get_ang(int x1, int y1, int x2, int y2)
{
 if ((x1 == x2) && (y1 == y2)) return(2304);
 return ((int)qrad(atan2(y2 -y1,
												 x2 -x1)) & 0x1ff);
}
void enemy_type::shootondist()
{
 int x = turn_speed, angdist;
 temp = get_ang(layers.x, layers.y, tank.layers.x, tank.layers.y);
 layers.ang &= 0x1ff;
 angdist = abs(layers.ang -temp);
 if (temp > layers.ang) x = turn_speed;
	else x = -turn_speed;
 if (angdist < 256) x *= -1;
 if (angdist < turn_speed)
 {
	layers.ang = temp & 0x1ff;
	if (random(100) < 2)
	 bullets.add(layers.x +COS(layers.ang) *((layers.sprts[0].w >> 1) +5),
							 layers.y +SIN(layers.ang) *((layers.sprts[0].w >> 1) +5),
							 layers.ang, BULLETSPD, ENEMY, 0);
 }
 else	layers.ang -= x;
}
void enemy_type::smartmove(int me) // Actaully stupid
{
 int res;
 if (moveable)
 {
	layers.ang = temp2 & 0x1ff;
	layers.x += COS(layers.ang) *speed;
	layers.y += SIN(layers.ang) *speed;
 }
 res = enemies.checkvehiclehit(layers.x, layers.y, layers.ang, Alpha, Radius, me);
 if (res && enemies.data[res -1].behavior != TURRET)
 {
	layers.x -= COS(layers.ang) *speed;
	layers.y -= SIN(layers.ang) *speed;
	if (((enemies.data[res -1].behavior == FOLLOW ||
				enemies.data[res -1].behavior == RANDOM) &&
				!notmyfault) ||
				enemies.data[res -1].behavior == CIRCLE)
	{
	 if (dist(enemies.data[res -1].layers.x, enemies.data[res -1].layers.y,
						tank.layers.x, tank.layers.y) > ESHOOTRANGE)
	 {
		moveable = 0;
		enemies.data[res -1].notmyfault = 1;
	 }
	 else
	 {
		notmyfault = 0;
		cur_point = 0;
		findtheway((int)layers.x >> 4, (int)layers.y >> 4,
							 ((int)layers.x >> 4) +(random(10) -5),
							 ((int)layers.y >> 4) +(random(10) -5),
							 path, &path_len);
		temp2 = get_ang(layers.x, layers.y, path[0].x, path[0].y) & 0x1ff;
	 }
	}
	else
	{
	 notmyfault = 0;
	 cur_point = 0;
	 findtheway((int)layers.x >> 4, (int)layers.y >> 4,
							((int)layers.x >> 4) +(random(10) -5),
							((int)layers.y >> 4) +(random(10) -5),
							path, &path_len);
	 temp2 = get_ang(layers.x, layers.y, path[0].x, path[0].y) & 0x1ff;
	}
 }
 else
 {
	moveable = 1;
	notmyfault = 0;
 }
}
void enemy_type::move(int me)
{
 int x = 0, angdist;
 //TURRET, CIRCLE, RANDOM, PATH_FIND, FOLLOW.
 if (behavior == EMPTY) return;
 if (behavior == TURRET)
	if (dist(layers.x, layers.y, tank.layers.x, tank.layers.y) <= TSHOOTRANGE)
	{
	 int x = turn_speed;
	 temp = get_ang(layers.x, layers.y, tank.layers.x, tank.layers.y);
	 layers.sprts[1].ang &= 0x1ff;
	 angdist = abs(layers.sprts[1].ang -temp);
	 if (temp > layers.sprts[1].ang) x = turn_speed;
		else x = -turn_speed;
	 if (angdist < 256) x *= -1;
	 if (angdist < turn_speed)
	 {
		layers.sprts[1].ang = temp & 0x1ff;
		if (random(100) < 2)
		 bullets.add(layers.x +COS(layers.sprts[1].ang) *((layers.sprts[0].w >> 1) +5),
								 layers.y +SIN(layers.sprts[1].ang) *((layers.sprts[0].w >> 1) +5),
								 layers.sprts[1].ang, BULLETSPD, ENEMY, 0);
	 }
	 else	layers.sprts[1].ang -= x;
	}
 if (behavior == CIRCLE)
 {
	if (dist(layers.x, layers.y, tank.layers.x, tank.layers.y) <= ESHOOTRANGE) shootondist();
	else
	{
	 layers.ang &= 0x1ff;
	 if (layers.ang > temp2) x = turn_speed;
	 if (layers.ang < temp2) x = -turn_speed;
	 angdist = abs(layers.ang -temp2);
	 if (angdist < 256) x *= -1;
	 if (angdist < turn_speed)
	 {
		layers.ang = temp2 & 0x1ff;
		layers.x += COS(layers.ang) *speed;
		layers.y += SIN(layers.ang) *speed;
		layers.ang += turn_speed *dir;
		temp2 = layers.ang & 0x1ff;
		if (enemies.checkvehiclehit(layers.x, layers.y, layers.ang, Alpha, Radius, me))
		{
		 layers.x -= COS(layers.ang) *speed;
		 layers.y -= SIN(layers.ang) *speed;
		 layers.ang -= turn_speed *dir;
		 dir *= -1;
		 temp2 = (temp2 +256) & 0x1ff;
		}
	 }
	 else layers.ang += x;
	}
 }

 if (behavior == FOLLOW)
 {
	if ((dist(layers.x, layers.y, tank.layers.x, tank.layers.y) <= ESHOOTRANGE) && (mode == 0)) shootondist();
	else
	{
	 if (!path_len || cur_point >= path_len)
	 {
		cur_point = 0;
		findtheway((int)layers.x >> 4, (int)layers.y >> 4,
							 (int)tank.layers.x >> 4, (int)tank.layers.y >> 4,
							 path, &path_len);
		if (!path_len)
		{
		 findtheway((int)layers.x >> 4, (int)layers.y >> 4,
								((int)layers.x >> 4) +(random(10) -5),
								((int)layers.y >> 4) +(random(10) -5),
								path, &path_len);
		}
		temp2 = get_ang(layers.x, layers.y, path[0].x, path[0].y) & 0x1ff;
	 }
	 else
	 {
		if (inrect(layers.x, layers.y,
							 path[cur_point].x -doublespeed, path[cur_point].y -doublespeed,
							 path[cur_point].x +doublespeed, path[cur_point].y +doublespeed))
		{
		 if (mode == 1)
		 {
			mode = 0;
			layers.x = ((int)layers.x & 0xfff0) +8; // 8=TILEW/2
			layers.y = ((int)layers.y & 0xfff0) +8;
		 }
		 else
		 {
			layers.x = path[cur_point].x;
			layers.y = path[cur_point].y;
		 }
		 cur_point++;
		 if (cur_point < path_len)
			temp2 = get_ang(layers.x, layers.y, path[cur_point].x, path[cur_point].y) & 0x1ff;
		}
		else
		{
		 angdist = abs(layers.ang -temp2);
		 if (angdist > turn_speed)
		 {
			if (layers.ang > temp2) x = turn_speed;
			if (layers.ang < temp2) x = -turn_speed;
			if (angdist < 256) x *= -1;
			layers.ang += x;
			layers.ang &= 0x1ff;
		 }
		 else smartmove(me);
		}
	 }
	}
	layers.ang &= 0x1ff;
	temp2 &= 0x1ff;
 }
 if (behavior == RANDOM)
 {
	double range = dist(layers.x, layers.y, tank.layers.x, tank.layers.y);
	if ((range <= ESHOOTRANGE) && (mode == 0)) shootondist();
	else
	{
	 if ((range <= EHUNTRANGE) && (mode == 0))
	 {
		cur_point = 0;
		findtheway((int)layers.x >> 4, (int)layers.y >> 4,
							 (int)tank.layers.x >> 4, (int)tank.layers.y >> 4,
							 path, &path_len);
		temp2 = get_ang(layers.x, layers.y, path[0].x, path[0].y);
	 }
	 if (!path_len || cur_point >= path_len)
	 {
		cur_point = 0;
		findtheway((int)layers.x >> 4, (int)layers.y >> 4,
							 random(MAP_W), random(MAP_H),
							 path, &path_len);
		if (!path_len)
		 findtheway((int)layers.x >> 4, (int)layers.y >> 4,
								((int)layers.x >> 4) + (random(10) - 5),
								((int)layers.y >> 4) + (random(10) - 5),
								path, &path_len);
		temp2 = get_ang(layers.x, layers.y, path[0].x, path[0].y);
	 }
	 else
	 {
		if (inrect(layers.x, layers.y,
							 path[cur_point].x -doublespeed, path[cur_point].y -doublespeed,
							 path[cur_point].x +doublespeed, path[cur_point].y +doublespeed))
		{
		 if (mode == 1)
		 {
			mode = 0;
			layers.x = ((int)layers.x & 0xfff0) + 8; // 8=TILEW/2
			layers.y = ((int)layers.y & 0xfff0) + 8;
		 }
		 else
		 {
			layers.x = path[cur_point].x;
			layers.y = path[cur_point].y;
		 }
		 cur_point++;
		 if (cur_point < path_len)
			temp2 = get_ang(layers.x, layers.y, path[cur_point].x, path[cur_point].y);
		}
		else
		{
		 angdist = abs(layers.ang -temp2);
		 if (angdist > turn_speed)
		 {
			if (layers.ang > temp2) x = turn_speed;
			if (layers.ang < temp2) x = -turn_speed;
			if (angdist < 256) x *= -1;
			layers.ang += x;
			layers.ang &= 0x1ff;
		 }
		 else smartmove(me);
		}
	 }
	}
	layers.ang &= 0x1ff;
	temp2 &= 0x1ff;
 }

 if (behavior == PATH_FIND)
 {
	if (dist(layers.x, layers.y, tank.layers.x, tank.layers.y) <= ESHOOTRANGE) shootondist();
	else
	{
	 temp2 = get_ang(layers.x, layers.y, path[cur_point].x, path[cur_point].y) & 0x1ff;
	 if (inrect(layers.x, layers.y, path[cur_point].x -doublespeed, path[cur_point].y -doublespeed, path[cur_point].x +doublespeed, path[cur_point].y +doublespeed))
	 {
		layers.x = path[cur_point].x;
		layers.y = path[cur_point].y;
		cur_point++;
		if (cur_point >= path_len) cur_point = 0;
		temp2 = get_ang(layers.x, layers.y, path[cur_point].x, path[cur_point].y) & 0x1ff;
	 }
	 layers.ang &= 0x1ff;
	 if (layers.ang > temp2) x = turn_speed;
	 if (layers.ang < temp2) x = -turn_speed;
	 angdist = abs(layers.ang -temp2);
	 if (angdist < 256) x *= -1;
	 if (angdist < turn_speed)
	 {
		layers.ang = temp2 & 0x1ff;
		layers.x += COS(layers.ang) *speed;
		layers.y += SIN(layers.ang) *speed;
	 }
	 else layers.ang += x;
	}
 }
 if (layers.x < 0 || layers.y < 0 ||
		 layers.x > MAP_PIXEL_W || layers.y > MAP_PIXEL_H) power = 0;
}
void enemy_type::handle(int me)
{
 if (layers.x >= 1 && layers.y >= 1 &&
		 layers.x < MAP_PIXEL_W -1 && layers.y < MAP_PIXEL_H -1)
	clearminmap(layers.x, layers.y);
 move(me);
 if (layers.x >= 1 && layers.y >= 1 &&
		 layers.x < MAP_PIXEL_W -1 && layers.y < MAP_PIXEL_H -1)
	drawonminmap(layers.x, layers.y, 72, 0);
 int res = bullets.checkvehiclehit(layers.x, layers.y, layers.ang, Alpha, Radius, ENEMY);
 switch (res)
 {
	case 1: power -= BULLETDAMAGE; break;
	case 2: power -= ROCKETDAMAGE; break;
 }
}
void enemy_type::drawpowerbar()
{
 setcolor(0);
 int layersy = layers.y +size2 -scroll_y,
		 layersx = layers.x -size2 -scroll_x,
		 layersx2 = layers.x +EPOWERBARSIZE -scroll_x -size2,
		 layersx3 = layers.x +((float)power /power2) *EPOWERBARSIZE -scroll_x -size2;
 khorline(layersy -1,
					layersx, layersx2);
 khorline(layersy +2,
				 layersx, layersx2);
 kverline(layersx -1,
					layersy,
					layersy +1);
 kverline(layersx2 +1,
					layersy,
					layersy +1);
 setcolor(4);
 khorline(layersy,
					layersx, layersx2);
 khorline(layersy +1,
					layersx, layersx2);
 setcolor(80);
 khorline(layersy,
					layersx, layersx3);
 khorline(layersy +1,
					layersx, layersx3);
}
void enemy_type::draw()
{
 if (((layers.x -scroll_x) > -size) && ((layers.x -scroll_x) < (SCREEN_W +size)) &&
		 ((layers.y -scroll_y) > -size) && ((layers.y -scroll_y) < (SCREEN_H +size)))
		 {
			if (showpb) drawpowerbar();
			layers.draw();
		 }
}
int enemy_type::dead()
{
 return(power <= 0);
}
int enemies_type::checkvehiclehit(int x, int y, int ang, int Alpha, double Radius, int me = -1)
{
 for(int e_index = 0; e_index < enemies_no; e_index++)
	if (e_index != me)
	 if	(krotinrot(x, y, ang,
								 data[e_index].layers.x,
								 data[e_index].layers.y,
								 data[e_index].layers.ang,
								 Alpha, Radius,
								 data[e_index].Alpha, data[e_index].Radius))
								 {
									if (me == -1) data[e_index].power -= (int)abs(tank.speed);
									return(e_index +1);
								 }
 return(0);
}
void enemies_type::handle()
{
 for (int e_index = 0; e_index < enemies_no; e_index++)
 {
	data[e_index].handle(e_index);
	if (data[e_index].dead())
	{
	 current_scores.scores += data[e_index].power2 *SCORE_ON_ENEMY;
	 current_scores.enemies++;
	 expls.add(data[e_index].layers.x, data[e_index].layers.y, EXPL_LENGTH, 1);
	 MixVoice(&VoiceData[4]);
	 enemies_no--;
	 clearminmap(data[e_index].layers.x, data[e_index].layers.y);
	 data[e_index] = data[enemies_no];
	 e_index--;
	}
 }
}
void enemies_type::draw()
{
 for(int e_index = 0; e_index < enemies_no; e_index++)
 {
	if (data[e_index].dead())
	{
	 sound(1000);
	 delay(500);
	 nosound();
	}
	data[e_index].draw();
 }
}
void enemies_type::add(double x, double y, int ang,
											 double speed, double turn_speed,
											 unsigned int power, int path_len,
											 enemytag behav, int mode = 0)
{
 if (enemies_no < MAX_ENEMIES)
 {
	data[enemies_no].layers.close();
	data[enemies_no].layers.set(x, y, ang, enemy_sprts[behav].sprts_no);
	for(int li = 0; li < enemy_sprts[behav].sprts_no; li++)
	 data[enemies_no].layers.sprts[li].set(0, 0,
																				 enemy_sprts[behav].sprts[li].cx,
																				 enemy_sprts[behav].sprts[li].cy,
																				 enemy_sprts[behav].sprts[li].ang,
																				 enemy_sprts[behav].sprts[li].w,
																				 enemy_sprts[behav].sprts[li].h,
																				 enemy_sprts[behav].sprts[li].data,
																				 true);
	data[enemies_no].mode = mode;
	data[enemies_no].speed = speed;
	data[enemies_no].turn_speed = turn_speed;
	data[enemies_no].power = power;
	data[enemies_no].power2 = power;
	data[enemies_no].doublespeed = speed *2;
	if (data[enemies_no].layers.sprts[0].w > data[enemies_no].layers.sprts[0].h)
		 data[enemies_no].size = data[enemies_no].layers.sprts[0].w;
	 else data[enemies_no].size = data[enemies_no].layers.sprts[0].h;
	data[enemies_no].size2 = data[enemies_no].size >> 1;
	data[enemies_no].path_len = path_len;
	data[enemies_no].cur_point = 0;
	data[enemies_no].behavior = behav;
	data[enemies_no].notmyfault = 0;
	data[enemies_no].dir = 1;
	data[enemies_no].temp = ang;
	data[enemies_no].temp2 = ang;
	data[enemies_no].Alpha = qrad(atan2(-(data[enemies_no].layers.sprts[0].h >> 1), (data[enemies_no].layers.sprts[0].w >> 1)));
	data[enemies_no].Radius = sqrt(0.25 *(data[enemies_no].layers.sprts[0].w *data[enemies_no].layers.sprts[0].w +
																			 (data[enemies_no].layers.sprts[0].h *data[enemies_no].layers.sprts[0].h)));
	if (data[enemies_no].behavior == TURRET)
	{
	 data[enemies_no].layers.sprts[1].ang = data[enemies_no].layers.ang;
	 data[enemies_no].layers.ang = 0;
	}
	if (behav == PATH_FIND)
	{
	 data[enemies_no].layers.ang = get_ang(x, y,
																				 data[enemies_no].path[1].x, data[enemies_no].path[1].y);
	 data[enemies_no].cur_point = 1;
	}
	enemies_no++;
 }
}
void enemies_type::close()
{
 enemies_no = 0;
}
enemies_type::enemies_type()
{
 enemies_no = 0;
}
void init_enemy_sprts()
{
 enemy_sprts[1].set(0, 0, 0, 2);
 enemy_sprts[1].sprts[0].set(0, 0, (turpadw >> 1) +1, (turpadh >> 1) +1, 0, turpadw, turpadh, turpad_img, true);
 enemy_sprts[1].sprts[1].set(0, 0, 5, (turcanh >> 1) +1, 0, turcanw, turcanh, turcan_img, true);

 enemy_sprts[2].set(0, 0, 0, 1);
 enemy_sprts[2].sprts[0].set(0, 0, 10, 9, 0, 20, 17, enemy_sprt, true);
 enemy_sprts[3].set(0, 0, 0, 1);
 enemy_sprts[3].sprts[0].set(0, 0, 10, 9, 0, 20, 17, enemy_sprt, true);
 enemy_sprts[4].set(0, 0, 0, 1);
 enemy_sprts[4].sprts[0].set(0, 0, 10, 9, 0, 20, 17, enemy_sprt, true);
 enemy_sprts[5].set(0, 0, 0, 1);
 enemy_sprts[5].sprts[0].set(0, 0, 10, 9, 0, 20, 17, enemy_sprt, true);
 enemy_sprts[6].set(0, 0, 0, 1);
 enemy_sprts[6].sprts[0].set(0, 0, 10, 9, 0, 20, 17, enemy_sprt, true);

 enemy_sprts[7].set(0, 0, 0, 1);
 enemy_sprts[7].sprts[0].set(0, 0, (flyw >> 1) +1, (flyh >> 1) +1, 0, flyw, flyh, fly_img, true);
 enemy_sprts[8].set(0, 0, 0, 1);
 enemy_sprts[8].sprts[0].set(0, 0, (migw >> 1) +1, (migh >> 1) +1, 0, migw, migh, mig_img, true);
}
void close_enemy_sprts()
{
 for(int si = 0; si < 7; si ++)
	enemy_sprts[si].close();
}