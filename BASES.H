void bases_type::add(int x, int y, int gap, int power)
{
 data[bases_no].x = x;
 data[bases_no].y = y;
 data[bases_no].gap = gap;
 data[bases_no].counter = gap;
 data[bases_no].power = power;
 data[bases_no].size = gapw; //GapW is bigger for sure.
 data[bases_no].size2 = (gapw >> 1);
 data[bases_no].power2 = power;
 bases_no++;
}
void bases_type::handle()
{
 for(int b_index = 0; b_index < bases_no; b_index++)
 {
	data[b_index].handle();
	if (data[b_index].power <= 0)
	{
	 current_scores.scores += SCORE_ON_GENERATOR *data[b_index].power2;
	 expls.add(data[b_index].x +5, data[b_index].y +5, EXPL_LENGTH, 1);
	 expls.add(data[b_index].x +gapw -5, data[b_index].y +5, EXPL_LENGTH, 1);
	 expls.add(data[b_index].x +gapw -5, data[b_index].y +gaph -5, EXPL_LENGTH, 1);
	 expls.add(data[b_index].x +5, data[b_index].y +gaph -5, EXPL_LENGTH, 1);
	 expls.add(data[b_index].x +(gapw >> 1), data[b_index].y +(gaph >> 1), EXPL_LENGTH, 1);
	 MixVoice(&VoiceData[4]);
	 bases_no--;
	 data[b_index].clearmap();
	 data[b_index] = data[bases_no];
	 b_index--;
	}
 }
}
void bases_type::draw()
{
 for(int b_index = 0; b_index < bases_no; b_index++)
	data[b_index].draw();
}
int bases_type::checkvehiclehit(int x, int y, int ang, int Alpha, double Radius)
{
 for(int b_index = 0; b_index < bases_no; b_index++)
	if (krectinrot(data[b_index].x, data[b_index].y,
								 data[b_index].x +gapw, data[b_index].y +gaph,
								 x, y, ang, Alpha, Radius))
	{
	 data[b_index].power -= (int)abs(tank.speed);
	 return(1);
	}
 return(0);
}

void base_type::handle()
{
 int canadd = 1;
 int res = bullets.checkbasehit(x, y);
 switch (res)
 {
	case 1: power -= BULLETDAMAGE; break;
	case 2: power -= ROCKETDAMAGE; break;
 }
 counter--;
 if (!counter)
 {
	if (enemies.enemies_no < MAX_GENERATE)
	{
	 for (int e_index = 0; e_index < enemies.enemies_no; e_index++)
		if (krectinrot(x, y -(BASE_H +(gaph >> 1)), x +gapw, y,
									 enemies.data[e_index].layers.x, enemies.data[e_index].layers.y,
									 enemies.data[e_index].layers.ang,
									 enemies.data[e_index].Alpha, enemies.data[e_index].Radius)) canadd = 0;

	 if (krectinrot(x, y -(BASE_H +(gaph >> 1)), x +gapw, y,
									tank.layers.x, tank.layers.y, tank.layers.ang, tank.Alpha, tank.Radius)) canadd = 0;

	 if (canadd)
	 {
		enemies.data[enemies.enemies_no].path[0].x = x +(gapw >> 1);
		enemies.data[enemies.enemies_no].path[0].y = y -BASE_H +(gaph >> 1);
		enemies.add(x +(gapw >> 1), y +(gaph >> 1), 384, random(3) +1, random(4) +3,
								random(3) +1, 1,
								(enemytag)((random(2) +1) *3), 1);
	 }
	}
	counter = gap;
 }
 drawmap();
}
void base_type::drawpowerbar()
{
 setcolor(0);
 int layersy = y +size2 -scroll_y +2,
		 layersx = x -scroll_x,
		 layersx2 = x +GPOWERBARSIZE -scroll_x,
		 layersx3 = x +((float)power /power2) *GPOWERBARSIZE -scroll_x;
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
void base_type::draw()
{
 if (((x -scroll_x) > -gapw) && ((y -scroll_y) > -gaph) &&
		 ((x -scroll_x) < SCREEN_W) && ((y -scroll_y) < SCREEN_H))
		 {
			if (showpb) drawpowerbar();
			kdrawsprite(x -scroll_x, y -scroll_y, gapw, gaph, gap_img);
		 }
}
void base_type::drawmap()
{
 for (int ix = x >> 4; ix <= (x +gapw) >> 4; ix++)
	for (int iy = y >> 4; iy <= (y +gaph) >> 4; iy++)
	minmap[(iy << 6) +(iy << 5) +ix] = 0;
}
void base_type::clearmap()
{
 for (int ix = x >> 4; ix <= (x +gapw) >> 4; ix++)
	for (int iy = y >> 4; iy <= (y +gaph) >> 4; iy++)
	 minmap[(iy << 6) +(iy << 5) +ix] = getmapcol(map[(iy << 6) +(iy << 5) +ix]);
}