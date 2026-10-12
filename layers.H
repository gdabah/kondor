class sprite_type
{
 public:
	double x, y, cx, cy;
	int ang;
	int w, h;
	unsigned char *data;
	boolean visible;
	void set(double nx, double ny, double ncx, double ncy, int nang, int nw, int nh, unsigned char *ndata, boolean nvisible);
	void draw(double px = 0, double py = 0, double pang = 0);
};
void sprite_type::set(double nx, double ny, double ncx, double ncy, int nang, int nw, int nh, unsigned char *ndata, boolean nvisible)
{
 x = nx;
 y = ny;
 cx = ncx;
 cy = ncy;
 ang = nang;
 w = nw;
 h = nh;
 data = ndata;
 visible = nvisible;
}
void sprite_type::draw(double px, double py, double pang)
{
 if (visible) krotsprite(px +x, py +y, cx, cy, pang +ang, w, h, data);
}
class sprt_layers_type
{
 public:
	double x, y;
	int ang;
	unsigned int sprts_no;
	sprite_type sprts[MAX_LAYERS];
	void draw();
	void set(double nx, double ny, int nang, unsigned int nsprts_no);
	void close();
};
void sprt_layers_type::set(double nx, double ny, int nang, unsigned int nsprts_no)
{
 x = nx;
 y = ny;
 ang = nang;
 sprts_no = nsprts_no;
}
void sprt_layers_type::draw()
{
 for(int s_index = 0; s_index < sprts_no; s_index++)
	sprts[s_index].draw(x -scroll_x, y -scroll_y, ang);
}
void sprt_layers_type::close()
{
 sprts_no = 0;
}