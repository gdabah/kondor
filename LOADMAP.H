//This header will handle with the map and all files....
char masterid = 'S';
struct loadtank_type
{
 int x, y, ang;
 double accel, turn_speed, cannon_turn_speed, maxspeed;
 unsigned int power;
};
loadtank_type loadtank;

struct loadenemy_type
{
 int x, y, ang;
 double speed, turn_speed;
 unsigned int power;
 unsigned char steps;
 pointtypei PATH[ENEMY_MAX_PATH_LENGTH];
 enemytag behavior;
};
loadenemy_type loadenemy;

struct loadobject_type{
 int x, y, type;
};
loadobject_type loadobject;

struct loadbase_type
{
 int x, y, gap, power;
};
loadbase_type loadbase;
int loadfmap(char *lfname, unsigned char **MAP)
{
 FILE *lfile;
 int en, on, bn,
		 g_index = 0, a_index = 0;
 if ((lfile = fopen(lfname, "rb")) == NULL) return(-1);
 if (fgetc(lfile) != masterid) return(2);
 fread(&LEVEL, sizeof(LEVEL), 1, lfile);
 if (current_level != LEVEL) return(2); //Oh Uh, someone tried to switch levels!
 fread(MSG, sizeof(MSG), 1, lfile);
 fread(&planesperlevel, sizeof(planesperlevel), 1, lfile);
 if (*MAP == NULL) return(0);
 fread(*MAP, MAP_W *MAP_H, 1, lfile);
 fread(&loadtank, sizeof(loadtank_type), 1, lfile);
 fread(&en, sizeof(en), 1, lfile);
 enemies.close();
 air_enemies.close();
 for (int il = 0; il <= en; il++)
 {
	fread(&loadenemy, sizeof(loadenemy_type), 1, lfile);
	if ((loadenemy.behavior != PIPER) && (loadenemy.behavior != MIG))
	{
	 memcpy(&enemies.data[g_index].path,
					loadenemy.PATH,
					sizeof(pointtypei) *ENEMY_MAX_PATH_LENGTH);
	 enemies.add(loadenemy.x, loadenemy.y, loadenemy.ang, loadenemy.speed,
							 loadenemy.turn_speed, loadenemy.power, loadenemy.steps, loadenemy.behavior);
	 g_index++;
	}
	else
	{
	 memcpy(&air_enemies.data[a_index].path,
					loadenemy.PATH,
					sizeof(pointtypei) *ENEMY_MAX_PATH_LENGTH);
	 air_enemies.add(loadenemy.x, loadenemy.y, loadenemy.ang, loadenemy.speed,
									 loadenemy.turn_speed, loadenemy.power, loadenemy.steps, loadenemy.behavior);
	 a_index++;
	}
 }
 /*for(int i = 0; i < 10; i++)
	air_enemies.add(random(MAP_PIXEL_W), random(MAP_PIXEL_H), 0, 1,
									1, 0, 1, 0, PIPER);*/
 objects.objects_no = 0;
 fread(&on, sizeof(on), 1, lfile);
 for (il = 0; il <= on; il++)
 {
	fread(&loadobject, sizeof(loadobject), 1, lfile);
	objects.add(loadobject.x, loadobject.y, loadobject.type);
 }
 bases.bases_no = 0;
 fread(&bn, sizeof(bn), 1, lfile);
 for (il = 0; il <= bn; il++)
 {
	fread(&loadbase, sizeof(loadbase), 1, lfile);
	bases.add(loadbase.x, loadbase.y, loadbase.gap, loadbase.power);
 }
 fclose(lfile);
 return(1);
}
void loadmap()
{
 char *mapfn, *str;
 mapfn = (char *)malloc(12);
 if (mapfn == NULL) memerr("Map Loading[1]");
 str = (char *)malloc(12);
 if (str == NULL) memerr("Map Loading[2]");
 strcpy(mapfn, "kondor");
 itoa(current_level, str, 10);
 strcat(mapfn, str);
 strcat(mapfn, ".map");
 int result = loadfmap(mapfn, &map);
 free(mapfn);
 free(str);
 switch (result)
 {
	case (-1):
	 filerr();
	break;
	case 2:
	 writemsg("FILE DECODING ERROR!", "");
	 closeall();
	 exit(0);
	break;
	case 0:
	 memerr("Memory For Map");
	break;
	default: ;
 }
 //TANK.
 tank.layers.close();
 tank.layers.set(loadtank.x, loadtank.y, loadtank.ang, 2);
 tank.layers.sprts[0].set(0, 0, TANKW >> 1, TANKH >> 1, 0, TANKW, TANKH, tank_img, true);
 tank.layers.sprts[1].set(0, 0, CANNONCY, CANNONH >> 1, 0, CANNONW, CANNONH, cannon_img, true);
 tank.Alpha = qrad(atan2(-tank.layers.sprts[0].h >> 1, tank.layers.sprts[0].w >> 1));
 tank.Radius = sqrt(0.25 *(tank.layers.sprts[0].w *tank.layers.sprts[0].w +(tank.layers.sprts[0].h *tank.layers.sprts[0].h)));
 tank.accel = loadtank.accel;
 tank.speed = 0;
 tank.height = 0;
 tank.halfwidth_3 = (tank.layers.sprts[0].w >> 1) +3;
 tank.turn_speed = loadtank.turn_speed;
 tank.cannon_turn_speed = loadtank.cannon_turn_speed;
 tank.maxspeed = loadtank.maxspeed;
 tank.power = /*loadtank.power*/10000;
 setminmap();
 setbonussprts();
 for (int i = 0; i < MAX_SLOTS; i++)
 {
	slots.data[i].amount = 0;
	slots.data[i].type = -1;
 }
 expls.expls_no = 0;
 bullets.bullets_no = 0;
 current_slot = 0;
 powericon = 0;
 poweractivated = 0;
 speedactivated = 0;
 speedcounter = 0;
 tank.shieldhits = 0;
 tank.shieldrad = 0;
}
void initmap()
{
 if ((map = (unsigned char *)malloc(MAP_W *MAP_H)) == NULL) memerr("Map");
}
void closemap()
{
 free(map);
}