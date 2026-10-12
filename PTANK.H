void tank_type::draw()
{
 if (height <= -1)
 {
	drawsink(layers.x -scroll_x, layers.y -scroll_y, layers.sprts[0].cx, layers.sprts[0].cy, layers.ang, layers.sprts[0].w, layers.sprts[0].h, layers.sprts[0].data, -height, -height, -height, -height);
	drawsink(tank.layers.x -scroll_x, tank.layers.y -scroll_y, tank.layers.sprts[1].cx, tank.layers.sprts[1].cy, tank.layers.ang +tank.layers.sprts[1].ang, tank.layers.sprts[1].w, tank.layers.sprts[1].h, tank.layers.sprts[1].data, 0, -(tank.height +2), -(tank.height +9), -(tank.height +9));
 }
 else layers.draw();
 if (shieldhits)
 {
	setcolor(4);
	circle(layers.x -scroll_x, layers.y -scroll_y, (int)shieldrad);
	if (shieldrad < SHIELD_MAX_RAD) shieldrad += SHIELD_RAD_RATE;
 }
 else if (shieldrad > 0)
 {
	setcolor(4);
	circle(layers.x -scroll_x, layers.y -scroll_y, (int)shieldrad);
	shieldrad -= SHIELD_RAD_RATE;
 }
 if (poweractivated)
	if (powericon) kdrawsprite(layers.x -scroll_x -8, layers.y -scroll_y -8, 16, 15, skey_img);
}
void tank_type::hit(unsigned int damage)
{
 if (damage > power) power = 0;
 else
 {
	if ((shieldrad > Radius) && (shieldhits)) shieldhits--;
	else power -= damage;
 }
 screenis(bkg);
 setcolor(0);
 bar(263 +(tank.power /204), 131, 312, 134);
 setcolor(45);
 bar(263, 131, 263 +(tank.power /204), 134);
 screenis(buffer);
}
void tank_type::isdead()
{
 if ((power <= 0) || (power > TANK_MAX_POWER))
 {
	lives--;
	if (!lives)
	{
	 gameloop = 1;
	 resumegame = false;
	 optionmenu = start;
	 screenis(video_buffer);
	 drawsprite(160 -(gameoverw >> 1), 100 -(gameoverh >> 1), gameoverw, gameoverh, gameover_s);
	 delay(3500);
	 screenis(buffer);
	 fadeout();
	 clearscreen();
	 clearskeys();
	 int hscresult = getscoreplace();
	 if (hscresult >= 0) enterhsc(hscresult);
	}
	else
	{
	 //You just died.
	 fadeout();
	 loadmap();
	 load_side_bar();
	 drawNhandle();
	 fadein(gamepal);
	}
 }
}
int checksink()
{
 int x = (int)tank.layers.x >> 4,
		 y = (int)tank.layers.y >> 4;
 int r;
 for(int ix = x -1; ix <= (x +1); ix++)
	for(int iy = y -1; iy <= (y +1); iy++)
	{
	 if (krectinrot(ix << 4, iy << 4, (ix +1) << 4, (iy +1) << 4,
									tank.layers.x, tank.layers.y, tank.layers.ang, tank.Alpha, tank.Radius))
		if (!waterxy(ix, iy)) return (0);
	}
 return(1);
}

void tank_type::handle()
{
 if ((heightspeed <= 0) && (checksink()))
 {
	if (height == -0.25) if (!isplaying(&VoiceData[5])) MixVoice(&VoiceData[5]);
	heightspeed = -0.25;
	speed -= 0.18 *speed;
 }
 if (((height <= -(layers.sprts[0].w << 2)) && (heightspeed < 0)) ||
		((height >= 0) && (heightspeed > 0))) heightspeed = 0;
 height += heightspeed;
 clearminmap(layers.x, layers.y);
 int ang = layers.ang;
 double x = layers.x, y = layers.y;
 if (keydown(arrowright)) tank.turn(turn_speed);
 if (keydown(arrowleft)) tank.turn(-turn_speed);
 move();
 if (enemies.checkvehiclehit(layers.x, layers.y, layers.ang, Alpha, Radius))
 {
	layers.x = x;
	layers.y = y;
	layers.ang = ang;
	layers.x -= COS(layers.ang) *speed;
	layers.y -= SIN(layers.ang) *speed;
	speed *= -0.4;
	if ((speed <= -HIT_SPEED) || (speed >= HIT_SPEED))
	{
	 hit(abs(speed *5));
	 expls.add(cur_coll.x, cur_coll.y, EXPL_LENGTH, 0);
	}
 }
 if (shieldrad > Radius)
 {
	if (bullets.checkcirclehit(layers.x, layers.y, shieldrad *shieldrad, PLAYER))
	{
	 hit(200);
	 isdead();
	}
 }
 else
	if (bullets.checkvehiclehit(layers.x, layers.y,
															layers.ang,
															Alpha, Radius,
															PLAYER))
	{
	 hit(200);
	 isdead();
 }
 int type = objects.checkvehiclehit(layers.x, layers.y,
																		layers.ang,
																		Alpha, Radius);
 if (type != -1)
 {
	MixVoice(&VoiceData[9]);
	if (type == 3) lives += random(MAX_LIVE) +1;
	else slots.add(type);
 }
 if (bases.checkvehiclehit(layers.x, layers.y,
													 layers.ang,
													 Alpha, Radius))
 {
	layers.x = x;
	layers.y = y;
	layers.ang = ang;
	layers.x -= COS(layers.ang) *speed;
	layers.y -= SIN(layers.ang) *speed;
	speed *= -0.4;
	hit(abs(speed *2));
 }
 drawonminmap(layers.x, layers.y, 11, 11);
}
int tank_type::moveable(int x, int y)
{
 if (height < 0) return(waterxy(x, y));
 return (!blockingxy(x, y));
}
int tank_type::checkhit()
{
 int x = (int)layers.x >> 4,
		 y = (int)layers.y >> 4;
 int r;
 for(int ix = x -1; ix <= (x +1); ix++)
	for(int iy = y -1; iy <= (y +1); iy++)
	{
	 if (!moveable(ix, iy))
	 {
		if ((r = krectinrot(ix << 4, iy << 4, (ix +1) << 4, (iy +1) << 4,
									 layers.x, layers.y, layers.ang, Alpha, Radius)) != 0)
		{
		 if (height < 0 && map[(iy << 6) +(iy << 5) +ix] < 101)
			heightspeed = 0.5;
		 return(r);
		}
	 }
	}
 return(0);
}
void tank_type::turn(int direction)
{
 layers.ang += direction;
 if (checkhit()) layers.ang -= direction;
 tank.layers.ang &= 0x1ff;
}
void tank_type::move()
{
 float s = speed;
 tank.layers.ang &= 0x1ff;
 layers.x += COS(layers.ang) *s;
 layers.y += SIN(layers.ang) *s;
 if (checkhit())
 {
	layers.x -= COS(layers.ang) *s;
	layers.y -= SIN(layers.ang) *s;
	if (height >= 0) speed *= -0.04;
	//if (height > 0)
	//if (!isplaying(&VoiceData[7])) MixVoice(&VoiceData[7]);
 }
}
void tank_type::turn_cannon(int direction)
{
 layers.sprts[1].ang += direction;
 tank.layers.ang &= 0x1ff;
}