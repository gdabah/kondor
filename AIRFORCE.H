// This header handles PIPERS and MIGS...
void air_enemy_type::targetondist()
{
 if (!mode2)
 {
	tempx = path[cur_point].x +400;
	tempy = path[cur_point].y +400;
	mode2 = 1;
 }
 int x, angdist;
 sprt.ang &= 0x1ff;
 temp2 = get_ang(sprt.x, sprt.y, tank.layers.x, tank.layers.y);
 x = turn_speed;
 angdist = abs(temp2 -sprt.ang);
 if (temp2 > sprt.ang) x = turn_speed;
	else x = -turn_speed;
 if (angdist < 0x100) x *= -1;
 if (angdist < turn_speed) sprt.ang = temp2 & 0x1ff;
 else sprt.ang -= x;
 if (!temp--)
 {
	mode *= -1;
	temp = random(32) +32;
 }
 sprt.x += COS(sprt.ang +mode) *0.5;
 sprt.y += SIN(sprt.ang +mode) *0.5;
 if (random(100) < 2)
	bullets.add(sprt.x +COS(sprt.ang) *(halfwidth +5),
							sprt.y +SIN(sprt.ang) *(halfwidth +5),
							sprt.ang, speed +5, AIRENEMY, 0);
}
void air_enemy_type::move()
{
 int x = 0, angdist, tx, ty;
 if (behavior == EMPTY) return;
 if (behavior == PIPER)
 {
	double range = dist(sprt.x, sprt.y, tank.layers.x, tank.layers.y);
	if (mode == 0)
	{
	 temp2 = get_ang(sprt.x, sprt.y, tank.layers.x, tank.layers.y) & 0x1ff;
	 if (range < FLYTOOCLOSE)
	 {
		mode = 1;
		temp = random(512);
		tempx = tank.layers.x +COS(temp) *(150 +random(300));
		tempy = tank.layers.y +SIN(temp) *(150 +random(300));
	 }
	}
	if (mode == 1)
	{
	 temp2 = get_ang(sprt.x, sprt.y, tempx, tempy) & 0x1ff;
	 if (dist(sprt.x, sprt.y, tempx, tempy) < FLYTOOCLOSE) mode = 0;
	}
	sprt.ang &= 0x1ff;
	temp2 &= 0x1ff;
	x = turn_speed;
	angdist = abs(temp2 -sprt.ang);
	if (angdist < turn_speed)
	{
	 sprt.ang = temp2 & 0x1ff;
	}
	else
	{
	 if (temp2 > sprt.ang) x = turn_speed;
		else x = -turn_speed;
	 if (angdist < 0x100) x *= -1;
	 sprt.ang -= x;
	}
	sprt.x += COS(sprt.ang) *speed;
	sprt.y += SIN(sprt.ang) *speed;
	if (mode == 0)
	 if ((range < ESHOOTRANGE) && (range > FLYTOOCLOSE))
		if (random(100) < 5)
		 bullets.add(sprt.x +COS(sprt.ang) *(halfwidth +5),
								 sprt.y +SIN(sprt.ang) *(halfwidth +5),
								 sprt.ang, speed +5, AIRENEMY, 0);
 }

 if (behavior == MIG)
 {
	if ((dist(sprt.x, sprt.y, tank.layers.x, tank.layers.y) <= MSHOOTRANGE)) targetondist();
	else
	{
	 if (mode2) {tx = tempx; ty = tempy; }
	 else {tx = path[cur_point].x; ty = path[cur_point].y; }
	 if (inrect(sprt.x, sprt.y, tx -speed2, ty -speed2, tx +speed2, ty +speed2))
	 {
		sprt.x = tx;
		sprt.y = ty;
		if (mode2) mode2 = 0;
		else
		{
		 cur_point++;
		 if (cur_point >= path_len) cur_point = 0;
		}
	 }
	 temp2 = get_ang(sprt.x, sprt.y, tx, ty);
	 sprt.ang &= 0x1ff;
	 angdist = abs(temp2 -sprt.ang);
	 if (angdist < turn_speed) sprt.ang = temp2;
	 else
	 {
		if (temp2 > sprt.ang) x = turn_speed;
		else x = -turn_speed;
		if (angdist < 0x100) x *= -1;
		sprt.ang -= x;
	 }
	 sprt.x += COS(sprt.ang) *speed;
	 sprt.y += SIN(sprt.ang) *speed;
	}
 }
}
void air_enemy_type::handle()
{
 if ((sprt.x >= 1) && (sprt.y >= 1) &&
		 (sprt.x < MAP_PIXEL_W -1) && (sprt.y < MAP_PIXEL_H -1))
	clearminmap(sprt.x, sprt.y);
 move();
 if ((sprt.x >= 1) && (sprt.y >= 1) &&
		 (sprt.x < MAP_PIXEL_W -1) && (sprt.y < MAP_PIXEL_H -1))
	drawonminmap(sprt.x, sprt.y, 72, 0);
 int res = bullets.checkvehiclehit(sprt.x, sprt.y, sprt.ang, Alpha, Radius, ENEMY);
 switch (res)
 {
	case 1: power -= BULLETDAMAGE; break;
	case 2: power -= ROCKETDAMAGE; break;
 }
}
void air_enemy_type::draw()
{
 if (((sprt.x -scroll_x) > -size) && ((sprt.x -scroll_x) < (SCREEN_W +size)) &&
		 ((sprt.y -scroll_y) > -size) && ((sprt.y -scroll_y) < (SCREEN_H +size)))
		 {
			drawsink(sprt.x -scroll_x +5, sprt.y -scroll_y +5, sprt.cx, sprt.cy, sprt.ang, sprt.w, sprt.h, sprt.data, halfwidth, halfheight, halfwidth, halfheight);
			sprt.draw(-scroll_x, -scroll_y);
		 }
}
int air_enemy_type::dead()
{
 return(power <= 0);
}
void air_enemies_type::handle()
{
 for (int e_index = 0; e_index < enemies_no; e_index++)
 {
	data[e_index].handle();
	if (data[e_index].dead())
	{
	 expls.add(data[e_index].sprt.x, data[e_index].sprt.y, EXPL_LENGTH, 1);
	 MixVoice(&VoiceData[4]);
	 enemies_no--;
	 clearminmap(data[e_index].sprt.x, data[e_index].sprt.y);
	 data[e_index] = data[enemies_no];
	 e_index--;
	}
 }
}
void air_enemies_type::draw()
{
 for(int e_index = 0; e_index < enemies_no; e_index++)
	data[e_index].draw();
}
void air_enemies_type::add(double x, double y, int ang,
													 double speed, double turn_speed,
													 unsigned int power, int path_len,
													 enemytag behav)
{
 if (enemies_no < MAX_AIR_ENEMIES)
 {
	data[enemies_no].sprt.set(x,
														y,
														enemy_sprts[behav].sprts[0].cx,
														enemy_sprts[behav].sprts[0].cy,
														ang,
														enemy_sprts[behav].sprts[0].w,
														enemy_sprts[behav].sprts[0].h,
														enemy_sprts[behav].sprts[0].data,
														true);

	data[enemies_no].cur_point = 0;
	data[enemies_no].path_len = path_len;
	data[enemies_no].speed = speed;
	data[enemies_no].turn_speed = turn_speed;
	data[enemies_no].power = power;
	data[enemies_no].speed2 = speed *2;
	data[enemies_no].halfwidth = (data[enemies_no].sprt.w >> 1);
	data[enemies_no].halfheight = (data[enemies_no].sprt.h >> 1);
	if (data[enemies_no].sprt.w > data[enemies_no].sprt.h)
		 data[enemies_no].size = data[enemies_no].sprt.w;
	 else data[enemies_no].size = data[enemies_no].sprt.h;
	data[enemies_no].behavior = behav;
	data[enemies_no].Alpha = qrad(atan2(-(data[enemies_no].sprt.h >> 1), (data[enemies_no].sprt.w >> 1)));
	data[enemies_no].Radius = sqrt(0.25 *(data[enemies_no].sprt.w *data[enemies_no].sprt.w +
																			 (data[enemies_no].sprt.h *data[enemies_no].sprt.h)));
	if (behav == MIG)
	{
	 data[enemies_no].sprt.ang = get_ang(x, y,
																			 data[enemies_no].path[1].x, data[enemies_no].path[1].y);
	 data[enemies_no].cur_point = 1;
	 data[enemies_no].mode = 0x80;
	 data[enemies_no].mode2 = 0;
	 data[enemies_no].temp = random(32) +32;
	}
	else
	{
	 data[enemies_no].mode = 0;
	}
	enemies_no++;
 }
}
void air_enemies_type::close()
{
 enemies_no = 0;
}
air_enemies_type::air_enemies_type()
{
 enemies_no = 0;
}