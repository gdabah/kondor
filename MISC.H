int counter = 0;
void gotonextlvl()
{
 if (tank.lives > 99) tank.lives = 99;
 if (current_level < MAX_LEVELS)
 {
	screenis(video_buffer);
	drawsprite(160 -(missaccow >> 1), 100 -(missaccoh >> 1), missaccow, missaccoh, missacco_s);
	delay(3500);
	screenis(buffer);
	fadeout();
	current_level++;
	loadmap();
	load_side_bar();
	drawNhandle();
	fadein(gamepal);
 }
 else
 {
	gameoverpage();
	resumegame = false;
	optionmenu = start;
	gameloop = 1;
	clearskeys();
	screenis(video_buffer);
	cleardevice();
	set_game_pal();
	screenis(buffer);
	int hscresult = getscoreplace();
	if (hscresult >= 0) enterhsc(hscresult);
 }
}
void handlecounter()
{
 if (counter > 0) counter--;
 else
 {
	movewater();
	if (!scrollmove) drawscroll();
	counter = 25;
	powericon = !powericon; //We use the same counter for the power icon...
	if (speedactivated)
	 if (!speedcounter--)
	 {
		tank.maxspeed /= 2;
		speedactivated = 0;
	 }
	if (!enemies.enemies_no) gotonextlvl();
	if (air_enemies.enemies_no < planesperlevel)
	{
	 air_enemies.add(-50 +random(2) *(MAP_PIXEL_W +100),
									 -50 +random(2) *(MAP_PIXEL_H +100),
									 0,
									 random(2) +1, random(3) +1,
									 random(1) +1, 0,
									 PIPER);
	}
 }
 if (poweractivated)
 {
	int c_s = slots.getslotn(2);
	if ((counter % 5) == 0)
	{
	 if (slots.data[c_s].amount)
	 {
		if (tank.power < TANK_MAX_POWER)
		{
		 slots.data[c_s].amount--;
		 tank.power += 100;
		 if (tank.power > TANK_MAX_POWER) tank.power = TANK_MAX_POWER;
		 screenis(bkg);
		 setcolor(45);
		 bar(263, 131, 263 +(tank.power /204), 134);
		 screenis(buffer);
		}
		else poweractivated = 0;
	 }
	 else
	 {
		poweractivated = 0;
		slots.data[c_s].amount = 0;
		slots.data[c_s].type = -1;
		slots.erase(c_s);
	 }
	}
 }
}