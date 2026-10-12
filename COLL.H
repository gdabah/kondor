pointtypei cur_coll;
int inrect(int x, int y, int x1, int y1, int x2, int y2)
{
 if ((x >= x1) && (y >= y1) && (x <= x2) && (y <= y2)) return(1);
 return(0);
}
int kincircle(int ix, int iy, int x, int y, double radius_pb2)
{
 return((((ix -x) *(ix -x)) +((iy -y) *(iy -y))) < radius_pb2);
}
int krectincircle(int x1, int y1, int x2, int y2, int ox, int oy, double radius_pb2)
{
 return(kincircle(x1, y1, ox, oy, radius_pb2) ||
				kincircle(x2, y1, ox, oy, radius_pb2) ||
				kincircle(x2, y2, ox, oy, radius_pb2) ||
				kincircle(x1, y2, ox, oy, radius_pb2));
}
int kcheckslope(int x, int y, int x1, int y1, int x2, int y2)
{
 double slope = (double)(y1 -y2) /(x1 -x2 +0.000001),
				xmin = x1 +(y1 -y) *slope,
				xmax = x2 +(y2 -y) *slope;
 if (xmin > xmax) swapdouble(&xmin, &xmax);
 if ((x >= xmin) && (x <= xmax)) return(1);
 return 0;
}
int kinrotrect2(int x, int y, double Ax, double Ay, double Bx, double By, double Cx, double Cy)
{
 if (kcheckslope(x, y, Ax, Ay, Bx, By) &&
		 kcheckslope(x, y, Bx, By, Cx, Cy)) return(1);
 return 0;
}
int krectinrot(int x1, int y1, int x2, int y2,
							double Ox, double Oy, int ang, int Alpha, double Radius)
{
 double	Ax = Ox +COS(ang +Alpha) *Radius,
				Ay = Oy +SIN(ang +Alpha) *Radius,
				Bx = Ox +COS(ang +256 -Alpha) *Radius,
				By = Oy +SIN(ang +256 -Alpha) *Radius,
				Cx = Ox +COS(ang +256 +Alpha) *Radius,
				Cy = Oy +SIN(ang +256 +Alpha) *Radius,
				Dx = Ox +COS(ang +512 -Alpha) *Radius,
				Dy = Oy +SIN(ang +512 -Alpha) *Radius;
 if ((inrect(Ax, Ay, x1, y1, x2, y2)) ||
		(inrect(Bx, By, x1, y1, x2, y2)) ||
		(inrect(Cx, Cy, x1, y1, x2, y2)) ||
		(inrect(Dx, Dy, x1, y1, x2, y2))) return(1);
 if ((kinrotrect2(x1, y1, Ax, Ay, Bx, By, Cx, Cy)) ||
		(kinrotrect2(x2, y1, Ax, Ay, Bx, By, Cx, Cy)) ||
		(kinrotrect2(x2, y2, Ax, Ay, Bx, By, Cx, Cy)) ||
		(kinrotrect2(x1, y2, Ax, Ay, Bx, By, Cx, Cy)))	return(2);
 /*line(Ax -scroll_x, Ay -scroll_y, Bx -scroll_x, By -scroll_y);
 line(Bx -scroll_x, By -scroll_y, Cx -scroll_x, Cy -scroll_y);
 line(Cx -scroll_x, Cy -scroll_y, Dx -scroll_x, Dy -scroll_y);
 line(Dx -scroll_x, Dy -scroll_y, Ax -scroll_x, Ay -scroll_y);
 rectangle(x1 -scroll_x, y1 -scroll_y, x2 -scroll_x, y2 -scroll_y);*/
 return(0);
}
int krotinrot(int x1, int y1, int ang1,
						 int x2, int y2, int ang2,
						 int Alpha1, double Radius1, int Alpha2, double Radius2)
{
 double	Ax = x1 +COS(ang1 +Alpha1) *Radius1,
				Ay = y1 +SIN(ang1 +Alpha1) *Radius1,
				Bx = x1 +COS(ang1 +256 -Alpha1) *Radius1,
				By = y1 +SIN(ang1 +256 -Alpha1) *Radius1,
				Cx = x1 +COS(ang1 +256 +Alpha1) *Radius1,
				Cy = y1 +SIN(ang1 +256 +Alpha1) *Radius1,
				Dx = x1 +COS(ang1 +512 -Alpha1) *Radius1,
				Dy = y1 +SIN(ang1 +512 -Alpha1) *Radius1;
 double	Ex = x2 +COS(ang2 +Alpha2) *Radius2,
				Ey = y2 +SIN(ang2 +Alpha2) *Radius2,
				Fx = x2 +COS(ang2 +256 -Alpha2) *Radius2,
				Fy = y2 +SIN(ang2 +256 -Alpha2) *Radius2,
				Gx = x2 +COS(ang2 +256 +Alpha2) *Radius2,
				Gy = y2 +SIN(ang2 +256 +Alpha2) *Radius2,
				Hx = x2 +COS(ang2 +512 -Alpha2) *Radius2,
				Hy = y2 +SIN(ang2 +512 -Alpha2) *Radius2;
 if (kinrotrect2(Ax, Ay, Ex, Ey, Fx, Fy, Gx, Gy))
 {
	cur_coll.x = Ax;
	cur_coll.y = Ay;
	return(1);
 }
 if (kinrotrect2(Bx, By, Ex, Ey, Fx, Fy, Gx, Gy))
 {
	cur_coll.x = Bx;
	cur_coll.y = By;
	return(1);
 }
 if (kinrotrect2(Cx, Cy, Ex, Ey, Fx, Fy, Gx, Gy))
 {
	cur_coll.x = Cx;
	cur_coll.y = Cy;
	return(1);
 }
 if (kinrotrect2(Dx, Dy, Ex, Ey, Fx, Fy, Gx, Gy))
 {
	cur_coll.x = Dx;
	cur_coll.y = Dy;
	return(1);
 }
 if (kinrotrect2(Ex, Ey, Ax, Ay, Bx, By, Cx, Cy))
 {
	cur_coll.x = Ex;
	cur_coll.y = Ey;
	return(1);
 }
 if (kinrotrect2(Fx, Fy, Ax, Ay, Bx, By, Cx, Cy))
 {
	cur_coll.x = Fx;
	cur_coll.y = Fy;
	return(1);
 }
 if (kinrotrect2(Gx, Gy, Ax, Ay, Bx, By, Cx, Cy))
 {
	cur_coll.x = Gx;
	cur_coll.y = Gy;
	return(1);
 }
 if (kinrotrect2(Hx, Hy, Ax, Ay, Bx, By, Cx, Cy))
 {
	cur_coll.x = Hx;
	cur_coll.y = Hy;
	return(1);
 }
 return(0);
}