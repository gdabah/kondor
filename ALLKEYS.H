//This header has all defines of scan keys...arrange.
#define	skeyESC          0x01 //1
#define	skey1            0x02 //2
#define	skey2            0x03 //3
#define	skey3            0x04 //4
#define	skey4            0x05 //5
#define	skey5            0x06 //6
#define	skey6            0x07 //7
#define	skey7            0x08 //8
#define	skey8            0x09 //9
#define	skey9            0x0A //10
#define	skey0            0x0B //11
#define skeyMINUS        0x0C //12
#define	skeyEQUAL        0x0D //13
#define	skeyBACKSPACE    0x0E //14
#define	skeyTAB          0x0F //15
#define	skeyQ            0x10 //16
#define	skeyW            0x11 //17
#define	skeyE            0x12 //18
#define	skeyR            0x13 //19
#define	skeyT            0x14 //20
#define	skeyY            0x15 //21
#define	skeyU            0x16 //22
#define	skeyI            0x17 //23
#define	skeyO            0x18 //24
#define	skeyP            0x19 //25
#define	skeyLBRACKET     0x1A //26
#define	skeyRBRACKET     0x1B //27
#define	skeyENTER        0x1C //28
#define	skeyLEFTCTRL     0x1D //29
#define skeyA            0x1E //30
#define	skeyS            0x1F //31
#define	skeyD            0x20 //32
#define	skeyF            0x21 //33
#define	skeyG            0x22 //34
#define	skeyH            0x23 //35
#define	skeyJ            0x24 //36
#define	skeyK            0x25 //37
#define	skeyL            0x26 //38
#define	skeySEMICOLON    0x27 //39
#define	skeyTICK         0x28 //40
#define	skeyAPOSTROPHE   0x29 //41
#define	skeyLEFTSHIFT    0x2A //42
#define	skeyBACKSLASH    0x2B //43
#define	skeyZ            0x2C //44
#define	skeyX            0x2D //45
#define	skeyC            0x2E //46
#define	skeyV            0x2F //47
#define	skeyB            0x30 //48
#define	skeyN            0x31 //49
#define	skeyM            0x32 //50
#define	skeyCOMMA        0x33 //51
#define	skeyPERIOD       0x34 //52
#define	skeySLASH        0x35 //53
#define	skeyRIGHTSHIFT   0x36 //54
#define	skeyKEYPADSTAR   0x37 //55
#define	skeyLEFTALT      0x38 //56
#define	skeySPACE        0x39 //57
#define	skeyCAPSLOCK     0x3A //58
#define	skeyF1           0x3B //59
#define	skeyF2           0x3C //60
#define	skeyF3           0x3D //61
#define	skeyF4           0x3E //62
#define	skeyF5           0x3F //63
#define	skeyF6           0x40 //64
#define	skeyF7           0x41 //65
#define	skeyF8           0x42 //66
#define	skeyF9           0x43 //67
#define	skeyF10          0x44 //68
#define	skeyNUMLOCK      0x45 //69
#define	skeySCROLLLOCK   0x46 //70
#define	skeyKEYPAD7      0x47 //71
#define	skeyKEYPAD8      0x48 //72
#define	skeyKEYPAD9      0x49 //73
#define	skeyKEYPADMINUS  0x4A //74
#define	skeyKEYPAD4      0x4B //75
#define	skeyKEYPAD5      0x4C //76
#define	skeyKEYPAD6      0x4D //77
#define	skeyKEYPADPLUS   0x4E //78
#define	skeyKEYPAD1      0x4F //79
#define	skeyKEYPAD2      0x50 //80
#define	skeyKEYPAD3      0x51 //81
#define	skeyKEYPAD0      0x52 //82
#define	skeyKEYPADDEL    0x53 //83
#define	skeySYSREQ       0x54 //84
#define	skeyF11          0x57 //87
#define	skeyF12          0x58 //88
#define	skeyKEYPADENTER  0x9C //156
#define	skeyRIGHTCTRL    0x9D //157
#define	skeyKEYPADSLASH  0xB5 //181
#define	skeyRIGHTALT     0xB8 //184
#define	skeyCTRLPRTSC    0xB7 //183 //Twice!!
#define	skeySHIFTPRTSC   0xB7 //183
#define	skeyHOME         0xC7 //199
#define	skeyUARROW       0xC8 //200
#define	skeyPGUP         0xC9 //201
#define	skeyLARROW       0xCB //203
#define	skeyRARROW       0xCD //205
#define	skeyEND          0xCF //207
#define	skeyDARROW       0xD0 //208
#define	skeyPGDN         0xD1 //209
#define	skeyINS          0xD2 //210
#define	skeyDEL          0xD3 //211
char *getkeyname(int keyn)
{
 switch(keyn)
 {
	case 1: return("ESCAPE");
	case 2: return("1");
	case 3: return("2");
	case 4: return("3");
	case 5: return("4");
	case 6: return("5");
	case 7: return("6");
	case 8: return("7");
	case 9: return("8");
	case 10: return("9");
	case 11: return("0");
	case 12: return("-");
	case 13: return("=");
	case 14: return("BACKSPACE");
	case 15: return("TAB");
	case 16: return("Q");
	case 17: return("W");
	case 18: return("E");
	case 19: return("R");
	case 20: return("T");
	case 21: return("Y");
	case 22: return("U");
	case 23: return("I");
	case 24: return("O");
	case 25: return("P");
	case 26: return("[");
	case 27: return("]");
	case 28: return("ENTER");
	case 29: return("LEFT CONTROL");
	case 30: return("A");
	case 31: return("S");
	case 32: return("D");
	case 33: return("F");
	case 34: return("G");
	case 35: return("H");
	case 36: return("J");
	case 37: return("K");
	case 38: return("L");
	case 39: return(";");
	case 40: return("'");
	case 41: return("`");
	case 42: return("LEFT SHIFT");
	case 43: return("\\");
	case 44: return("Z");
	case 45: return("X");
	case 46: return("C");
	case 47: return("V");
	case 48: return("B");
	case 49: return("N");
	case 50: return("M");
	case 51: return(",");
	case 52: return(".");
	case 53: return("/");
	case 54: return("RIGHT SHIFT");
	case 55: return("KEYPAD *");
	case 56: return("LEFT ALT");
	case 57: return("SPACEBAR");
	case 58: return("CAPS LOCK");
	case 59: return("F1");
	case 60: return("F2");
	case 61: return("F3");
	case 62: return("F4");
	case 63: return("F5");
	case 64: return("F6");
	case 65: return("F7");
	case 66: return("F8");
	case 67: return("F9");
	case 68: return("F10");
	case 69: return("NUM LOCK");
	case 70: return("SCROLL LOCK");
	case 71: return("KEYPAD 7");
	case 72: return("KEYPAD 8");
	case 73: return("KEYPAD 9");
	case 74: return("KEYPAD -");
	case 75: return("KEYPAD 4");
	case 76: return("KEYPAD 5");
	case 77: return("KEYPAD 6");
	case 78: return("KEYPAD +");
	case 79: return("KEYPAD 1");
	case 80: return("KEYPAD 2");
	case 81: return("KEYPAD 3");
	case 82: return("KEYPAD 0");
	case 83: return("KEYPAD DEL");
	case 84: return("SYSREQ"); //From here the numbers are greater.
	case 87: return("F11");
	case 88: return("F12");
	case 156: return("KEYPAD ENTER");
	case 157: return("RIGHT CONTROL");
	case 181: return("KEYPAD /");
	case 184: return("RIGHT ALT");
	case 183: return("CTRL PRINT SCREEN");
	case 199: return("HOME");
	case 200: return("UP ARROW");
	case 201: return("PAGE UP");
	case 203: return("LEFT ARROW");
	case 205: return("RIGHT ARROW");
	case 207: return("END");
	case 208: return("DOWN ARROW");
	case 209: return("PAGE DOWN");
	case 210: return("INSERT");
	case 211: return("DELETE");
 }
 char stringn[256];
 itoa(keyn, stringn, 10);
 return(stringn);
}
char skey2char(int keyn)
{
 switch(keyn)
 {
	case 2: return('1');
	case 3: return('2');
	case 4: return('3');
	case 5: return('4');
	case 6: return('5');
	case 7: return('6');
	case 8: return('7');
	case 9: return('8');
	case 10: return('9');
	case 11: return('0');
	case 12: return('-');
	case 13: return('=');
	case 16: return('Q');
	case 17: return('W');
	case 18: return('E');
	case 19: return('R');
	case 20: return('T');
	case 21: return('Y');
	case 22: return('U');
	case 23: return('I');
	case 24: return('O');
	case 25: return('P');
	case 26: return('[');
	case 27: return(']');
	case 30: return('A');
	case 31: return('S');
	case 32: return('D');
	case 33: return('F');
	case 34: return('G');
	case 35: return('H');
	case 36: return('J');
	case 37: return('K');
	case 38: return('L');
	case 39: return(':');
	case 40: return(char(39));
	case 41: return('`');
	case 43: return('\\');
	case 44: return('Z');
	case 45: return('X');
	case 46: return('C');
	case 47: return('V');
	case 48: return('B');
	case 49: return('N');
	case 50: return('M');
	case 51: return(',');
	case 52: return('.');
	case 53: return('/');
	case 57: return(' ');
	default: return('\0');
 }
}