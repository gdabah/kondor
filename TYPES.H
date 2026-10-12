class tank_type
{
 public:
	sprt_layers_type layers;
	double accel, speed, maxspeed, turn_speed, cannon_turn_speed;
	int	Alpha;
	double Radius;
	float height, heightspeed;
	unsigned int power, lives;
	int shieldhits;
	float shieldrad;
	int halfwidth_3;
	void hit(unsigned int p);
	void isdead();
	void handle();
	int moveable(int ix, int iy);
	int checkhit();
	void turn(int direction);
	void draw();
	void move();
	void turn_cannon(int direction);
};
tank_type tank;
enum enemytag {EMPTY = 0, TURRET = 1, CIRCLE = 2, RANDOM = 3, PATH_FIND = 4, ANGLE = 5, FOLLOW = 6, PIPER = 7, MIG = 8};
class enemy_type
{
 public:
	enemytag behavior;
	int mode, temp, temp2, dir;
	double speed, turn_speed;
	int power, size, power2, size2, doublespeed;
	int	Alpha;
	int moveable, notmyfault;
	double Radius;
	sprt_layers_type layers;
	pointtypei path[ENEMY_MAX_PATH_LENGTH];
	int path_len;
	int cur_point;
	void shootondist();
	void smartmove(int me);
	void move(int me);
	void handle(int me);
	void drawpowerbar();
	void draw();
	int dead();
};
class enemies_type
{
 public:
	enemy_type data[MAX_ENEMIES];
	int enemies_no;
	int checkvehiclehit(int x, int y, int ang, int Alpha, double Radius, int me);
	void handle();
	void draw();
	void add(double x, double y, int ang, double speed, double turn_speed, unsigned int power, int path_len, enemytag behav, int mode);
	void close();
	enemies_type();
} enemies;
class air_enemy_type
{
 public:
	pointtypei path[ENEMY_MAX_PATH_LENGTH];
	int tempx, tempy, mode, mode2;
	int cur_point, path_len;
	enemytag behavior;
	int temp, temp2;
	double speed, speed2, turn_speed;
	int power, size, halfwidth, halfheight;
	int	Alpha;
	double Radius;
	sprite_type sprt;
	void targetondist();
	void move();
	void handle();
	void draw();
	int dead();
};
class air_enemies_type
{
 public:
	air_enemy_type data[MAX_AIR_ENEMIES];
	int enemies_no;
	void handle();
	void draw();
	void add(double x, double y,
					 int ang, double speed, double turn_speed,
					 unsigned int power, int path_len, enemytag behav);
	void close();
	air_enemies_type();
} air_enemies;
class base_type
{
 public:
	int x, y, counter, gap, power, size, power2, size2;
	void handle();
	void draw();
	void drawpowerbar();
	void drawmap();
	void clearmap();
};
class bases_type
{
 public:
	base_type data[MAX_BASES];
	int bases_no;
	void add(int x, int y, int gap, int power);
	int checkvehiclehit(int x, int y,
											int ang, int Alpha,
											double Radius);
	void handle();
	void draw();
} bases;
struct frame_type
{
 int w;
 int h;
 unsigned char *sprt;
};
class frames_type
{
 public:
 int frame;
 int maxframe;
 frame_type frames[MAXFRAMES];
 void add(int w, int h, unsigned char *sprt);
 void draw(int x, int y);
 frames_type();
};

struct bonus_type{
 int w;
 int h;
 unsigned char *sprt;
};
bonus_type bonussprts[5];