#include <qunit.h>
void main()
{
 init320x200();
 loadbmp("gameover.bmp");
 while (!kbhit());
 save32("kondor19.dat");
 savepal("kondor20.dat");
 closegraph();
}