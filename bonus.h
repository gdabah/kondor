//This header handles the bonuses in the game...
/*
	BONUSES TABLE
 \------------/
-1.NO HIT.
 0.ROCKET  V
 1.TURBO   V
 2.POWER   V
 3.EXTRA LIVES V
 4.SHIELD  V
*/
void setbonussprts()
{
 bonussprts[0].w = 15;
 bonussprts[0].h = 9;
 bonussprts[0].sprt = rocket_img;
 bonussprts[1].w = 17;
 bonussprts[1].h = 8;
 bonussprts[1].sprt = fshoe_img;
 bonussprts[2].w = 15;
 bonussprts[2].h = 15;
 bonussprts[2].sprt = cross_img;
 bonussprts[3].w = 16;
 bonussprts[3].h = 16;
 bonussprts[3].sprt = rock_img;
 bonussprts[4].w = 12;
 bonussprts[4].h = 13;
 bonussprts[4].sprt = shield_img;
}
boolean canuseitem = true;
void usebonus()
{
 if (canuseitem == false) return;
 canuseitem = false;
 int type = slots.use();
 if (type == -1) return;
 switch(type)
 {
	case 0:
	 if (tank.height >= 0)
	 {
		int ang = (tank.layers.ang +tank.layers.sprts[1].ang);
		bullets.add(tank.layers.x +COS(ang) *((CANNONW -CANNONCY) +(BULLETW >> 1)),
								tank.layers.y +SIN(ang) *((CANNONW -CANNONCY) +(BULLETH >> 1)),
								ang, BULLETSPD, PLAYER, 1);
		slots.data[current_slot].amount--;
		if (slots.data[current_slot].amount == 0)
		{
		 slots.data[current_slot].type = -1;
		 slots.erase(current_slot);
		}
		MixVoice(&VoiceData[3]);
	 }
	break;
	case 1:
	if (!speedactivated)
	{
	 if (speedactivated) return;
	 speedactivated = 1;
	 speedcounter = SPEEDTIME;
	 tank.maxspeed *= 2;
	 slots.data[current_slot].amount--;
	 if (slots.data[current_slot].amount == 0)
	 {
		slots.data[current_slot].type = -1;
		slots.erase(current_slot);
	 }
	}
	break;
	case 2:
	 if (tank.power >= TANK_MAX_POWER) return;
	 if (poweractivated) return;
	 poweractivated = 1;
	 if (!isplaying(&VoiceData[6])) MixVoice(&VoiceData[6]);
	 break;
	case 4:
	 if (tank.shieldhits) return;
	 slots.data[current_slot].amount--;
	 tank.shieldhits = 10 +random(MAX_SHIELD_HITS);
	 if (slots.data[current_slot].amount == 0)
	 {
		slots.data[current_slot].type = -1;
		slots.erase(current_slot);
	 }
	 if (!isplaying(&VoiceData[8])) MixVoice(&VoiceData[8]);
	break;
	default: ;
 }
}