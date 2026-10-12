#define FONT_FILE      "kondor.fnt"
//"qsoft.fnt"
#define OPTIONS_FILE   "kondor.cfg"
//"funtank.cfg"
#define PAL_FILE       "kondor.pal"
//"pal.dat"
#define TILES_FILE 	   "kondor.dat"
//"sprites.dat"
#define IMAGES_FILE    "kondor2.dat"
//"images.dat"
#define MENU_IMGS_FILE "kondor3.dat"
//"menu.dat"
#define INTRO_FILE     "kondor4.dat"
//"start.dat"
#define SIDE_BAR_FILE  "kondor5.dat"
//sidebar.dat"
#define HSC_BOARD_FILE  "kondor6.dat"
//hscpage.dat"
#define SCORES_FILE "kondor.hsc"
//kondor 7 and on are the wav's.
#define INTROIMG "kondor17.dat"
#define INTROPAL "kondor18.dat"
#define ENDIMG "kondor19.dat"
#define ENDPAL "kondor20.dat"

#define BULLETW 5
#define BULLETH 5
#define TANKW 23
#define TANKH 24
#define CANNONW 20
#define CANNONH 6
#define CANNONCY 4
#define BASE_W 40
#define BASE_H 60

#define MAP_W 96
#define MAP_H 96

#define WINDOW_X 0
#define WINDOW_Y 0
#define WINDOW_W 16
#define WINDOW_H 12
#define TILE_W 16
#define TILE_H 16
#define SCRRANGE 95
#define SPRITES_NO 115
#define MAXFRAMES 10

const int SCREEN_W = WINDOW_W *TILE_W;
const int SCREEN_H = WINDOW_H *TILE_H;
const int MAP_PIXEL_W = MAP_W *TILE_W;
const int MAP_PIXEL_H = MAP_H *TILE_H;

#define BULLETSPD 5
#define BULLETDAMAGE 3
#define ROCKETDAMAGE 8
#define TSHOOTRANGE 18225
#define ESHOOTRANGE 9025
#define MSHOOTRANGE 4900
#define FLYTOOCLOSE 2500
#define EHUNTRANGE  10000
#define MAX_BULLETS 100
#define BULLETW 5
#define BULLETH 5

#define MAX_ENEMIES 55
#define MAX_AIR_ENEMIES 30
#define MAX_OBJECTS 40 //-BONUSES
#define MAX_BASES 5
#define MAX_GENERATE 20
int planesperlevel = 0;

#define MAX_EXPLS 10
#define ENEMY_MAX_PATH_LENGTH 30
#define EXPL_LENGTH 45
#define TANK_MAX_POWER 10000
#define MAX_SHIELD_HITS 10
#define SHIELD_RAD_RATE 0.5
#define SHIELD_MAX_RAD 20
const SMR_PB2 = SHIELD_MAX_RAD *SHIELD_MAX_RAD;
#define MAX_SLOTS     4
#define EPOWERBARSIZE 20
#define POWERUPSPEED  25
#define SPEEDTIME     30
#define HIT_SPEED     0.2

#define BONUS_RANGE 7
#define MAX_LIVE    3

#define START_LEVEL 1
int LEVEL = START_LEVEL;
unsigned char current_level = 1;
#define MAX_LEVELS  12
char MSG[256] = "";
char MENU_MSG[256] = "—”œ∆‘®√©¨†ππ";
#define MAX_SCORES 9

#define SCORE_ON_ENEMY 2
#define SCORE_ON_AIR_ENEMY 3
#define SCORE_ON_GENERATOR 4
#define SCORE_ON_POWER 5
#define SCORE_ON_LEVELNO 8

#define MAX_LAYERS 5

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

#define turpadw 17
#define turpadh 17
#define turcanw 18
#define turcanh 7
#define flyw 15
#define flyh 9
#define migw 18
#define migh 15
#define guardw 18
#define guardh 15
#define fshoew 17
#define fshoeh 8

//Enum for the options
typedef enum options{start, resume, option, hghscores, help, exitgame};
options optionmenu;

enum owner_type {PLAYER, ENEMY, AIRENEMY};

unsigned char *tank_img, *cannon_img, *bullet_img,
							*expl1, *expl2, *expl3, *expl4,
							*texpl1, *texpl2, *texpl3, *texpl4, *texpl5,
							*skey_img, *cross_img, *rocket_img, *shield_img, *fly_img,
							*turpad_img, *mig_img, *fshoe_img, *turcan_img;
int powericon = 0, poweractivated = 0,
		speedactivated = 0, speedcounter = 0;
unsigned char *start_s, *startc_s, *resume_s, *resumec_s,	*options_s,
							*optionsc_s, *help_s, *helpc_s, *exit_s, *exitc_s, *gameover_s,
							*missacco_s, *scores_s, *scoresc_s;