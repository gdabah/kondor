//This header will handle the slots..item/number/keyboard
float sheildrad = 0;
struct slot{
 int amount;
 int type;
 unsigned char *sprt;
};
class slot_type{
public:
 slot data[MAX_SLOTS];
 int slotempty(int n);
 int getslotn(int type);
 int use();
 void add(int type);
 void drawsprt(int n);
 void draw();
 void erase(int n);
};
slot_type slots;
int current_slot = 0;
void drawslotrect(int x, int y, int x2, int y2)
{
 horline(y, x +2, x2 -2);
 horline(y2, x +2, x2 -2);
 verline(x, y +2, y2 -2);
 verline(x2, y +2, y2 -2);
}
void drawslots(int color)
{
 screenis(bkg);
 setcolor(color);
 switch(current_slot)
 {
	case 0: drawslotrect(262, 70, 284, 90); break;
	case 1: drawslotrect(291, 70, 313, 90); break;
	case 2: drawslotrect(262, 100, 284, 120); break;
	case 3: drawslotrect(291, 100, 313, 120); break;
 }
 screenis(buffer);
}
int slot_type::slotempty(int n)
{
 if (slots.data[n].amount == 0) return(slots.data[n].type);
 return(-1);
}
int slot_type::getslotn(int type)
{
 for (int i = 0; i < MAX_SLOTS; i++)
	if (slots.data[i].type == type) return(i);
 return(-1);
}
void slot_type::add(int type)
{
 drawslots(0);
 for (int i = 0; i < MAX_SLOTS; i++)
	if (slots.data[i].type == type)
	{
	 slots.data[i].amount += random(BONUS_RANGE) +4;
	 if (slots.data[i].amount > 99) slots.data[i].amount = 99;
	 current_slot = i;
	 drawslots(80);
	 return;
	}
 for (i = 0; i < MAX_SLOTS; i++)
	if (slots.data[i].type == -1)
	{
	 slots.data[i].type = type;
	 slots.data[i].amount = random(BONUS_RANGE) +4;
	 if (slots.data[i].amount > 99) slots.data[i].amount = 99;
	 drawsprt(i);
	 current_slot = i;
	 drawslots(80);
	 break;
	}
}
void slot_type::drawsprt(int n)
{
 screenis(bkg);
 switch(n)
 {
	case 0:
	 drawsprite(265 +((18 -bonussprts[data[0].type].w) >> 1),
							72 +((18 -bonussprts[data[0].type].h) >> 1), bonussprts[data[0].type].w, bonussprts[data[0].type].h, bonussprts[data[0].type].sprt);
	break;
	case 1:
	 drawsprite(294 +((18 -bonussprts[data[1].type].w) >> 1),
							72 +((18 -bonussprts[data[1].type].h) >> 1), bonussprts[data[1].type].w, bonussprts[data[1].type].h, bonussprts[data[1].type].sprt);
	break;
	case 2:
	 drawsprite(265 +((18 -bonussprts[data[2].type].w) >> 1),
							102 +((18 -bonussprts[data[2].type].h) >> 1), bonussprts[data[2].type].w, bonussprts[data[2].type].h, bonussprts[data[2].type].sprt);
	break;
	case 3:
	 drawsprite(294 +((18 -bonussprts[data[3].type].w) >> 1),
							102 +((18 -bonussprts[data[3].type].h) >> 1), bonussprts[data[3].type].w, bonussprts[data[3].type].h, bonussprts[data[3].type].sprt);
	break;
 }
 screenis(buffer);
}
void slot_type::draw()
{
 setcolor(86);
 if (data[0].amount)
	drawstringreg(264, 72, data[0].amount);
 if (data[1].amount)
	drawstringreg(293, 72, data[1].amount);
 if (data[2].amount)
	drawstringreg(264, 102, data[2].amount);
 if (data[3].amount)
	drawstringreg(293, 102, data[3].amount);
}
void slot_type::erase(int n)
{
 screenis(bkg);
 setcolor(0);
 switch(n)
 {
	case 0: bar(265, 72, 265 +16, 72 +16); break;
	case 1: bar(294, 72, 294 +16, 72 +16); break;
	case 2: bar(265, 102, 265 +16, 102 +16); break;
	case 3: bar(294, 102, 294 +16, 102 +16); break;
	default: ;
 }
 screenis(buffer);
 for (int i = 0; i < MAX_SLOTS; i++)
	if (slots.data[i].amount > 0)
	{
	 drawslots(0);
	 current_slot = i;
	 drawslots(80);
	 break;
	}
}
int slot_type::use()
{
 if (data[current_slot].amount > 0)
	return(data[current_slot].type);
 return(-1);
}