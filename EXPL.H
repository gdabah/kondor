class expl_type
{
 public:
	int x, y, age;
	frames_type frames;
	int dead();
	void draw();
	void handle();
};
int expl_type::dead()
{
 return(age <= 0);
}
void expl_type::draw()
{
 frames.draw(x, y);
}
void expl_type::handle()
{
 age--;
 frames.frame = (EXPL_LENGTH -age) /5;
}
class expls_type
{
 public:
	int expls_no;
	expl_type data[MAX_EXPLS];
	void handle();
	void draw();
	void add(int x, int y, int age, int type);
	expls_type();
} expls;
void expls_type::handle()
{
 for (int e_index = 0; e_index < expls_no; e_index++)
 {
	if (data[e_index].dead())
	{
	 expls_no--;
	 data[e_index] = data[expls_no];
	}
	data[e_index].handle();
 }
}
void expls_type::draw()
{
 for(int e_index = 0; e_index < expls_no; e_index++)
	data[e_index].draw();
}
void expls_type::add(int x, int y, int age, int type)
{
 if (expls_no < MAX_EXPLS)
 {
	data[expls_no].x = x;
	data[expls_no].y = y;
	data[expls_no].age = age;
	data[expls_no].frames.frame = 0;
	data[expls_no].frames.maxframe = 0;
	if (type == 0)
	{
	 data[expls_no].frames.add(7, 6, expl1);
	 data[expls_no].frames.add(7, 9, expl2);
	 data[expls_no].frames.add(9, 10, expl3);
	 data[expls_no].frames.add(9, 11, expl4);
	}
	if (type == 1)
	{
	 data[expls_no].frames.add(14, 11, texpl1);
	 data[expls_no].frames.add(14, 13, texpl2);
	 data[expls_no].frames.add(16, 14, texpl3);
	 data[expls_no].frames.add(16, 16, texpl4);
	 data[expls_no].frames.add(16, 15, texpl5);
	}
	expls_no++;
 }
}
expls_type::expls_type()
{
 expls_no = 0;
}