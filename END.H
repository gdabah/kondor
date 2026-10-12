//This header handles the final part of the game, KONDOR!!!!

#define str1 "ÔÈÁÎË ÙÏÕ ÆÏÒ ÐÌÁÙÉÎÇ"
#define str2 "ËÏÎÄÏÒ¡"
#define str3 "ÑÓÏÆÔ ±¹¹·­±¹¹¹¨Ã©"
#define str4 "ÂÙ ÇÉÌ ÄÁÂÁÈ ÁÎÄ ÏÒÅÎ ÂÅÃËÅÒ"

void gameoverpage()
{
 int edone = 0;
 double y = 200;
 screenis(video_buffer);
 clearscreen();
 screenis(bkg);
 if (!loadpal(ENDPAL)) filerr();
 if (!load32(ENDIMG)) filerr();
 screenis(buffer);
 setcolor(0);
 while (!edone)
 {
	copyscreen(buffer, bkg);
	drawstringreg(160 -(strlen(str1) *2.5), y, str1);
	drawstringreg(160 -(strlen(str2) *2.5), y +8, str2);
	drawstringreg(160 -(strlen(str3) *2.5), y +30, str3);
	drawstringreg(160 -(strlen(str4) *2.5), y +38, str4);
	if (y > -43) y -= 0.5;
	if (keydown(skeyESC)) edone = 1;
	waitretrace();
	drawscreen(buffer);
 }
}