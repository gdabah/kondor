class object_type
{
 public:
	int x, y;
	int w, h;
	int type;
	unsigned char *sprt;
	void draw();
};
void object_type::draw()
{
 int tx = x -scroll_x, ty = y -scroll_y;
 if ((tx > -w) && (ty > -h) &&
		 (tx < SCREEN_W) && (ty < SCREEN_H))
	kdrawsprite(tx, ty, w, h, sprt);
}
class objects_type
{
 public:
	object_type data[MAX_OBJECTS];
	unsigned int objects_no;
	int checkvehiclehit(int x, int y, int ang, int Alpha, double Radius);
	void checkscrollhit();
	void draw();
	void handle();
	void add(double x, double y, int type);
	objects_type();
};
objects_type objects;
int objects_type::checkvehiclehit(int x, int y, int ang, int Alpha, double Radius)
{
 int temp;
 for(int b_index = 0; b_index < objects_no; b_index++)
	if (krectinrot(data[b_index].x, data[b_index].y,
								 data[b_index].x +data[b_index].w, data[b_index].y +data[b_index].h,
								 x, y, ang, Alpha, Radius))
	{
	 temp = data[b_index].type;
	 objects_no--;
	 data[b_index] = data[objects_no];
	 return(temp);
	}
 return(-1);
}
void objects_type::handle()
{
 int type = checkvehiclehit(1, 1, 1, 1, 1);
 if	(type == -1) return;
 else slots.add(type);
}
void objects_type::draw()
{
 for(int b_index = 0; b_index < objects_no; b_index++)
	data[b_index].draw();
}
void objects_type::add(double x, double y, int type)
{

 if (objects_no < MAX_OBJECTS)
 {
	data[objects_no].x = x;
	data[objects_no].y = y;
	data[objects_no].w = 16;
	data[objects_no].h = 16;
	data[objects_no].type = type;
	data[objects_no].sprt = rock_img;//Make a switch for type and select sprite.
	objects_no++;
 }
}
objects_type::objects_type()
{
 objects_no = 0;
}