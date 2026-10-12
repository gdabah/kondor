#include <qunit.h>
#include <ctype.h>
#define str "Mini Map"
#define FNAME "shit.cpp"
void main()
{
 ofstream fdata(FNAME);
 for (int i = 0; i < strlen(str); i++)
	fdata << (char)(toupper(str[i]) | 128);
 fdata.close();
}