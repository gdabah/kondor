#define startw 67
#define starth 17
#define startcw 67
#define startch 17
#define resumew 84
#define resumeh 17
#define resumecw 84
#define resumech 17
#define optionsw 92
#define optionsh 17
#define optionscw 92
#define optionsch 17
#define helpw 50
#define helph 16
#define helpcw 50
#define helpch 16
#define exitw 52
#define exith 16
#define exitcw 52
#define exitch 16
#define gameoverw 216
#define gameoverh 40
#define missaccow 198
#define missaccoh 90
#define scoresw 78
#define scoresh 17
#define scorescw 78
#define scoresch 17

#include <qunit.h>
//#include "define.h"
//#include "images.h"
#include "menupix.h"
/*
TABLE OF ORDERS:Images.dat//Kondor2.dat
1.Bullet
2.Tank
3.Cannon
4.Explosion1: 1, 2, 3, 4
5.Explosion2: 1, 2, 3, 4, 5
6.Sweden Key
7.Cross
8.Rocket
9.Shield
10.Piper
11.Turret Pad
12.Mig
13.FShoe
14.Turret Cannon
-->21

TABLE OF ORDERS:Menu.dat//Kondor3.dat
1.Start
2.StartC
3.Resume
4.ResumeC
5.Options
6.OptionsC
7.Help
8.HelpC
9.Exit
10.ExitC
11.Game Over
12.Mission Accomplished
13.Resume
14.ResumeC
-->13
*/
int savesprite(int w, int h, unsigned char *img)
{
 FILE *fil;
 fil = fopen("kondor3.dat", "ab");
 if (fil == NULL) return(0);
 fwrite(&w, 1, sizeof(int), fil);
 fwrite(&h, 1, sizeof(int), fil);
 fwrite(img, 1, w *h, fil);
 fclose(fil);
 return(1);
}
void err()
{
 cout << "i/o error!";
 exit(0);
}
void main()
{
 clrscr();
 /*if (!savesprite(67, 17, start_s)) err();
 if (!savesprite(67, 17, startc_s)) err();
 if (!savesprite(84, 17, resume_s)) err();
 if (!savesprite(84, 17, resumec_s)) err();
 if (!savesprite(92, 17, options_s)) err();
 if (!savesprite(92, 17, optionsc_s)) err();
 if (!savesprite(50, 16, help_s)) err();
 if (!savesprite(50, 16, helpc_s)) err();
 if (!savesprite(52, 16, exit_s)) err();
 if (!savesprite(52, 16, exitc_s)) err();
 if (!savesprite(216, 40, gameover_s)) err();
 if (!savesprite(198, 90, missacco_s)) err();*/
 if (!savesprite(78, 17, scores_s)) err();
 if (!savesprite(78, 17, scoresc_s)) err();
}