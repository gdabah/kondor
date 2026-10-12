//Will draw the map ! ! !
unsigned char getmapcol(unsigned char tile)
{
 if (tile == 0 || tile == 1)
 {
	switch (random(5))
	{
	 case 0: return(4);
	 case 1: return(5);
	 case 2: return(7);
	 case 3: return(10);
	 case 4: return(11);
	}
 }
 switch(tile)
 {
	case 7: return(29);
	case 8: return(30);
	case 9: return(31);
	case 10: return(32);
	case 11: return(33);
	case 12: return(30);
	case 13: return(32);
	case 14: return(44);
	case 15: return(50);
	case 16: return(52);
	case 17: return(47);
	case 18: return(58);
	case 19: return(59);
	case 20: return(55);
	case 253: return(33);
	case 254: return(11);
	case 255: return(72);
 }
 if (((tile >= 21) && (tile <= 36)) ||
		 ((tile >= 53) && (tile <= 68)) ||
		 ((tile >= 69) && (tile <= 76))) return (160);
 if (((tile >= 37) && (tile <= 52)) ||
		 ((tile >= 85) && (tile <= 100)) ||
		 ((tile >= 77) && (tile <= 84))) return(183);
 if (tile >= 101) return(100);
 return(0);
}
void drawminmap()
{
 fillscreen(0);
 for(int ix = 0; ix < MAP_W; ix ++)
	for(int iy = 0; iy < MAP_H; iy ++)
	 plotpixel(111 +ix, 51 +iy, getmapcol(map[(iy << 5) +(iy << 6) +ix]));
 setcolor(0);
 for (int i = 0; i <= EADD; i++) ;
	//if (enemies[i].behavior != TURRET) //plotpixel(111 +(enemies[i].x >> 4), 51 +(enemies[i].y >> 4), 80);
	//writestrxy(111 +(enemies[i].x >> 4), 51 +(enemies[i].y >> 4), i);
	 //else plotpixel(111 +(enemies[i].x >> 4), 51 +(enemies[i].y >> 4), 0);
 rectangle(110 +(scroll_x >> 4), 50 +(scroll_y >> 4), 110 +(scroll_x >> 4) +20, 50 +(scroll_y >> 4) +13);
}
void drawmap()
{
 cleardevice();
 drawminmap();
 drawscreen(scr);
 delay(1000);
 while(!keydown(28)) ;
 clearskeys();
}