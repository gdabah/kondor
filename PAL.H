//This heander handles in the palettes stuff...
unsigned char gamepal[768]; //Gloabl game's pal array.
//Make darker colors.
void makeshadowpal()
{
 unsigned char r, g, b;
 for(int i = 0; i < 128; i++)
 {
	gamepal[(i +128) *3] = gamepal[i *3] *0.75;
	gamepal[(i +128) *3 +1] = gamepal[(i *3) +1] *0.75;
	gamepal[(i +128) *3 +2] = gamepal[(i *3) +2] *0.75;
 }
}
//This routine loads the game pal from a file.
int load_game_pal()
{
 FILE *fil;
 if ((fil = fopen(PAL_FILE, "rb")) == NULL) filerr();
 fread(gamepal, 1, 768, fil);
 fclose(fil);
 makeshadowpal();
 return(1);
}
void set_game_pal()
{
 for (int i = 0; i < 256; i++)
	setpal(i, gamepal[i *3], gamepal[(i *3) +1], gamepal[(i *3) +2]);
}