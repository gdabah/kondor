//This header handles in the options menu:Keys, 1 player...SOUND! ! !
//These winows default position.
#define winx 40
#define winy 25
#define winx2 (320 -winx)
#define winy2 (winy +11)
#define winspace 2 //Space between each window.
#define INPUTKEYS 12 //We have 13 keys to input.
//Temp sound fx.
int tempsoundfx = 1;
const int calcspace = (winy2 -winy) +winspace; //Calculate the place of the texts.
/*You may change these keys, that's why they're int.
These keys will have a default.*/
int firekey = skeyLEFTALT; //Fire(shooting).SpaceBar.
int breakskey = skeySPACE; // To stop.
int arrowup = skeyUARROW; //Up.
int arrowdown = skeyDARROW; //Down.
int arrowleft = skeyLARROW; //Left.
int arrowright = skeyRARROW; //Right.
int itemkey = skeyENTER; //To use the item that you have in the inventory!
int keylside = skeyLBRACKET; //To rotate the inventory one left.'('
int keyrside = skeyRBRACKET; //To rotate the inventory one right.')'
int keyrotcanl = skeyZ;      //To rotate the cannon left.'z'
int keyrotcanr = skeyX;      //To rotate the cannon right.'x'
/*  //*********-*/ //Chosen key rotate pallette.
#define fadecol 255 //The color we want to rotate.
int fadered = 2; //Red rotates.
int faderedp = 1; //Does it rotates up or down?
char or = 0, og = 0, ob = 0; //Original FadeRed's rgb.
/*  \\*********-*/
//Save keys and info of the options menu.
void saveoptions()
{
 FILE *fs;
 if ((fs = fopen(OPTIONS_FILE, "wb")) == NULL) filerr();
 fwrite(&firekey, sizeof(firekey), 1, fs);
 fwrite(&breakskey, sizeof(breakskey), 1, fs);
 fwrite(&arrowup, sizeof(arrowup), 1, fs);
 fwrite(&arrowdown, sizeof(arrowdown), 1, fs);
 fwrite(&arrowleft, sizeof(arrowleft), 1, fs);
 fwrite(&arrowright, sizeof(arrowright), 1, fs);
 fwrite(&itemkey, sizeof(itemkey), 1, fs);
 fwrite(&keylside, sizeof(keylside), 1, fs);
 fwrite(&keyrside, sizeof(keyrside), 1, fs);
 fwrite(&keyrotcanl, sizeof(keyrotcanl), 1, fs);
 fwrite(&keyrotcanr, sizeof(keyrotcanr), 1, fs);
 fwrite(&showpb, sizeof(showpb), 1, fs);
 fwrite(&soundfx, sizeof(soundfx), 1, fs);
 fclose(fs);
}
//Load keys and info of the options menu.
int loadoptions()
{
 FILE *fl;
 if ((fl = fopen(OPTIONS_FILE, "rb")) == NULL) filerr();
 fread(&firekey, sizeof(firekey), 1, fl);
 fread(&breakskey, sizeof(breakskey), 1, fl);
 fread(&arrowup, sizeof(arrowup), 1, fl);
 fread(&arrowdown, sizeof(arrowdown), 1, fl);
 fread(&arrowleft, sizeof(arrowleft), 1, fl);
 fread(&arrowright, sizeof(arrowright), 1, fl);
 fread(&itemkey, sizeof(itemkey), 1, fl);
 fread(&keylside, sizeof(keylside), 1, fl);
 fread(&keyrside, sizeof(keyrside), 1, fl);
 fread(&keyrotcanl, sizeof(keyrotcanl), 1, fl);
 fread(&keyrotcanr, sizeof(keyrotcanr), 1, fl);
 fread(&showpb, sizeof(showpb), 1, fl);
 fread(&soundfx, sizeof(soundfx), 1, fl);
 fclose(fl);
 if (!soundblaster)
 {
	tempsoundfx = soundfx;
	soundfx = 0; //If there is no SB installed then the SB is turned off.
 }
 return(1);
}
//Only for this game/font.
void drawrect(int x, int y, int x2, int y2)
{
 horline(y, x +2, x2 -2);
 horline(y2, x +2, x2 -2);
 verline(x, y +2, y2 -2);
 verline(x2, y +2, y2 -2);
 plotpixel(x +1, y +1, gcol);
 plotpixel(x2 -1, y +1, gcol);
 plotpixel(x2 -1, y2 -1, gcol);
 plotpixel(x +1, y2 -1, gcol);
}
//This routine returns the 'y' place of the text.
int textplace(int which)
{
 return((which *calcspace) -10 +winy);
}
//Draw the text.
void drawtext()
{
 char textline[255] = "";
 strcpy(textline, "");
 strcpy(textline, "ÆÉÒÅº ");
 strcat(textline, getkeyname(firekey));
 drawstring(winx +5, textplace(1), textline);
 strcpy(textline, "ÂÒÅÁËº ");
 strcat(textline, getkeyname(breakskey));
 drawstring(winx +5, textplace(2), textline);
 strcpy(textline, "ÍÏÖÅ ÌÅÆÔº ");
 strcat(textline, getkeyname(arrowleft));
 drawstring(winx +5, textplace(3), textline);
 strcpy(textline, "ÍÏÖÅ ÒÉÇÈÔº ");
 strcat(textline, getkeyname(arrowright));
 drawstring(winx +5, textplace(4), textline);
 strcpy(textline, "ÍÏÖÅ ÆÏÒ×ÁÒÄº ");
 strcat(textline, getkeyname(arrowup));
 drawstring(winx +5, textplace(5), textline);
 strcpy(textline, "ÍÏÖÅ ÂÁÃË×ÁÒÄº ");
 strcat(textline, getkeyname(arrowdown));
 drawstring(winx +5, textplace(6), textline);
 strcpy(textline, "ÕÓÅ ÉÎÖÅÎÔÏÒÙº ");
 strcat(textline, getkeyname(itemkey));
 drawstring(winx +5, textplace(7), textline);
 strcpy(textline, "ÉÎÖÅÎÔÏÒÙ ÌÅÆÔº ");
 strcat(textline, getkeyname(keylside));
 drawstring(winx +5, textplace(8), textline);
 strcpy(textline, "ÉÎÖÅÎÔÏÒÙ ÒÉÇÈÔº ");
 strcat(textline, getkeyname(keyrside));
 drawstring(winx +5, textplace(9), textline);
 strcpy(textline, "ÒÏÔÁÔÅ ÃÁÎÎÏÎ ÌÅÆÔº ");
 strcat(textline, getkeyname(keyrotcanl));
 drawstring(winx +5, textplace(10), textline);
 strcpy(textline, "ÒÏÔÁÔÅ ÃÁÎÎÏÎ ÒÉÇÈÔº ");
 strcat(textline, getkeyname(keyrotcanr));
 drawstring(winx +5, textplace(11), textline);
 strcpy(textline, "ĞÏ×ÅÒÂÁÒº ");
 if (showpb) strcat(textline, "ÏÎ");
 else strcat(textline, "ÏÆÆ");
 drawstring(winx +5, textplace(12), textline);
 strcpy(textline, "ÓÏÕÎÄº ");
 if (soundfx) strcat(textline, "ÏÎ");
 else strcat(textline, "ÏÆÆ");
 drawstring(winx +5, textplace(13), textline);
}
//This shows the windows that will show you what key to in-put!!
void drawwindow(int chosen)
{
 fadered += faderedp;
 if ((fadered > 62) || (fadered < 2)) faderedp *= -1;
 setpal(fadecol, fadered, 0, 0);
 drawsprite(160 -(optionscw /2), 5, optionscw, optionsch, optionsc_s);
 for (int index = 0; index <= INPUTKEYS; index++)
 {
	if (index == chosen) setcolor(fadecol);
	else setcolor(107);
	drawrect(winx, winy +(index *calcspace), winx2, winy2 +(index *calcspace) -1);
 }
 drawtext();
}
//Pointer to key.
int *ptrkey(int which)
{
 switch(which)
 {
	case 0: return(&firekey);
	case 1: return(&breakskey);
	case 2: return(&arrowleft);
	case 3: return(&arrowright);
	case 4: return(&arrowup);
	case 5: return(&arrowdown);
	case 6: return(&itemkey);
	case 7: return(&keylside);
	case 8: return(&keyrside);
	case 9: return(&keyrotcanl);
	case 10: return(&keyrotcanr);
 }
 return(&firekey); //Shouldn't be here, but compiler needs it.
}
//Check out whether the player pressed this key before.
int checkkey(int *keyn, int which)
{
 if (*keyn == 170) return(0);        //Extended key scan code.
 if (*keyn == firekey) swapint(ptrkey(which), &firekey);
 if (*keyn == breakskey) swapint(ptrkey(which), &breakskey);
 if (*keyn == arrowleft) swapint(ptrkey(which), &arrowleft);
 if (*keyn == arrowright) swapint(ptrkey(which), &arrowright);
 if (*keyn == arrowup) swapint(ptrkey(which), &arrowup);
 if (*keyn == arrowdown) swapint(ptrkey(which), &arrowdown);
 if (*keyn == itemkey) swapint(ptrkey(which), &itemkey);
 if (*keyn == keylside) swapint(ptrkey(which), &keylside);
 if (*keyn == keyrside) swapint(ptrkey(which), &keyrside);
 if (*keyn == keyrotcanl) swapint(ptrkey(which), &keyrotcanl);
 if (*keyn == keyrotcanr) swapint(ptrkey(which), &keyrotcanr);
 return(1);
}
//Wait until key is being pressed then get a key that in the array.
void waitforkey(int *key, int which)
{
 int finished = 0;
 int index = 0;
 clearskeys();
 while(!finished)
 {
	copyscreen(buffer, bkg);
	for (index = 1; index < 256; index++)
	 if (keydown(index))
	 {
		if (index == skeyESC)
		{
		 MixVoice(&VoiceData[1]);
		 return; //Whether the player wants the key to remain.
		}
		if (checkkey(&index, which))
		{
		 MixVoice(&VoiceData[1]);
		 finished = 1;
		 break;
		}
	 }
	drawwindow(which);
	drawscreen(buffer);
 }
 *key = index;
 clearskeys();
}
//Waits the player to press SpaceBar.(sound off/on)
void waitforspace(int *val, int win)
{
 int finished = 0;
 delay(35);
 clearskeys();
 while(!finished)
 {
	copyscreen(buffer, bkg);
	if (keydown(skeySPACE)) //You may not change the off/on, if your SB is not installed.
	{
	 if (*val) *val = false;
	 else *val = true;
	 MixVoice(&VoiceData[1]);
	 clearskeys();
	}
	if (keydown(skeyESC))
	{
	 MixVoice(&VoiceData[1]);
	 return; //Whether the player wants the key(or option) to remain.
	}
	if (keydown(skeyENTER))
	{
	 MixVoice(&VoiceData[1]);
	 return; //The player just chose his option.(Enter)
	}
	drawwindow(win);
	drawscreen(buffer);
 }
}
void gameoptions() //Options routine.
{
 getpal(fadecol, &or, &og, &ob); //Get the pal chosen's fade color.
 blackpal();
 screenis(bkg);
 cleardevice();
 screenis(buffer);
 cleardevice();
 copyscreen(buffer, bkg);
 drawwindow(0);
 drawscreen(buffer);
 fadein(gamepal);
 waitforkey(&firekey, 0);
 waitforkey(&breakskey, 1);
 waitforkey(&arrowleft, 2);
 waitforkey(&arrowright, 3);
 waitforkey(&arrowup, 4);
 waitforkey(&arrowdown, 5);
 waitforkey(&itemkey, 6);
 waitforkey(&keylside, 7);
 waitforkey(&keyrside, 8);
 waitforkey(&keyrotcanl, 9);
 waitforkey(&keyrotcanr, 10);
 waitforspace(&showpb, 11);
 if (soundblaster) waitforspace(&soundfx, 12);
 saveoptions();
 setpal(fadecol, or, og, ob); //Original 255's pal, because we change the pal at the fade (chosen).
 fadeout();
}