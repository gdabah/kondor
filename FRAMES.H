void frames_type::add(int w, int h, unsigned char *sprt)
{
 frames[maxframe].w = w;
 frames[maxframe].h = h;
 frames[maxframe].sprt = sprt;
 maxframe++;
}
void frames_type::draw(int x, int y)
{
 x -= frames[frame].w >> 1;
 y -= frames[frame].h >> 1;
 if (((x -scroll_x) > -frames[frame].w) &&
		 ((x -scroll_x) < (SCREEN_W +frames[frame].w) &&
		 ((y -scroll_y) > -frames[frame].h)) &&
		 ((y -scroll_y) < (SCREEN_H +frames[frame].h)))
	kdrawsprite(x -scroll_x, y -scroll_y,
							frames[frame].w, frames[frame].h, frames[frame].sprt);
}
frames_type::frames_type()
{
 frame = 0;
 maxframe = 0;
}