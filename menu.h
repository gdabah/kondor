//This include handle the start of the game.......Menu...Stars(effect)
int resumeyplace = 0; //This will help to draw the sprites even if the resume label is exist!
//Draw the menu with Resume checking!
void drawmenu()
{
 if (resumegame) resumeyplace = 25;
 else resumeyplace = 0;
 drawsprite(160 -(startw >> 1), 50, startw, starth, start_s);
 if (resumegame) drawsprite(160 -(resumew >> 1), 75, resumew, resumeh, resume_s);
 drawsprite(160 -(optionsw >> 1), 75 +resumeyplace, optionsw, optionsh, options_s);
 drawsprite(160 -(scoresw >> 1), 100 +resumeyplace, scoresw, scoresh, scores_s);
 drawsprite(160 -(helpw >> 1), 125 +resumeyplace, helpw, helph, help_s);
 drawsprite(160 -(exitw >> 1), 150 +resumeyplace, exitw, exith, exit_s);
 switch (optionmenu)
 {
	case start:
	 drawsprite(160 -(startcw >> 1), 50, startcw, startch, startc_s);
	break;
	case resume:
		drawsprite(160 -(resumecw >> 1), 75, resumecw, resumech, resumec_s);
	break;
	case option:
	 drawsprite(160 -(optionscw >> 1), 75 +resumeyplace, optionscw, optionsch, optionsc_s);
	break;
	case hghscores:
	 drawsprite(160 -(scorescw >> 1), 100 +resumeyplace, scorescw, scoresch, scoresc_s);
	break;
	case help:
	 drawsprite(160 -(helpcw >> 1), 125 +resumeyplace, helpcw, helpch, helpc_s);
	break;
	case exitgame:
	 drawsprite(160 -(exitcw >> 1), 150 +resumeyplace, exitcw, exitch, exitc_s);
	break;
 }
}
//Clear all screens and load game's pal, load the intro pic
void clearscreen()
{
 screenis(video_buffer);
 cleardevice();
 screenis(buffer);
 cleardevice();
 screenis(bkg);
 if (!load32(INTRO_FILE)) filerr();
 setcolor(86);
 drawstringreg(0, 194, MENU_MSG);
 set_game_pal();
 screenis(buffer);
}
//Main void of the header.
void menu()
{
 boolean quitmenu = false;
 optionmenu = start;
 screenis(buffer);
 while(!quitmenu)
 {
	copyscreen(buffer, bkg);
	/*if (keydown(skeyESC)) //Points the Exit.
	{
	 optionmenu = exitgame;
	 callmsound();
	 clearskeys();
	}*/
	if (keydown(skeyUARROW))
	{
	 switch(optionmenu)
	 {
		case start: optionmenu = exitgame; break;
		case resume: optionmenu = start; break;
		case option: if (resumegame) optionmenu = resume;
								 else optionmenu = start; break;
		case hghscores: optionmenu = option; break;
		case help: optionmenu = hghscores; break;
		case exitgame: optionmenu = help; break;
	 }
	 MixVoice(&VoiceData[0]);
	 clearskeys();
	}
	if (keydown(skeyDARROW))
	{
	 switch(optionmenu)
	 {
		case start: if (resumegame) optionmenu = resume;
								else optionmenu = option; break;
		case resume: optionmenu = option; break;
		case option: optionmenu = hghscores; break;
		case hghscores: optionmenu = help; break;
		case help: optionmenu = exitgame; break;
		case exitgame: optionmenu = start; break;
	 }
	 MixVoice(&VoiceData[0]);
	 clearskeys();
	}
	if (keydown(skeyENTER))
	{
	 switch(optionmenu)
	 {
		case start:
		 if (resumegame)
		 {
			int hscresult = getscoreplace();
			if (hscresult >= 0) enterhsc(hscresult);
			clearscreen();
		 }
		 current_level = START_LEVEL;
		 strcpy(current_scores.name, "");
		 current_scores.scores = 0;
		 current_scores.enemies = 0;
		 tank.lives = 5;
		 resumegame = true;
		 loadmap();
		 start_game();
		 clearscreen();
		 clearskeys();
		break;
		case resume://If the user wants to continue on playing the last game...
		 start_game();
		 clearscreen();
		 clearskeys();
		break;
		case option: //Ok please don't change the sound :)
		 gameoptions();
		 clearscreen();
		 clearskeys();
		break;
		case hghscores: //Show high scores table..
		 showhighscr();
		 clearscreen();
		 clearskeys();
		break;
		case help: //We need the help please......
		 gamehelp();
		 clearscreen();
		 clearskeys();
		break;
		case exitgame: //Don't go please......
		 quitmenu = true;
		break;
	 }
	}
	drawmenu();
	drawscreen(buffer);
 }
}