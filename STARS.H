//This header handle the stars effect.
#define MAXSTARS 300 //Change it.......
//Struct of the stars
typedef struct tagstar{
											 int x;
											 int y;
											 int z;
											 unsigned char col;
											};
//Array of the stars
tagstar stars[MAXSTARS];
//Create the star n
void createstar(int starn)
{
 do { stars[starn].x = (random(320) -160); } while(!stars[starn].x);
 do { stars[starn].y = (random(200) -100); } while(!stars[starn].y);
 stars[starn].z = 255;
 stars[starn].col = random(2);
}
//Move the star n
void movestar(int starn)
{
 if (!stars[starn].z--) createstar(starn);
}
//Draw the star n
void drawstar(int starn)
{
 plotpixel(((stars[starn].x << 8) /stars[starn].z) +160,
					 ((stars[starn].y << 8) /stars[starn].z) +100,
					 56 +stars[starn].col *8 +(256 -stars[starn].z) /32);
}
//Handle does:Move, Draw, Check limits
void handlestars()
{
 int x = 0;
 int y = 0;
 for (int i = 0; i < MAXSTARS; i++)
 {
	x = ((stars[i].x << 8) /stars[i].z) +160;
	y = ((stars[i].y << 8) /stars[i].z) +100;
	if ((x > 319) || (x < 0) || (y > 199) || (y < 0)) createstar(i);
	movestar(i);
	drawstar(i);
 }
}
//Init does:Set x, y, z, col of each star.
void initstars()
{
 for (int i = 0; i < MAXSTARS; i++)
 {
	createstar(i);
	stars[i].z = random(255) +1;
 }
}