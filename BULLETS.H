boolean canshoot = true;
int bullet_max_age = 35;
class bullet_type
{
 public:
	double speed;
	int Alpha, Radius;
	owner_type owner;
	int type;
	sprite_type sprt;
	unsigned int age;
	boolean dead();
	void move();
	void draw();
};
boolean bullet_type::dead()
{
 if (!age) return true;
 return false;
}
void bullet_type::move()
{
 sprt.x += COS(sprt.ang) *speed;
 sprt.y += SIN(sprt.ang) *speed;
 age--;
}
void bullet_type::draw()
{
 int tx = sprt.x -scroll_x, ty = sprt.y -scroll_y;
 if ((tx > -BULLETW) && (ty > -BULLETH) &&
		 (tx < SCREEN_W) && (ty < SCREEN_H))
 kdrawsprite(sprt.x -scroll_x -(BULLETW >> 1), sprt.y -scroll_y -(BULLETH >> 1), BULLETW, BULLETH, bullet_img);
}
class bullets_type
{
 public:
	bullet_type data[MAX_BULLETS];
	unsigned int bullets_no;
	int checkvehiclehit(int x, int y, double ang, int Alpha, double Radius, owner_type owner);
	int checkcirclehit(int x, int y, double radius, owner_type owner);
	int checkbasehit(int x, int y);
	void checkscrollhit();
	void handle();
	void draw();
	void add(double x, double y, int ang, double speed, owner_type owner, int type);
	bullets_type();
};
bullets_type bullets;
int bullets_type::checkvehiclehit(int x, int y, double ang, int Alpha, double Radius, owner_type owner)
{
 for(int b_index = 0; b_index < bullets_no; b_index++)
	if (((owner != PLAYER) || (data[b_index].owner != PLAYER)) &&
			((owner == PLAYER) || (data[b_index].owner != AIRENEMY)))
	 if (krotinrot(data[b_index].sprt.x, data[b_index].sprt.y,
								 data[b_index].sprt.ang,
								 x, y, ang,
								 Alpha, Radius, data[b_index].Alpha, data[b_index].Radius))
	 {
		data[b_index].age = 0;
		return(data[b_index].type +1);
	 }
 return(0);
}
int bullets_type::checkcirclehit(int x, int y, double radius, owner_type owner)
{
 for(int b_index = 0; b_index < bullets_no; b_index++)
	if ((owner != PLAYER) || (data[b_index].owner != PLAYER))
	{
	 if (krectincircle(data[b_index].sprt.x -(BULLETW >> 1), data[b_index].sprt.y -(BULLETH >> 1),
										 data[b_index].sprt.x +(BULLETW >> 1), data[b_index].sprt.y +(BULLETH >> 1),
										 x, y, radius))
	 {
		data[b_index].age = 0;
		return(data[b_index].type +1);
	 }
	}
 return(0);
}
int bullets_type::checkbasehit(int x, int y)
{
 for(int b_index = 0; b_index < bullets_no; b_index++)
	if (krectinrot(x, y, x +gapw, y +gaph,
								 data[b_index].sprt.x, data[b_index].sprt.y,
								 data[b_index].sprt.ang, data[b_index].Alpha, data[b_index].Radius))
	{
	 data[b_index].age = 0;
	 return(data[b_index].type +1);
	}
 return(0);
}
void bullets_type::checkscrollhit()
{
 int x = 0, y = 0, tx, ty, sx, sy;
 for(int b_index = 0; b_index < bullets_no; b_index++)
 {
	if (data[b_index].owner != AIRENEMY)
	{
	 x = data[b_index].sprt.x;
	 y = data[b_index].sprt.y;
	 tx = x >> 4;
	 ty = y >> 4;
	 sx = (x +BULLETW) >> 4;
	 sy = (y +BULLETH) >> 4;
	 if ((blockingxy(tx, ty)) ||
			 (blockingxy(sx, ty)) ||
			 (blockingxy(sx, sy)) ||
			 (blockingxy(tx, sy))) data[b_index].age = 0;
	}
 }
}
void bullets_type::handle()
{
 checkscrollhit();
 for(int b_index = 0; b_index < bullets_no; b_index++)
 {
	if (data[b_index].dead())
	{
	 bullets_no--;
	 data[b_index] = data[bullets_no];
	}
	else data[b_index].move();
 }
}
void bullets_type::draw()
{
 for(int b_index = 0; b_index < bullets_no; b_index++)
 {
	if (data[b_index].type == 0)
	 data[b_index].draw();
	else
	 data[b_index].sprt.draw(-scroll_x, -scroll_y);
 }
}
void bullets_type::add(double x, double y, int ang, double speed, owner_type owner, int type)
{
 if (bullets_no < MAX_BULLETS)
 {
	data[bullets_no].sprt.set(x, y, (bullets_sprts[type].w >> 1) + 1, (bullets_sprts[type].h >> 1) + 1, ang, bullets_sprts[type].w, bullets_sprts[type].h, bullets_sprts[type].data, true);
	data[bullets_no].type = type;
	data[bullets_no].speed = speed;
	data[bullets_no].age = bullet_max_age;
	data[bullets_no].owner = owner;
	data[bullets_no].Alpha = qrad(atan2(-(data[bullets_no].sprt.h >> 1), (data[bullets_no].sprt.w >> 1)));
	data[bullets_no].Radius = sqrt(0.25 *((data[bullets_no].sprt.w *data[bullets_no].sprt.w) +
																			 (data[bullets_no].sprt.h *data[bullets_no].sprt.h)));
	bullets_no++;
 }
}
bullets_type::bullets_type()
{
 bullets_no = 0;
}
void shoot()
{
 if ((canshoot) && (tank.height >= 0))
 {
	MixVoice(&VoiceData[2]);
	int ang = (tank.layers.ang +tank.layers.sprts[1].ang);
	bullets.add(tank.layers.x +COS(ang) *((CANNONW -CANNONCY) +(BULLETW >> 1)),
							tank.layers.y +SIN(ang) *((CANNONW -CANNONCY) +(BULLETH >> 1)),
							ang, BULLETSPD, PLAYER, 0);
	canshoot = false;
 }
}