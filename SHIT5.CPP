#include <qunit.h>
int soundfx = 1;
int showpb = 1;
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
//Save keys and info of the options menu.
void saveoptions()
{
 FILE *fs;
 if ((fs = fopen("kondor.cfg", "wb")) == NULL) return ;
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
void main()
{
 saveoptions();
}