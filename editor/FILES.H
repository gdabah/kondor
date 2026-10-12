//This unit handles in the files..Format...Load...Save!!!
char masterid = 'S';
void savemap(char *sfname, unsigned char *MAP)
{
 FILE *sfile;
 if ((sfile = fopen(sfname, "wb")) == NULL) return;
 fputc(masterid, sfile);
 fwrite(&LEVEL, sizeof(LEVEL), 1, sfile);
 fwrite(CAPTION, sizeof(CAPTION), 1, sfile);
 fwrite(&FLYERS, sizeof(FLYERS), 1, sfile);
 fwrite(MAP, MAP_W *MAP_H, 1, sfile);
 fwrite(&tank, sizeof(tank_type), 1, sfile);
 fwrite(&EADD, sizeof(EADD), 1, sfile);
 for (int is = 0; is <= EADD; is++)
	fwrite(&enemies[is], sizeof(enemies[is]), 1, sfile);
 fwrite(&OADD, sizeof(OADD), 1, sfile);
 for (is = 0; is <= OADD; is++)
	fwrite(&objects[is], sizeof(objects[is]), 1, sfile);
 fwrite(&BADD, sizeof(BADD), 1, sfile);
 for (int ib = 0; ib <= BADD; ib++)
	fwrite(&bases[ib], sizeof(bases[ib]), 1, sfile);
 fclose(sfile);
}
int loadmap(char *lfname, unsigned char **MAP)
{
 for (int i = 0; i < MAXOBJECTS; i++)
 {
	objects[i].x = -20;
	objects[i].y = -20;
	objects[i].type = 0;
 }
 for (i = 0; i < MAXENEMIES; i++)
 {
	enemies[i].behavior = EMPTY;
	enemies[i].x = 0;
	enemies[i].y = 0;
	enemies[i].ang = 0;
	enemies[i].speed = 0;
	enemies[i].turn_speed = 0;
	enemies[i].power = 0;
	enemies[i].steps = 0;
	for (int j = 0; j < MAXSTEPS; j++)
	{
	 enemies[i].PATH[j].x = 0;
	 enemies[i].PATH[j].y = 0;
	}
 }
 for (i = 0; i < MAXBASES; i++)
 {
	bases[i].x = -20;
	bases[i].y = -20;
	bases[i].gap = 0;
	bases[i].power = 0;
 }
 basesn = 0;
 enemiesn = 0;
 objectsn = 0;
 FILE *lfile;
 if ((lfile = fopen(lfname, "rb")) == NULL) return(0);
 if (fgetc(lfile) != masterid) return(0);
 fread(&LEVEL, sizeof(LEVEL), 1, lfile);
 fread(CAPTION, sizeof(CAPTION), 1, lfile);
 fread(&FLYERS, sizeof(FLYERS), 1, lfile);
 if (*MAP) free(*MAP);
 *MAP = (unsigned char far *) malloc(MAP_W *MAP_H);
 if (*MAP == NULL) return(0);
 fread(*MAP, MAP_W *MAP_H, 1, lfile);
 fread(&tank, sizeof(tank_type), 1, lfile);
 fread(&EADD, sizeof(EADD), 1, lfile);
 for (int il = 0; il <= EADD; il++)
	fread(&enemies[il], sizeof(enemies[il]), 1, lfile);
 fread(&OADD, sizeof(OADD), 1, lfile);
 for (il = 0; il <= OADD; il++)
	fread(&objects[il], sizeof(objects[il]), 1, lfile);
 fread(&BADD, sizeof(BADD), 1, lfile);
 for (il = 0; il <= BADD; il++)
	fread(&bases[il], sizeof(bases[il]), 1, lfile);
 fclose(lfile);
 return(1);
}