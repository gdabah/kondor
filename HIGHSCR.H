//This header will handle the scores...board, calculation...
#define MAX_SCORE_NAME 14
struct hsc_type
{
 char name[MAX_SCORE_NAME];
 unsigned int enemies;
 unsigned int scores;
};
hsc_type highscores[MAX_SCORES];
hsc_type current_scores;
float cy, cx = 0.4, dx = 0.02; //Cursor position
int getscoreplace()
{
 for (int i = 0; i < MAX_SCORES; i++)
	if (current_scores.scores > highscores[i].scores)
	{
	 for (int j = MAX_SCORES -1; j > i; j--)
		highscores[j] = highscores[j -1];
	 highscores[i] = current_scores;
	 highscores[i].name[0] = '\0';
	 return(i);
	}
 return(-1);
}
void drawscores()
{
 for (int id = 0; id < MAX_SCORES; id++)
	if (highscores[id].scores != 0) //No Player...
	{
	 drawstring(46, 45 +(id *14), highscores[id].name);
	 drawstring(171, 45 +(id *14), highscores[id].enemies);
	 drawstring(234, 45 +(id *14), highscores[id].scores);
	}
}
void savescores()
{
 FILE *hsfs;
 if ((hsfs = fopen(SCORES_FILE, "wb")) == NULL) filerr();
 for (int is = 0; is < MAX_SCORES; is++)
	fwrite(&highscores[is], sizeof(hsc_type), 1, hsfs);
 fclose(hsfs);
}
void loadscores()
{
 FILE *hsfl;
 if ((hsfl = fopen(SCORES_FILE, "rb")) == NULL) filerr();
 for (int il = 0; il < MAX_SCORES; il++)
	fread(&highscores[il], sizeof(hsc_type), 1, hsfl);
 fclose(hsfl);
}
void showhighscr()
{
 blackpal();
 screenis(bkg);
 if (!load32(HSC_BOARD_FILE)) filerr();
 screenis(buffer);
 cleardevice();
 copyscreen(buffer, bkg);
 drawscores();
 drawscreen(buffer);
 fadein(gamepal);
 int scrdone = 0;
 while(!scrdone)
 {
	copyscreen(buffer, bkg);
	if (keydown(skeyESC)) scrdone = 1;
	drawscores();
	drawscreen(buffer);
 }
 fadeout();
}
//For name's input.
void drawcursor(int x, int y, int pos = 0)
{
 setcolor(106);
 if (cx > 3) { dx *= (-1); cy = 0; }
 if (cx < 0) { dx *= (-1); cy = 1; }
 cx += dx;
 horline(y +cy, x +cx +(pos *6), x +3 +cx +(pos *6));
}
void enterhsc(int place)
{
 int y = 50 +(place *14), x = 46, strpos = 0;
 blackpal();
 screenis(bkg);
 if (!load32(HSC_BOARD_FILE)) filerr();
 screenis(buffer);
 cleardevice();
 copyscreen(buffer, bkg);
 drawscores();
 drawcursor(x, y, strpos);
 drawscreen(buffer);
 fadein(gamepal);
 while(1)
 {
	copyscreen(buffer, bkg);
	if ((keydown(skeyENTER)) && (highscores[place].name[0] != '\0')) break;//One letter is enough..
	if (keydown(skeyBACKSPACE))
	{
	 if (strpos > 0)
	 {
		strpos--;
		highscores[place].name[strpos] = '\0';
	 }
	 keypress[skeyBACKSPACE] = 0;
	}
	else
	if (skeypressed())
	{
	 if (strpos < 13)
	 {
		char ch = skey2char(skeypressed());
		if (ch != '\0')
		{
		 highscores[place].name[strpos] = ch;
		 highscores[place].name[strpos +1] = '\0';
		 keypress[skeypressed()] = 0;
		 strpos++;
		}
	 }
	}
	drawstring(x, y -5, highscores[place].name);
	drawscores();
	drawcursor(x, y, strpos);
	drawscreen(buffer);
 }
 savescores();
 fadeout();
}