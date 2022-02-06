#define RS 0x01000000;
#define EN 0x02000000;

void Lcd_Command(char cmd)                          
{
	IOCLR1 = 0XFF << 16;
	IOSET1 = (cmd & 0XF0) << 16;
	IOCLR1 = RS;
	IOSET1 = EN;
	delay(5);
	IOCLR1 = EN;
	
	IOCLR1 = 0XFF << 16;
	IOSET1 = ((cmd<<4) & 0XF0) << 16;
	IOCLR1 = RS;
	IOSET1 = EN;
	delay(5);
	IOCLR1 = EN;
}

void Lcd_Data(char Data)
{
	IOCLR1 = 0XFF << 16;
	IOSET1 = (Data & 0XF0) << 16;
	IOSET1 = RS;
	IOSET1 = EN;
	delay(5);
	IOCLR1 = EN;
	
	IOCLR1 = 0XFF << 16;
	IOSET1 = ((Data<<4) & 0XF0) << 16;
	IOSET1 = RS;
	IOSET1 = EN;
	delay(5);
	IOCLR1 = EN;
}

void Lcd_String(const unsigned char *Str)
{
	while(*Str)
	{
		Lcd_Data(*Str++);
	}
}

void Lcd_Intialization()
{
	Lcd_Command(0x02);
	Lcd_Command(0x28);
	Lcd_Command(0x06);
	Lcd_Command(0x0c);
}