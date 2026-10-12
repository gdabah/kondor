//Greetings: by Steven H Don
/*
1 MENU
2 OPTIONS
3 SHOOT
4 ROCKET
5 EXPLOSION1
6 WATER
7 POWER BONUS
8 WALL COLLISION
9 SHIELD
10 BONUS
*/
#define WAVS 10
unsigned int CBuffer;
unsigned char far *DMABuffer;
unsigned long bytes_played = 0;
struct WaveData VoiceData[WAVS];
void interrupt (*OldIRQ)(...);
int soundfx = 1;//Is the sound off or on?
int soundblaster = 0;//Is the SB installed?
unsigned long DMAInCurrentBlock()
{
 unsigned long DMACurrent;
 DMACurrent = inportb(1 +(DMA << 1));
 DMACurrent += inportb(1 +(DMA << 1)) << 8;
 DMACurrent = 0x7fff -DMACurrent;
 DMACurrent &= 8191;
 return(DMACurrent);
}
int isplaying(struct WaveData *Voice)
{
 unsigned long current = DMAInCurrentBlock() +bytes_played;
 return(Voice->finishing > current);
}
void StartPlayBack()
{
 long LinearAddress;
 unsigned int Page, OffSet;
 WriteDSP(0xD1);
 WriteDSP(0x40);
 WriteDSP(165);
 LinearAddress = FP_SEG(DMABuffer);
 LinearAddress = (LinearAddress << 4) +FP_OFF(DMABuffer);
 Page = LinearAddress >> 16;
 OffSet = LinearAddress & 0xFFFF;
 outportb(0x0A, 4 | DMA);
 outportb(0x0C, 0);
 outportb(0x0B, 0x58 | DMA);
 outportb(DMA << 1, OffSet & 0xFF);
 outportb(DMA << 1, OffSet >> 8);
 if (DMA == 0) outportb(0x87, Page);
 if (DMA == 1) outportb(0x83, Page);
 if (DMA == 3) outportb(0x82, Page);
 outportb((DMA << 1) +1, 0xFF);
 outportb((DMA << 1) +1, 0x7F);
 outportb(0x0A, DMA);
 WriteDSP(0x48);
 WriteDSP(0xFF);
 WriteDSP(0x1F);
 WriteDSP(0x1C);
}
void ClearBuffer(unsigned int Buffer)
{
 char *Address;
 Address = (char *)MK_FP(FP_SEG(DMABuffer), FP_OFF(DMABuffer) +(Buffer << 13));
 memset(Address, 128, 8192);
}
void MixVoice(struct WaveData *Voice)
{
 if (!soundblaster) return ;
 if (!soundfx) return ;
 unsigned int Counter, OffSet, DMAPointer;
 DMAPointer = inportb(1 +(DMA << 1));
 DMAPointer = DMAPointer +(inportb(1 +(DMA << 1)) << 8);
 DMAPointer = 0x7FFF -DMAPointer;
 OffSet = DMAPointer;
 for (Counter = 0; Counter <= Voice->length; Counter++)
 {
	DMABuffer[OffSet++] += Voice->data[Counter];
	OffSet &= 0x7FFF;
 }
 Voice->finishing = bytes_played +DMAInCurrentBlock() +Voice->length;
}
void LoadVoice(struct WaveData *Voice, char *FileName)
{
 FILE *WAVFile;
 if ((WAVFile = fopen(FileName, "rb")) == NULL) filerr();
 fseek(WAVFile, 0L, SEEK_END);
 Voice->length = ftell(WAVFile) -48;
 if ((Voice->data = (unsigned char *)malloc(Voice->length +2)) == NULL) memerr("×ÁÖÓ");
 fseek(WAVFile, 46L, SEEK_SET);
 fread(Voice->data, Voice->length +2, 1, WAVFile);
 fclose(WAVFile);
}
void ConvertVoice(struct WaveData *Voice)
{
 unsigned int OffSet;
 for (OffSet = 0; OffSet <= Voice->length; OffSet++)
 {
	Voice->data[OffSet] >>= 2;
	Voice->data[OffSet] -= 32;
 }
}
void interrupt ServiceIRQ (...)
{
 inportb(Base +0xE);
 outportb(0x20, 0x20);
 if ((IRQ == 2) || (IRQ == 10) || (IRQ == 11)) outportb(0xA0, 0x20);
 ClearBuffer(CBuffer);
 CBuffer++;
 CBuffer &= 3;
 bytes_played += 8192;
}
void AssignBuffer()
{
 char *TempBuf;
 long LinearAddress;
 unsigned int Page1, Page2;
 if ((TempBuf = (char *)malloc(32768)) == NULL) memerr("ÄÍÁ ÂÕÆÆÅÒ");
 LinearAddress = FP_SEG(TempBuf);
 LinearAddress = (LinearAddress << 4) +FP_OFF(TempBuf);
 Page1 = LinearAddress >> 16;
 Page2 = (LinearAddress +32767) >> 16;
 if (Page1 != Page2)
 {
	if ((DMABuffer = (unsigned char *)malloc(32768)) == NULL) memerr("ÄÍÁ ÂÕÆÆÅÒ");
	free(TempBuf);
 }
 else DMABuffer = TempBuf;
 memset(DMABuffer, 128, 0x7FFF);
}
void interrupt (*Old71)(...);
void interrupt (*Old11)(...);
void interrupt (*Old13)(...);
void interrupt (*Old15)(...);
void interrupt (*Old72)(...);
void interrupt (*Old73)(...);
unsigned char getdma()
{
 unsigned char Before, After;
 unsigned int          Count;
 ResetDSP(Base);
 WriteDSP(0xD3);
 WriteDSP(0x40);
 WriteDSP(165);
 WriteDSP(0x14);
 WriteDSP(0x01);
 Count = 0;
 asm{
	cli
 }
 Before = inportb(0x8) &0xE0;
 WriteDSP(0x00);
 do{
	After = inportb(0x8) &0xE0;
 }while ((Before == After) && (++Count < 60000)) ;
 asm{
	sti
 }
 ResetDSP(Base);
 if (Before != After)
 {
	Count = 0;
	After ^= (Before);
	while (After > 0)
	{
	 Count++;
	 After >>= 1;
	}
	return(Count -5);
 }
 return(0xff);
}
void interrupt ServiceIRQ2(...)
{
 inportb(Base +0xE);
 outportb(0x20, 0x20);
 outportb(0xA0, 0x20);
 IRQ = 2;
}
void interrupt ServiceIRQ3(...)
{
 inportb(Base +0xE);
 outportb (0x20, 0x20);
 IRQ = 3;
}
void interrupt ServiceIRQ5(...)
{
 inportb(Base +0xE);
 outportb(0x20, 0x20);
 IRQ = 5;
}
void interrupt ServiceIRQ7(...)
{
 inportb(Base +0xE);
 outportb(0x20, 0x20);
 IRQ = 7;
}
void interrupt ServiceIRQ10(...)
{
 inportb(Base +0xE);
 outportb(0x20, 0x20);
 outportb(0xA0, 0x20);
 IRQ = 10;
}
void interrupt ServiceIRQ11(...)
{
 inportb(Base +0xE);
 outportb(0x20, 0x20);
 outportb(0xA0, 0x20);
 IRQ = 11;
}
void getirq()
{
 IRQ = 0;
 WriteDSP(0xD1);
 WriteDSP(0x40);
 WriteDSP(165);
 outportb(0x0A, 4 +DMA);
 outportb(0x0C, 0);
 outportb(0x0B, 0x49);
 outportb(1 +(DMA << 1), 0x03);
 outportb(1 +(DMA << 1), 0x00);
 outportb(0x0A, DMA);
 WriteDSP(0x14);
 WriteDSP(0x03);
 WriteDSP(0x00);
 unsigned int Count = 0;
 do
	Count++;
 while ((!IRQ) && (Count != 0xFFFF)) ;
}
void getsb()
{
 DMA = getdma();
 Old71 = getvect(0x71);
 Old11 = getvect(11);
 Old13 = getvect(13);
 Old15 = getvect(15);
 Old72 = getvect(0x72);
 Old73 = getvect(0x73);
 setvect (0x71, ServiceIRQ2);
 setvect (11, ServiceIRQ2);
 setvect (13, ServiceIRQ5);
 setvect (15, ServiceIRQ7);
 setvect (0x72, ServiceIRQ10);
 setvect (0x73, ServiceIRQ11);
 outportb (0x21, inportb(0x21) &(!(1 << 2)));
 outportb (0x21, inportb(0x21) &(!(1 << 3)));
 outportb (0x21, inportb(0x21) &(!(1 << 5)));
 outportb (0x21, inportb(0x21) &(!(1 << 7)));
 outportb (0xA1, inportb(0xA1) &(!(1 << 1)));
 outportb (0xA1, inportb(0xA1) &(!(1 << 2)));
 outportb (0xA1, inportb(0xA1) &(!(1 << 3)));
 getirq();
 setvect(0x71, Old71);
 setvect(11, Old11);
 setvect(13, Old13);
 setvect(15, Old15);
 setvect(0x72, Old72);
 setvect(0x73, Old73);
 outportb(0x21, inportb(0x21) |(1 << 2));
 outportb(0x21, inportb(0x21) |(1 << 3));
 outportb(0x21, inportb(0x21) |(1 << 5));
 outportb(0x21, inportb(0x21) |(1 << 7));
 outportb(0xA1, inportb(0xA1) |(1 << 1));
 outportb(0xA1, inportb(0xA1) |(1 << 2));
 outportb(0xA1, inportb(0xA1) |(1 << 3));
}
void initsound()
{
 LoadVoice(&VoiceData[0], "kondor7.dat"); ConvertVoice(&VoiceData[0]);
 LoadVoice(&VoiceData[1], "kondor8.dat"); ConvertVoice(&VoiceData[1]);
 LoadVoice(&VoiceData[2], "kondor9.dat"); ConvertVoice(&VoiceData[2]);
 LoadVoice(&VoiceData[3], "kondor10.dat"); ConvertVoice(&VoiceData[3]);
 LoadVoice(&VoiceData[4], "kondor11.dat"); ConvertVoice(&VoiceData[4]);
 LoadVoice(&VoiceData[5], "kondor12.dat"); ConvertVoice(&VoiceData[5]);
 LoadVoice(&VoiceData[6], "kondor13.dat"); ConvertVoice(&VoiceData[6]);
 LoadVoice(&VoiceData[7], "kondor14.dat"); ConvertVoice(&VoiceData[7]);
 LoadVoice(&VoiceData[8], "kondor15.dat"); ConvertVoice(&VoiceData[8]);
 LoadVoice(&VoiceData[9], "kondor16.dat"); ConvertVoice(&VoiceData[9]);
 AssignBuffer();
 if ((IRQ == 2) || (IRQ == 10) || (IRQ == 11))
 {
	if (IRQ == 2) OldIRQ = getvect(0x71);
	if (IRQ == 10) OldIRQ = getvect(0x72);
	if (IRQ == 11) OldIRQ = getvect(0x73);
 }
 else OldIRQ = getvect(8 +IRQ);
 if ((IRQ == 2) || (IRQ == 10) || (IRQ == 11))
 {
	if (IRQ == 2) setvect(0x71, ServiceIRQ);
	if (IRQ == 10) setvect(0x72, ServiceIRQ);
	if (IRQ == 11) setvect(0x73, ServiceIRQ);
 }
 else setvect(8 +IRQ, ServiceIRQ);
 if (IRQ == 2 || IRQ == 10 || IRQ == 11)
 {
	if (IRQ == 2) outportb(0xA1, inportb(0xA1) &253);
	if (IRQ == 10) outportb(0xA1, inportb(0xA1) &251);
	if (IRQ == 11) outportb(0xA1, inportb(0xA1) &247);
	outportb(0x21, inportb(0x21) &251);
 }
 else outportb(0x21, inportb(0x21) & !(1 << IRQ));
 CBuffer = 3;
 StartPlayBack();
}
void closesound()
{
 if ((IRQ == 2) || (IRQ == 10) || (IRQ == 11))
 {
	if (IRQ == 2) setvect(0x71, OldIRQ);
	if (IRQ == 10) setvect(0x72, OldIRQ);
	if (IRQ == 11) setvect(0x73, OldIRQ);
 }
 else setvect(8 +IRQ, OldIRQ);
 if ((IRQ == 2) || (IRQ == 10) || (IRQ == 11))
 {
	if (IRQ == 2) outportb(0xA1, inportb(0xA1) | 2);
	if (IRQ == 10) outportb(0xA1, inportb(0xA1) | 4);
	if (IRQ == 11) outportb(0xA1, inportb(0xA1) | 8);
	outportb (0x21, inportb(0x21) | 4);
 }
 else outportb(0x21, inportb(0x21) | (1 << IRQ));
 for (int i = 0; i < WAVS; i++)
	free(VoiceData[i].data);
 free(DMABuffer);
 closesb();
}