/*	jmah002_project_file.c
 *	Name & E-mail:  Jeremy Mah - jmah002@ucr.edu
 *	CS Login: jmah002
 *	Partner(s) Name & E-mail:Miguel Vasquez - mvasq007@ucr.edu
 *	Lab Section: 22
 *	Assignment: Final Project
 *	Exercise Description: Tank Wars
 *
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <bit.h>
#include <timer.h>
#define LOW 0
#define HIGH 1
#define INPUT 0
#define OUTPUT 1

unsigned char gridarr[127];
unsigned char special = 0;
unsigned char specialcount = 2;
typedef struct _task {
	/*Tasks should have members that include: state, period,
		a measurement of elapsed time, and a function pointer.*/
	signed char state; //Task's current state
	unsigned long int period; //Task period
	unsigned long int elapsedTime; //Time elapsed since last task tick
	int (*TickFct)(int); //Task tick function
} task;


void digitalWrite(unsigned char pin, unsigned char value){
	unsigned char writeValue = 0;
	if(value != 0){
		writeValue = 1;
	}

	switch(pin){
	case 1:
		PORTB = (PORTB & ~(1 << 0)) | (writeValue << 0);
		break;
	case 2:
		PORTB = (PORTB & ~(1 << 1)) | (writeValue << 1);
		break;
	case 3:
		PORTB = (PORTB & ~(1 << 2)) | (writeValue << 2);
		break;
	case 4:
		PORTB = (PORTB & ~(1 << 3)) | (writeValue << 3);
		break;
	case 5:
		PORTB = (PORTB & ~(1 << 4)) | (writeValue << 4);
		break;
	case 6:
		PORTB = (PORTB & ~(1 << 5)) | (writeValue << 5);
		break;
	case 7:
		PORTB = (PORTB & ~(1 << 6)) | (writeValue << 6);
		break;
	case 8:
		PORTB = (PORTB & ~(1 << 7)) | (writeValue << 7);
		break;
	case 14:
		PORTD = (PORTD & ~(1 << 0)) | (writeValue << 0);
		break;
	case 15:
		PORTD = (PORTD & ~(1 << 1)) | (writeValue << 1);
		break;
	case 16:
		PORTD = (PORTD & ~(1 << 2)) | (writeValue << 2);
		break;
	case 17:
		PORTD = (PORTD & ~(1 << 3)) | (writeValue << 3);
		break;
	case 18:
		PORTD = (PORTD & ~(1 << 4)) | (writeValue << 4);
		break;
	case 19:
		PORTD = (PORTD & ~(1 << 5)) | (writeValue << 5);
		break;
	case 20:
		PORTD = (PORTD & ~(1 << 6)) | (writeValue << 6);
		break;
	case 21:
		PORTD = (PORTD & ~(1 << 7)) | (writeValue << 7);
		break;
	case 22:
		PORTC = (PORTC & ~(1 << 0)) | (writeValue << 0);
		break;
	case 23:
		PORTC = (PORTC & ~(1 << 1)) | (writeValue << 1);
		break;
	case 24:
		PORTC = (PORTC & ~(1 << 2)) | (writeValue << 2);
		break;
	case 25:
		PORTC = (PORTC & ~(1 << 3)) | (writeValue << 3);
		break;
	case 26:
		PORTC = (PORTC & ~(1 << 4)) | (writeValue << 4);
		break;
	case 27:
		PORTC = (PORTC & ~(1 << 5)) | (writeValue << 5);
		break;
	case 28:
		PORTC = (PORTC & ~(1 << 6)) | (writeValue << 6);
		break;
	case 29:
		PORTC = (PORTC & ~(1 << 7)) | (writeValue << 7);
		break;
	case 33:
		PORTA = (PORTA & ~(1 << 7)) | (writeValue << 7);
		break;
	case 34:
		PORTA = (PORTA & ~(1 << 6)) | (writeValue << 6);
		break;
	case 35:
		PORTA = (PORTA & ~(1 << 5)) | (writeValue << 5);
		break;
	case 36:
		PORTA = (PORTA & ~(1 << 4)) | (writeValue << 4);
		break;
	case 37:
		PORTA = (PORTA & ~(1 << 3)) | (writeValue << 3);
		break;
	case 38:
		PORTA = (PORTA & ~(1 << 2)) | (writeValue << 2);
		break;
	case 39:
		PORTA = (PORTA & ~(1 << 1)) | (writeValue << 1);
		break;
	case 40:
		PORTA = (PORTA & ~(1 << 0)) | (writeValue << 0);
		break;
	default:
		/* Bad pin number, insert error message here. */
		break;
	}	
}

void pinMode(unsigned char pin, unsigned char value){
	unsigned char writeValue = 0;
	if(value == OUTPUT){
		writeValue = 1;
	}
	else if(value == INPUT){
		writeValue = 0;
	}

	switch(pin){
	case 1:
		DDRB = (DDRB & ~(1 << 0)) | (writeValue << 0);
		break;
	case 2:
		DDRB = (DDRB & ~(1 << 1)) | (writeValue << 1);
		break;
	case 3:
		DDRB = (DDRB & ~(1 << 2)) | (writeValue << 2);
		break;
	case 4:
		DDRB = (DDRB & ~(1 << 3)) | (writeValue << 3);
		break;
	case 5:
		DDRB = (DDRB & ~(1 << 4)) | (writeValue << 4);
		break;
	case 6:
		DDRB = (DDRB & ~(1 << 5)) | (writeValue << 5);
		break;
	case 7:
		DDRB = (DDRB & ~(1 << 6)) | (writeValue << 6);
		break;
	case 8:
		DDRB = (DDRB & ~(1 << 7)) | (writeValue << 7);
		break;
	case 14:
		DDRD = (DDRD & ~(1 << 0)) | (writeValue << 0);
		break;
	case 15:
		DDRD = (DDRD & ~(1 << 1)) | (writeValue << 1);
		break;
	case 16:
		DDRD = (DDRD & ~(1 << 2)) | (writeValue << 2);
		break;
	case 17:
		DDRD = (DDRD & ~(1 << 3)) | (writeValue << 3);
		break;
	case 18:
		DDRD = (DDRD & ~(1 << 4)) | (writeValue << 4);
		break;
	case 19:
		DDRD = (DDRD & ~(1 << 5)) | (writeValue << 5);
		break;
	case 20:
		DDRD = (DDRD & ~(1 << 6)) | (writeValue << 6);
		break;
	case 21:
		DDRD = (DDRD & ~(1 << 7)) | (writeValue << 7);
		break;
	case 22:
		DDRC = (DDRC & ~(1 << 0)) | (writeValue << 0);
		break;
	case 23:
		DDRC = (DDRC & ~(1 << 1)) | (writeValue << 1);
		break;
	case 24:
		DDRC = (DDRC & ~(1 << 2)) | (writeValue << 2);
		break;
	case 25:
		DDRC = (DDRC & ~(1 << 3)) | (writeValue << 3);
		break;
	case 26:
		DDRC = (DDRC & ~(1 << 4)) | (writeValue << 4);
		break;
	case 27:
		DDRC = (DDRC & ~(1 << 5)) | (writeValue << 5);
		break;
	case 28:
		DDRC = (DDRC & ~(1 << 6)) | (writeValue << 6);
		break;
	case 29:
		DDRC = (DDRC & ~(1 << 7)) | (writeValue << 7);
		break;
	case 33:
		DDRA = (DDRA & ~(1 << 7)) | (writeValue << 7);
		break;
	case 34:
		DDRA = (DDRA & ~(1 << 6)) | (writeValue << 6);
		break;
	case 35:
		DDRA = (DDRA & ~(1 << 5)) | (writeValue << 5);
		break;
	case 36:
		DDRA = (DDRA & ~(1 << 4)) | (writeValue << 4);
		break;
	case 37:
		DDRA = (DDRA & ~(1 << 3)) | (writeValue << 3);
		break;
	case 38:
		DDRA = (DDRA & ~(1 << 2)) | (writeValue << 2);
		break;
	case 39:
		DDRA = (DDRA & ~(1 << 1)) | (writeValue << 1);
		break;
	case 40:
		DDRA = (DDRA & ~(1 << 0)) | (writeValue << 0);
		break;
	default:
		/* Bad pin number, insert error message here. */
		break;
	}	
}

void dataIn(unsigned char datapin , unsigned char clockpin, unsigned char value) // put data into pin
{
	short num;
	for (unsigned char i = 0; i < 8; i++)
	{
		num = (value >> i) & (0x01) ;
		dataIn1 ( datapin, clockpin, num);
	
	}

}  
void dataIn1(unsigned char datapin , unsigned char clockpin, unsigned char value)
{

	digitalWrite(datapin,  value);
	digitalWrite(clockpin, 1);
	digitalWrite(clockpin, 0);
	

}

unsigned char GetKeypadKey() {

	PORTC = 0xEF; // Enable col 4 with 0, disable others with 1’s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
if (GetBit(PINC,0)==0) { return('D'); }
	if (GetBit(PINC,1)==0) { return('C'); }
	if (GetBit(PINC,2)==0) { return('B'); }
	if (GetBit(PINC,3)==0) { return('A'); }

	// Check keys in col 2
	PORTC = 0xDF; // Enable col 5 with 0, disable others with 1’s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('#'); }
	if (GetBit(PINC,1)==0) { return('9'); }
	if (GetBit(PINC,2)==0) { return('6'); }
	if (GetBit(PINC,3)==0) { return('3'); }

	// Check keys in col 3
	PORTC = 0xBF; // Enable col 6 with 0, disable others with 1’s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('0'); }
	if (GetBit(PINC,1)==0) { return('8'); }
	if (GetBit(PINC,2)==0) { return('5'); }
	if (GetBit(PINC,3)==0) { return('2'); }

	// Check keys in col 4	
	// ... *****FINISH*****
	PORTC = 0x7F; // Enable col 7 with 0, disable others with 1’s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('*'); }
	if (GetBit(PINC,1)==0) { return('7'); }
	if (GetBit(PINC,2)==0) { return('4'); }
	if (GetBit(PINC,3)==0) { return('1'); }

	return('\0'); // default value

}
unsigned char gameover = 0; // 1 = over
//=========================LCD SCREEN==============================

//********* LCD interface synchSM *********************************************

// Define LCD port assignments here so easier to change than if hardcoded below
unsigned char *LCD_Data = &PORTD;	// LCD 8-bit data bus
unsigned char *LCD_Ctrl = &PORTA;	// LCD needs 2-bits for control, use port B
const unsigned char LCD_RS = 0;		// LCD Reset pin is PB3
const unsigned char LCD_E = 1;		// LCD Enable pin is PB4

unsigned char LCD_rdy_g = 0; // Set by LCD interface synchSM, ready to display new string
unsigned char LCD_go_g = 0; // Set by user synchSM wishing to display string in LCD_string_g
unsigned char LCD_string_g[17]; // Filled by user synchSM, 16 chars plus end-of-string char



void LCD_WriteCmdStart(unsigned char cmd) {
	*LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_RS, 0);
	*LCD_Data = cmd;
	*LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_E, 1);
}
void LCD_WriteCmdEnd() {
	*LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_E, 0);
}
void LCD_WriteDataStart(unsigned char Data) {
	*LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_RS,1);
	*LCD_Data = Data;
	*LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_E, 1);
}
void LCD_WriteDataEnd() {
	*LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_E, 0);
}
void LCD_Cursor(unsigned char column ) {
	if ( column < 16 ) { // IEEE change this value to 16
	LCD_WriteCmdStart(0x80+column);
}
else {
	LCD_WriteCmdStart(0xBF+column); // IEEE change this value to 0xBF+column
}
}

enum LI_States { LI_Init1, LI_Init2, LI_Init3, LI_Init4, LI_Init5, LI_Init6,
	LI_WaitDisplayString, LI_Clr, LI_PositionCursor, LI_DisplayChar, LI_WaitGo0 } LI_State;
unsigned char asd = 26;
int hard = 0;
void LI_Tick() {
	
	static unsigned char i;
	switch(LI_State) { // Transitions
		case -1:
			LI_State = LI_Init1;
			break;
		case LI_Init1:
			LI_State = LI_Init2;
			i=0;
			break;
		case LI_Init2:
			if (i<10) { // Wait 100 ms after power up
				LI_State = LI_Init2;
			}
			else {
				LI_State = LI_Init3;
			}
			break;
		case LI_Init3:
			LI_State = LI_Init4;
			LCD_WriteCmdEnd();
			break;
		case LI_Init4:
			LI_State = LI_Init5;
			LCD_WriteCmdEnd();
			break;
		case LI_Init5:
			LI_State = LI_Init6;
			LCD_WriteCmdEnd();
			break;
		case LI_Init6:
			LI_State = LI_WaitDisplayString;
			LCD_WriteCmdEnd();
			break;
		//////////////////////////////////////////////
		case LI_WaitDisplayString:
			if (!LCD_go_g) {
				LI_State = LI_WaitDisplayString;
			}
			else if (LCD_go_g) {
			 LCD_rdy_g = 0;
				LI_State = LI_Clr;
			}
			break;
		case LI_Clr:
			LI_State = LI_PositionCursor;
			LCD_WriteCmdEnd();
			i=0;
			break;
		case LI_PositionCursor:
			LI_State = LI_DisplayChar;
			LCD_WriteCmdEnd();
			break;
		case LI_DisplayChar:
			if (i<16) {
				LI_State = LI_PositionCursor;
				LCD_WriteDataEnd();
			i++;
			}
			else {
				LI_State = LI_WaitGo0;
				LCD_WriteDataEnd();
			}
			break;
		case LI_WaitGo0:
			if (!LCD_go_g) {
				LI_State = LI_WaitDisplayString;
			}
			else if (LCD_go_g) {
				LI_State = LI_WaitGo0;
			}
			break;
		default:
			LI_State = LI_Init1;
		} // Transitions

	switch(LI_State) { // State actions
		case LI_Init1:
		 LCD_rdy_g = 0;
			break;
		case LI_Init2:
			i++; // Waiting after power up
			break;
		case LI_Init3:
			LCD_WriteCmdStart(0x38);
			break;
		case LI_Init4:
			LCD_WriteCmdStart(0x06);
			break;
		case LI_Init5:
			LCD_WriteCmdStart(0x0F);
			break;
		case LI_Init6:
			LCD_WriteCmdStart(0x01); // Clear
			break;
		//////////////////////////////////////////////
		case LI_WaitDisplayString:
			LCD_rdy_g = 1;
			break;
		case LI_Clr:
			LCD_WriteCmdStart(0x01);
			break;
		case LI_PositionCursor:
			LCD_Cursor(i);			
			break;
		case LI_DisplayChar:
			LCD_WriteDataStart(LCD_string_g[i]);
			break;
		case LI_WaitGo0:
			break;
		default:
			break;
	} // State actions
	return LI_State;
}
//--------END LCD interface synchSM------------------------------------------------


// SynchSM for testing the LCD interface -- waits for button press, fills LCD with repeated random num
unsigned char msg [] = "     Press 1 or 2 to select difficulty.   ";
unsigned char mag1[] = "Press 3 to start";
unsigned char mag2[] = "Reset to play.  ";
unsigned char mag [] = "Game in Progress.";
unsigned char display = 1;
enum LT_States { LT_s0, LT_WaitLcdRdy, LT_WaitButton, LT_FillAndDispString,
LT_HoldGo1, LT_WaitBtnRelease,LT_1 } LT_State;

void LT_Tick() {
	static unsigned short j;
	static unsigned char i, x, c;
	
	switch(LT_State) { // Transitions
		case -1:
			LT_State = LT_s0;
			break;
		case LT_s0:
			LT_State = LT_WaitLcdRdy;
			break;
		case LT_WaitLcdRdy:
			if (!LCD_rdy_g) {
				LT_State = LT_WaitLcdRdy;
			}
			else if (LCD_rdy_g) {
				LT_State = LT_WaitButton;
			}
			break;
		case LT_WaitButton:
				
				LT_State = LT_FillAndDispString;
			
			break;
		case LT_FillAndDispString:
			LT_State = LT_HoldGo1;
			break;
		case LT_HoldGo1:
			LCD_go_g=0;
		 	LT_State = LT_WaitBtnRelease;
			break;
		case LT_WaitBtnRelease:
			LT_State = LT_WaitLcdRdy;
			break;
		default:
			LT_State = LT_s0;
		} // Transitions

	switch(LT_State) { // State actions
		case LT_s0:
			LCD_go_g=0;
			//strcpy(LCD_string_g, "1234567890123456"); // Init, but never seen, shows use of strcpy though
			break;
		case LT_WaitLcdRdy:
			break;
		case LT_WaitButton:
			break;
		case LT_FillAndDispString:
		  if (display == 1)
		  {
			for (i=0; i<16; i++) { // Fill string with c
				LCD_string_g[i] = msg[i+x];
			}
			x++;
			if(x > asd){
				x = 0; //reset x
			}
			LCD_string_g[i] = '\0'; // End-of-string char
			LCD_go_g = 1; // Display string
			
		  }	
		 else if( display == 2)
		  	{
				  for (i=0; i<16; i++) { // Fill string with c
				  LCD_string_g[i] = mag[i];
					 }
			  
			  
			  LCD_string_g[i] = '\0'; // End-of-string char
			  LCD_go_g = 1; // Display string
			  
		  
			  }
		else if( display == 3)
				 {
					 for (i=0; i<16; i++) { // Fill string with c
					 LCD_string_g[i] = mag1[i];
				 }
 
 
				 LCD_string_g[i] = '\0'; // End-of-string char
				 LCD_go_g = 1; // Display string
 
 
							  }	
		else if( display == 4)
				 {
					for (i=0; i<16; i++) { // Fill string with c
					LCD_string_g[i] = mag2[i];
				}
				
				LCD_string_g[i] = '\0'; // End-of-string char
				LCD_go_g = 1; // Display string
 
 
							  }				  
		break;	
		case LT_HoldGo1:
			break;
		case LT_WaitBtnRelease:
			break;
		default:
			break;
	} // State actions
	return LT_State;
}
//--------END LCD interface synchSM------------------------------------------------

enum Move_States { Begin, Start, Move_wait, Move_up, Move_down, Move_left, Move_right, Move_wRelease,gg  } Move_State;  // user/game interface
unsigned char restart = 0;
unsigned char WoL= 0; // 0 = lose 1 = win
 unsigned char seed = 50;
 unsigned char bullettouch = 0; // 1 when 2 bullets collide.
 int i1 = 1;
 int r = 1;
 int xpos = 0;
 int ypos = 0;
 short prevState = 0;
 short up = 1;
 short down = 2;
 short left = 3;
 short right = 4;
 int tick = 0;
 unsigned char 	exminus = 128;
 unsigned char 		enr = 128;
int				enemyxpos = 15;
 unsigned char 		enemyypos = 7;
 unsigned char 		enemyPrevState = 0;

 unsigned char tick1 = 0;

 //shooting variables
 	int temp = 0;
 	int temp1 = 0;
 	int shootR = 0;
 	int sypos = 0; 
	int enemytemp = 10;
 	int enemytemp1 = 0;
 	int enemyshootR = 0;
 	int enemysypos= 10;
	 	unsigned char stillshootingup = 0;
	 	unsigned char stillshootingdown = 0;
	 	unsigned char stillshootingleft = 0;
	 	unsigned char stillshootingright = 0;
		unsigned char estillshootingup = 0;
		unsigned char estillshootingdown = 0;
		unsigned char estillshootingleft = 0;
		unsigned char estillshootingright = 0;	 
void Moving(){
		
		static unsigned char  c;
		

switch( Move_State)  {
	
	  // Transitions
		case Begin:
				 gameover = 0; 
				 WoL = 0;
					c = GetKeypadKey();
					if ( GetKeypadKey() == '1')
					{
						hard = 1;
						display = 3;
					}
					else if (GetKeypadKey() == '2')
					{
						display = 3;
						hard = 0;
					}
					if (GetKeypadKey() == '3') {
						display = 2;
						Move_State = Start;
					}
					
					break;
			case Start:

			
					Move_State = Move_wait;
					
						
				break;
			case Move_wait:
			bullettouch1();
				c = GetKeypadKey();
				if (enemyxpos == xpos && enemyypos == ypos)
				{
					 // gg hetouched you		
						Move_State = gg;
						speaker();

				}
				else if (enemyxpos == temp && enemyypos == sypos)
				{
					// gg HEGOTSHOT 
					
						Move_State = gg;  
						speaker();
						WoL = 1;
							
				}
				else if (xpos == enemytemp && ypos == enemysypos )
				{
						// gg YOUGOTSHOT
									
					Move_State = gg;
					speaker();
					WoL = 0;
									
				}
				else if (bullettouch == 1)
				{//bullets touched
					 	 temp = 0;
					 	 temp1 = 0;
						shootR = 0;
					 	 sypos = 0;
					 	 enemytemp = 0;
					 	 enemytemp1 = 0;
						 enemyshootR = 0;
					 	 enemysypos = 0;
						 estillshootingup = 0;
						estillshootingdown = 0;
						 estillshootingleft = 0;
						 estillshootingright = 0;
						 stillshootingup = 0;
						stillshootingdown = 0;
						 stillshootingleft = 0;
						 stillshootingright = 0;
						 speaker();
				}
										
						
					else if (GetKeypadKey() == '\0') 
						{
							Move_State = Move_wait;
							seed = seed +1;
						}
					
					else if(c == '6')  // Button active low
					{
						Move_State = Move_up;
						seed = seed + 50;
					}
								
					else if(c == 'B')  // Button active low
					{
						Move_State = Move_down;
					}
					
					else if(c == 'A')  // Button active low
					{
						Move_State = Move_right;
						seed = seed - 24;
					}
					
					else if(c == 'C')  // Button active low
					{
						Move_State = Move_left;
						seed = seed - 7;
					}

							
				break;
			
			case Move_up:
				Move_State = Move_wRelease;
				break;
			case Move_down:
				Move_State = Move_wRelease;
				break;
			case Move_right:
				Move_State = Move_wRelease;
				break;
			case Move_left:
				Move_State = Move_wRelease;
				break;
			case gg:
				if (GetKeypadKey() =='7')
				{
					display = 1;
					restart = 1;
					Move_State = Begin;
					
				}
				else
				{
					//speaker();
					display = 4;
					Move_State = gg;
				}
				break;
				
			case Move_wRelease:
				if (enemyxpos == xpos && enemyypos == ypos)
				{
					 // gg hetouched you
					speaker();
						Move_State = gg;				
					
				}
				else if (enemyxpos == temp && enemyypos == sypos)
					{
						 // gg HEGOTSHOT
						speaker();	
						Move_State = gg;
						WoL = 1;										
					}
								
				
				else if (GetKeypadKey() == '\0')  // Wait for button release
					Move_State = Move_wait;
				
				else 
					Move_State = Move_wRelease;
				
				break;		
				
	 
  }

			
		

		
	switch(Move_State)  {// State actions
				case Start: 
					createarray();
					map();
					i1 = 1;
					r = 1;
					xpos = 0;
					ypos = 0;
					prevState = 0;
					up = 1;
					down = 2;
					left = 3;
					right = 4;
					tick = 0;
					prevState = up;
					digitalWrite(1, 0);
					digitalWrite(3, 0);
					digitalWrite(2, 0);
					dataIn(1,3,255);
					dataIn(1,3,255);
					dataIn(1,3,255);
					dataIn(1,3,255);
					dataIn(1,3,255);
					dataIn(1,3,254);
					dataIn(1,3,1);
					digitalWrite(2, 1);
					
	
					break;
			
			case Move_up:
	
			if (xpos < 15)
			{	
				unsigned char graphpos = (ypos * 16) + (xpos + 1);
				if (gridarr[graphpos] == 1)// if  the spot above current position is lit(wall)
				{
					prevState = up;
					break;
				}
				xpos ++;
				i1 = i1 * 2;
	
				if (i1 == 256 )
				{
					i1 = 1;
				}

			}		
				prevState = up;
				break;
			case Move_down:
			
	
				if (xpos > 0)
				{
					unsigned char graphpos = (ypos * 16) + (xpos - 1);
					if (gridarr[graphpos] == 1)// if  the spot below current position is lit(wall)
					{
						prevState = down;
						break;
					}
					if (i1 == 1 && xpos > 1)
						{
							i1 = 256;
						}
						
					xpos --;
					i1 = i1 / 2;
					
				}
			prevState = down;
				break;
			case Move_right:
	
					if (ypos > 0)
					{
						unsigned char graphpos = ((ypos-1) * 16) + (xpos);
						if (gridarr[graphpos] == 1)// if  the spot right of current position is lit(wall)
						{
							prevState = right;
							break;
						}
						ypos --;
						r = r / 2;

						}
						prevState = right;
				break;
			case Move_left:
						if (ypos < 7)
						{
							unsigned char graphpos = ((ypos+1) * 16) + (xpos);
							if (gridarr[graphpos] == 1)// if  the spot below current position is lit(wall)
							{
								 prevState = left;
								break;
							}						
						
							ypos ++;
							r = r * 2;

						   }	
						   prevState = left;		
				break;
			
			case Move_wRelease:
					map ();
					// ME ----------------
					digitalWrite(4, 0);
					digitalWrite(3, 0);
					digitalWrite(2, 0);
					dataIn(1,3,255);
					dataIn(1,3,255);
					dataIn(1,3,255);
					dataIn(1,3,255);
	
			
					if (xpos < 8)
					{
						dataIn(1,3,255);
						dataIn(1,3,255 - i1);
					}
					else
					{
						dataIn(1,3,255 - i1);
						dataIn(1,3,255);
					}
					dataIn(1,3,r);
					digitalWrite(2, 1);
					// draw enemy location------
					digitalWrite(4, 0);
					digitalWrite(3, 0);
					digitalWrite(2, 0);
					dataIn(1,3,255);
					dataIn(1,3,255);

			
			
					if (enemyxpos < 8)
					{
						dataIn(1,3,255 );
				
						dataIn(1,3,255 - exminus);
					}
					else
					{
						dataIn(1,3,255- exminus);
						dataIn(1,3,255 );

					}
					dataIn(1,3,255);
					dataIn(1,3,255);
					dataIn(1,3,enr);
					// MY BULLETS ..================================================================================
					if (special == 1)
					{
						digitalWrite(2, 1);
						digitalWrite(4, 0);
						digitalWrite(3, 0);
						digitalWrite(2, 0);
						
						if (temp < 8)
						{
							dataIn(1,3,255);
							dataIn(1,3,255 - temp1);
							dataIn(1,3,255);
							dataIn(1,3,255 - temp1);
							dataIn(1,3,255);
							dataIn(1,3,255 );
						}
						else
						{
							dataIn(1,3,255- temp1 );
							dataIn(1,3,255);
							dataIn(1,3,255- temp1 );
							dataIn(1,3,255);
							dataIn(1,3,255 );
							dataIn(1,3,255);
						}
						dataIn(1,3,shootR);
						digitalWrite(2, 1);
					}
					else
					{
							digitalWrite(2, 1);
							digitalWrite(4, 0);
							digitalWrite(3, 0);
							digitalWrite(2, 0);
		
							if (temp < 8)
							{
								dataIn(1,3,255);
								dataIn(1,3,255);
								dataIn(1,3,255);
								dataIn(1,3,255 - temp1);
								dataIn(1,3,255);
								dataIn(1,3,255 - temp1 );
							}
							else
							{
								dataIn(1,3,255);
								dataIn(1,3,255);
								dataIn(1,3,255- temp1 );
								dataIn(1,3,255);
								dataIn(1,3,255 - temp1  );
								dataIn(1,3,255);
							}
							dataIn(1,3,shootR);
							digitalWrite(2, 1);
					}
						
						// ENEMY BULLETS================================================================================
						digitalWrite(4, 0);
						digitalWrite(3, 0);
						digitalWrite(2, 0);
											
						if (enemytemp < 8)
						{
							dataIn(1,3,255);
							dataIn(1,3,255);
							dataIn(1,3,255);
							dataIn(1,3,255 - enemytemp1);
							dataIn(1,3,255);
							dataIn(1,3,255 - enemytemp1 );
						}
						else
						{
							dataIn(1,3,255);
							dataIn(1,3,255);
							dataIn(1,3,255- enemytemp1 );
							dataIn(1,3,255);
							dataIn(1,3,255 - enemytemp1  );
							dataIn(1,3,255);
						}
						dataIn(1,3,enemyshootR);
					digitalWrite(2, 1);
									
			LEDbar();
				
					break;
			case Move_wait:
				map ();
			LEDbar();
				digitalWrite(4, 0);
				digitalWrite(3, 0);
				digitalWrite(2, 0);
				dataIn(1,3,255);
				dataIn(1,3,255);
				dataIn(1,3,255);
				dataIn(1,3,255);
	
				
				if (xpos < 8)
				{
					dataIn(1,3,255);
					dataIn(1,3,255 - i1);
				}
				else
				{
					dataIn(1,3,255 - i1);
					dataIn(1,3,255);
				}
				dataIn(1,3,r);
				digitalWrite(2, 1);
				// draw enemy location -----
				digitalWrite(4, 0);
				digitalWrite(3, 0);
				digitalWrite(2, 0);
				dataIn(1,3,255);
				dataIn(1,3,255);

				
				
				if (enemyxpos < 8)
				{
					dataIn(1,3,255 );
					
					dataIn(1,3,255 - exminus);
				}
				else
				{
					dataIn(1,3,255- exminus);
					dataIn(1,3,255 );

				}
				dataIn(1,3,255);
				dataIn(1,3,255);
				dataIn(1,3,enr);
				digitalWrite(2, 1);
				//------------------------------MY BULLETZ
				if (special == 1)
				{
					digitalWrite(2, 1);
					digitalWrite(4, 0);
					digitalWrite(3, 0);
					digitalWrite(2, 0);
					
					if (temp < 8)
					{
						dataIn(1,3,255);
						dataIn(1,3,255 - temp1);
						dataIn(1,3,255);
						dataIn(1,3,255 - temp1);
						dataIn(1,3,255);
						dataIn(1,3,255 );
					}
					else
					{
						dataIn(1,3,255- temp1 );
						dataIn(1,3,255);
						dataIn(1,3,255- temp1 );
						dataIn(1,3,255);
						dataIn(1,3,255 );
						dataIn(1,3,255);
					}
					dataIn(1,3,shootR);
					digitalWrite(2, 1);
				}
				else
				{
					digitalWrite(2, 1);
					digitalWrite(4, 0);
					digitalWrite(3, 0);
					digitalWrite(2, 0);
					
					if (temp < 8)
					{
						dataIn(1,3,255);
						dataIn(1,3,255);
						dataIn(1,3,255);
						dataIn(1,3,255 - temp1);
						dataIn(1,3,255);
						dataIn(1,3,255 - temp1 );
					}
					else
					{
						dataIn(1,3,255);
						dataIn(1,3,255);
						dataIn(1,3,255- temp1 );
						dataIn(1,3,255);
						dataIn(1,3,255 - temp1  );
						dataIn(1,3,255);
					}
					dataIn(1,3,shootR);
					digitalWrite(2, 1);
				}
					//----------------------- ENEMY BULLETS0000000000000000000--------------------
					digitalWrite(4, 0);
					digitalWrite(3, 0);
					digitalWrite(2, 0);
					
					if (enemytemp < 8)
					{
						dataIn(1,3,255);
						dataIn(1,3,255);
						dataIn(1,3,255);
						dataIn(1,3,255 - enemytemp1);
						dataIn(1,3,255);
						dataIn(1,3,255 - enemytemp1 );
					}
					else
					{
						dataIn(1,3,255);
						dataIn(1,3,255);
						dataIn(1,3,255- enemytemp1 );
						dataIn(1,3,255);
						dataIn(1,3,255 - enemytemp1  );
						dataIn(1,3,255);
					}
					dataIn(1,3,enemyshootR);
					digitalWrite(2, 1);
				break;
			case gg:
				
				gameover = 1; 
				if (WoL == 1)
				{    
				   unsigned char toparr1[] = {222,243,27,126,230,247,151,254} ;
					unsigned char botarr1[] = {195,189,86,122,122,86,189,195};
					unsigned char rowarr1[] ={1, 2, 4, 8, 16, 32, 64, 128};
						digitalWrite(1, 0);
						digitalWrite(3, 0);
						for (int n = 0; n < 8; n++)
						{

							
							digitalWrite(2, 0);
							dataIn(1,3,255);
							dataIn(1,3,255);
							dataIn(1,3,255);
							dataIn(1,3,255);
							dataIn(1,3,255);
							dataIn(1,3,botarr1[n]);
							dataIn(1,3,rowarr1[n]);
							digitalWrite(2, 1);

							
						}
						
				}
				else
				{
		 				unsigned char toparr1[] = {222,243,27,126,230,247,151,254} ;
	 					unsigned char botarr1[] = {195,189,90,118,118,90,189,195};
 						   unsigned char rowarr1[] ={1, 2, 4, 8, 16, 32, 64, 128};
 						   digitalWrite(1, 0);
 						   digitalWrite(3, 0);
 						   for (int n = 0; n < 8; n++)
 						   {

	 						   
	 						   digitalWrite(2, 0);
	 						   dataIn(1,3,255);
	 						   dataIn(1,3,255);
	 						   dataIn(1,3,255);
	 						   dataIn(1,3,botarr1[n]);
	 						   dataIn(1,3,255);
	 						   dataIn(1,3,255);
	 						   dataIn(1,3,rowarr1[n]);
	 						   digitalWrite(2, 1);

	 						   
 						   }
				}								 
		}
	
		return Move_State;
		}					
		
	enum Shoot_States {Shoot_wait, Shoot_up, Shoot_down, Shoot_left, Shoot_right, Shoot_wRelease} Shoot_State;	
	static unsigned char  Keyin;


void Shooting() // shooting states
{
		
		
		switch (Shoot_State){
		case Shoot_wait:
		{
			if(special == 1)
			{
				specialcount--;
				special = 0;
			}
			
			Keyin = GetKeypadKey();
			if (GetKeypadKey() == 'D') {
				if (prevState == up)
				{
				     temp = xpos+1; // bullet location
					 temp1 = i1*2;  // value for datain
					 shootR = r; // value for rows
					 sypos = ypos;// bullet y location
					 special = 0;
					Shoot_State = Shoot_up;
				}
				else if (prevState == down)
				{
				     temp = xpos-1;
					 temp1 = i1/2;
					 shootR = r;
					 sypos = ypos;
					  special = 0;
					Shoot_State = Shoot_down;
				}
				else if (prevState == right)
				{
				     temp = xpos;
					 temp1 = i1;
					 shootR = r/2;
					 sypos = ypos-1;
					  special = 0;
					Shoot_State = Shoot_right;
				}
				else if (prevState == left)
				{
				     temp = xpos;
					 temp1 = i1;
					 shootR = r*2;
					 sypos = ypos+1;
					  special = 0;
					Shoot_State = Shoot_left;
				}
			}				
			   else if  (GetKeypadKey() == '#' && specialcount > 0) {
				   if (prevState == up)
				   {
					   temp = xpos+1;
					   temp1 = i1*2;
					   shootR = r;
					   sypos = ypos;
					   special = 1;
					   Shoot_State = Shoot_up;
				   }
				   else if (prevState == down)
				   {
					   temp = xpos-1;
					   temp1 = i1/2;
					   shootR = r;
					   sypos = ypos;
					   special = 1;
					   Shoot_State = Shoot_down;
				   }
				   else if (prevState == right)
				   {
					   temp = xpos;
					   temp1 = i1;
					   shootR = r/2;
					   sypos = ypos-1;
					   special = 1;
					   Shoot_State = Shoot_right;
				   }
				   else if (prevState == left)
				   {
					   temp = xpos;
					   temp1 = i1;
					   shootR = r*2;
					   sypos = ypos+1;
					   special = 1;
					   Shoot_State = Shoot_left;
				   }
			  }
			break;
		}		
	 case Shoot_up:
		Shoot_State = Shoot_wRelease;
		break;
	 case Shoot_down:
	 	 Shoot_State = Shoot_wRelease;
	 	 break;
	 case Shoot_left:
		 Shoot_State = Shoot_wRelease;
		 break;
     case Shoot_right:
		 Shoot_State = Shoot_wRelease;
		 break;	 	  
	 	 
	case Shoot_wRelease:
		if (GetKeypadKey() == '\0'){
		 // Wait for button release

				if(stillshootingdown == 1)
				{
					Shoot_State = Shoot_down;
				}
				else if ( stillshootingleft == 1 )
				{
					Shoot_State = Shoot_left;
				}
				else if ( stillshootingright == 1 )
				{
					Shoot_State = Shoot_right;
				}
				else if ( stillshootingup == 1 )
				{
					Shoot_State = Shoot_up;
				}
				
				else
					Shoot_State = Shoot_wait;
			}
			else {
				

									
				if(stillshootingdown == 1)
				{
					Shoot_State = Shoot_down;
				}
				else if ( stillshootingleft == 1 )
				{
					Shoot_State = Shoot_left;
				}
				else if ( stillshootingright == 1 )
				{
					Shoot_State = Shoot_right;
				}
				else if ( stillshootingup == 1 )
				{
					Shoot_State = Shoot_up;
				}
				else
				Shoot_State = Shoot_wRelease;
			}
			break;		
		}
	
		switch(Shoot_State) { // State actions

			
			case Shoot_up:
			{	
				if (temp < 16  )
				{
					 stillshootingup = 1;
					if (special == 0)
					{
							unsigned char graphpos = (sypos * 16) + (temp); // if bullet hit wall
						if (gridarr[graphpos] == 1)// if  the spot is lit(wall)
						{
							speaker();
							wallhit(graphpos); // turn it off.
							gridarr[graphpos] = 0;
							stillshootingup = 0; // stop bullet
								 temp = 0;
								 temp1 = 0;
								 shootR = 0;
							break;
						}
						tick ++;
						if (tick == 5)
						{
							temp ++;
							temp1 = temp1 * 2;
							tick = 0;
						}
					}
					else if (special == 1)
					{
						unsigned char graphpos = (sypos * 16) + (temp); // if bullet hit wall
						if (gridarr[graphpos] == 1)// if  the spot is lit(wall)
						{
							speaker();
							wallhit(graphpos); // turn it off.
							gridarr[graphpos] = 0;
					
							break;
						}
						tick ++;
						if (tick == 8)
						{
							temp ++;
							temp1 = temp1 * 2;
							tick = 0;
						}
						
					}
					
			
						
					
						if (temp1 > 128 && temp < 15)
						{
							temp1 = 1;
						}	
					break;
			}
			 stillshootingup = 0;
			break;	
			}
			case Shoot_down:
			{
				if (temp >= 0  )
				{
					stillshootingdown = 1;
					
					unsigned char graphpos = (sypos * 16) + (temp); // if bullet hit wall
					if (gridarr[graphpos] == 1)// if  the spot is lit(wall)
					{
						speaker();
						wallhit(graphpos); // turn it off.
						gridarr[graphpos] = 0;
						temp = 0;
						temp1 = 0;
						shootR = 0;
						stillshootingdown = 0; // stop bullet
						
					}
					if (stillshootingdown == 1)
						
					{
							
							
							tick ++;
							if (tick == 5)
							{
								temp --;
								temp1 = temp1 / 2;
								tick = 0;
							}
							if (temp == 7)
							{
								temp1 = 128;
							}	
					}
					break;
				}
				
			else 
			 {
				 stillshootingdown = 0;
				break;
				}				
			}
			case Shoot_right:
			{
				if (sypos >= 0   )
				{
					stillshootingright = 1;
					
					unsigned char graphpos = (sypos * 16) + (temp); // if bullet hit wall
					if (gridarr[graphpos] == 1)// if  the spot is lit(wall)
					{
						speaker();
						wallhit(graphpos); // turn it off.
						gridarr[graphpos] = 0;
						temp = 0;
						temp1 = 0;
						shootR = 0;
						stillshootingright = 0; // stop bullet
						break;
					}
					
					tick ++;
					if (tick == 5)
					{
						sypos --;
						shootR = shootR / 2;
						tick = 0;
					}
					
					break;
				}
			stillshootingright = 0;
			break;
			}				
			case Shoot_left:
			{
				if (sypos < 8   )
				{
					stillshootingleft = 1;
					
					unsigned char graphpos = (sypos * 16) + (temp); // if bullet hit wall
					if (gridarr[graphpos] == 1)// if  the spot is lit(wall)
					{
				
				speaker();
						wallhit(graphpos); // turn it off.
						gridarr[graphpos] = 0;
						stillshootingleft = 0; // stop bullet
						temp = 0;
						temp1 = 0;
						shootR = 0;
						break;
					}
					
					tick ++;
					if (tick == 5)
					{
						sypos ++;
						shootR = shootR * 2;
						tick = 0;
					}
					
					if (sypos == 8)
					{
						stillshootingleft = 0;	
					}
				
					break;
				}
				stillshootingright = 0;
				break;
			}
								 
}
return Shoot_State;
}

unsigned char toparr[] = {222,243,27,126,230,247,151,254} ;
	unsigned char botarr[] = {127,239,225,79,124,207,217,127};
	unsigned char rowarr[] ={1, 2, 4, 8, 16, 32, 64, 128};
void wallhit(unsigned char loc){ // these are the locations where there is a wall
			switch(loc){
				case 7:
				{
					int numz = botarr[0];
					botarr[0]= numz + 128;
					break;
				}
				case 8:
				{
					int numz = toparr[0];
					toparr[0] = numz + 1;
					break;
				}
				case 13:
				{
					int numz = toparr[0];
					toparr[0] = numz + 32;
					break;
				}
				case 20:
				{
					int numz = botarr[1];
					botarr[1] = numz + 16;
					break;
				}
				case 26:
				{
					int numz = toparr[1];
					toparr[1] = numz + 4;
					break;
				}
				case 27:
				{
					int numz = toparr[1];
					toparr[1] = numz + 8;
					break;
				}
				case 33:
				{
					int numz = botarr[2];
					botarr[2] = numz + 2;
					break;
				}
				case 34:
				{
					int numz = botarr[2];
					botarr[2] = numz + 4;
					break;
				}
				case 35:
				{
					int numz = botarr[2];
					botarr[2] = numz + 8;
					break;
				}
				case 36:
				{
					int numz = botarr[2];
					botarr[2] = numz + 16;
					break;
				}
				case 42:
				{
					int numz = toparr[2];
					toparr[2] = numz + 4;
					break;
				}
				case 45:
				{
					int numz = toparr[2];
					toparr[2] = numz + 32;
					break;
				}
				case 46:
				{
					int numz = toparr[2];
					toparr[2] = numz + 64;
					break;
				}
				case 47:
				{
					int numz = toparr[2];
					toparr[2] = numz + 128;
					break;
				}
				case 52:
				{
					int numz = botarr[3];
					botarr[3] = numz + 16;
					break;
				}
				case 53:
				{
					int numz = botarr[3];
					botarr[3] = numz + 32;
					break;
				}
				case 55:
				{
					int numz = botarr[3];
					botarr[3] = numz + 128;
					break;
				}
				case 56:
				{
					int numz = toparr[3];
					toparr[3] = numz + 1;
					break;
				}
				case 63:
				{
					int numz = toparr[3];
					toparr[3] = numz + 128;
					break;
				}
				case 64:
				{
					int numz = botarr[4];
					botarr[4] = numz + 1;
					break;
				}
				case 65:
				{
					int numz = botarr[4];
					botarr[4] = numz + 2;
					break;
				}
				case 71:
				{
					int numz = botarr[4];
					botarr[4] = numz + 128;
					break;
				}
				case 72:
				{
					int numz = toparr[4];
					toparr[4] = numz + 1;
					break;
				}
				case 75:
				{
					int numz = toparr[4];
					toparr[4] = numz + 8;
					break;
				}
				case 76:
				{
					int numz = toparr[4];
					toparr[4] = numz + 16;
					break;
				}
				case 84:
				{
					int numz = botarr[5];
					botarr[5] = numz + 16 ;
					break;
				}
				case 85:
				{
					int numz = botarr[5];
					botarr[5] = numz + 32 ;
					break;
				}
				case 91:
				{
					int numz = toparr[5];
					toparr[5] = numz + 8;
					break;
				}
				case 97:
				{
					int numz = botarr[6];
					botarr[6] = numz + 2;
					break;
				}
				case 98:
				{
					int numz = botarr[6];
					botarr[6] = numz + 4;
					break;
				}
				case 101:
				{
					int numz = botarr[6];
					botarr[6] = numz + 32;
					break;
				}
				case 107:
				{
					int numz = toparr[6];
					toparr[6] = numz + 8 ;
					break;
				}
				case 109:
				{
					int numz = toparr[6];
					toparr[6] = numz + 32 ;
					break;
				}
				case 110:
				{
					int numz = toparr[6];
					toparr[6] = numz + 64 ;
					break;
				}
				case 119:
				{
					int numz = botarr[7];
					botarr[7] = numz +  128 ;
					break;
				}
				case 120:
				{
					int numz = toparr[7];
					toparr[7] = numz + 1 ;
					break;
				}
				
			}
}				
void map() // draws the map
{
	
	digitalWrite(1, 0);
	digitalWrite(3, 0);
	for (int n = 0; n < 8; n++)
	{

		
		digitalWrite(2, 0);
		dataIn(1,3,toparr[n]);
		dataIn(1,3,botarr[n]);
		dataIn(1,3,255);
		dataIn(1,3,255);
		dataIn(1,3,255);
		dataIn(1,3,255);
		dataIn(1,3,rowarr[n]);
		digitalWrite(2, 1);

		
	}
		

}


void createarray() // creates array for map
{
	unsigned char gridarron[] = {7,8,13,20,26,27,33,34,35,36,42,45,46,47,52,53,55,56,63,64,65,71,72,75,76,84,85,91,97,98,101,107,109,110,119,120};
	for(int z = 0; z < 128; z++)
	{
		gridarr[z] = 0;
	}
	for (int z = 0; z < 36; z++)
	{
		unsigned char arrtemp = gridarron[z];//sets those indexes to 1 (on)
		gridarr[arrtemp] = 1;
	}
	unsigned char toparr1[] = {222,243,27,126,230,247,151,254} ;
	unsigned char botarr1[] = {127,239,225,79,124,207,217,127};

		//repopulate arrays;
		for(int z = 0; z < 8; z++)
		{
			toparr[z] = toparr1[z];
			botarr[z] = botarr1[z];
		}

}


unsigned char num = 0;	
enum Enemy_States { eBegin, eStart, Enemy_wait, Enemy_shooting, Enemy_up, Enemy_down, Enemy_left, Enemy_right, Eshoot  } Enemy_State; // enemy SM
	int tick2 = 0;
	
	unsigned char prevx;
	unsigned char prevy;
	void Enmove(){
			
			switch( Enemy_State)  {
				// Transitions
				case eBegin:
				
					 {
			 
						unsigned char c = GetKeypadKey();
						 if (GetKeypadKey() == '3') {
							 Enemy_State = eStart;
							 restart = 0;
						 }
					 }
				
				break;
				case eStart:

					Enemy_State = Enemy_wait;
					break;
				
				case Enemy_wait:
					{
			
						if (hard == 1)	
						{
							srand(seed);
						num = rand()%5;
						
						
						//unsigned char c = GetKeypadKey();
						
							if(estillshootingup == 1 || estillshootingdown == 1 || estillshootingright == 1 || estillshootingleft == 1 )
						{Enemy_State = Enemy_shooting;}
							
						 else if (restart == 1)
						{
					
							    Enemy_State = eBegin;
							
						}
						
		
							else if( num == 1 )  // Button active low
							{
								if (tick2 == 10)
								{   
									tick2= 0;
									if (enemyxpos > xpos)
									{
										Enemy_State = Enemy_down;
									}
									else
									Enemy_State = Enemy_up;
								}
								else{
									tick2++;
									Enemy_State = Enemy_wait;
								}
										
							}												
							else if(  num == 2)  // Button active low
							{
								if (tick2 == 10)
								{
									tick2= 0;
									if (enemyxpos > xpos)
									{
										Enemy_State = Enemy_down;
									}
									else
									Enemy_State = Enemy_up;
								}
								else{
									tick2++;
									Enemy_State = Enemy_wait;
								}
							}								
									
											
							else if(  num == 3)  // Button active low
							{
								if (tick2 == 10)
								{
									tick2= 0;
									if (enemyypos > ypos)
									{
										Enemy_State = Enemy_right;
									}
									else
									Enemy_State = Enemy_left;
								}
								else{
									tick2++;
									Enemy_State = Enemy_wait;
								}
							}
							
							else if(  num == 4)  // Button active low
								{
									if (tick2 == 10)
									{
										tick2= 0;
										
										if (enemyypos > ypos)
										{
											Enemy_State = Enemy_right;
										}
										else
										Enemy_State = Enemy_left;
									}
									else{
										tick2++;
										Enemy_State = Enemy_wait;
									}
								}									
							else if ( num == 0)
							{
								if (tick2 == 10)
								{
									tick2= 0;
								Enemy_State = Eshoot;
								}	
								else{
									tick2++;
									Enemy_State = Enemy_wait;
								}							
								
							}
						}
						
						if (hard == 0)
						{
							{
								srand(seed);
								num = 1 + rand()%5;
								
								
							if (restart == 1)
								{
									
									Enemy_State = eBegin;
									
								}
								//unsigned char c = GetKeypadKey();
								
								if(estillshootingup == 1 || estillshootingdown == 1 || estillshootingright == 1 || estillshootingleft == 1 )
							{Enemy_State = Enemy_shooting;}
								
								 
								
								else if ((prevx == enemyxpos || prevy == enemyypos))
								{
									if (tick2 == 10)
									{
										tick2= 0;
										prevy = 8;
										prevx = 16;
										Enemy_State = Eshoot;
										
									}
									else{
										tick2++;
										Enemy_State = Enemy_wait;
									}
									
								}
								
								
								else if( num == 1 )  // Button active low
								{
									if (tick2 == 8)
									{	
										tick2 = 0;
										if (enemyxpos == xpos || enemyypos == ypos)
										{
											if (enemyxpos > xpos)
											enemyPrevState = down;
											else if ( enemyxpos < xpos )
											enemyPrevState = up;
											else if (enemyypos > ypos)
											enemyPrevState = right;
											else if (enemyypos < ypos)
											enemyPrevState = left;
											Enemy_State= Eshoot;
										}
									
										if (enemyxpos > xpos)
										{
											prevx = enemyxpos;
											Enemy_State = Enemy_down;
										}
										else
										Enemy_State = Enemy_up;
									}
									else{
										tick2++;
										Enemy_State = Enemy_wait;
									}
									
								}
								else if(  num == 2 )  // Button active low
								{
									if (tick2 == 8)
									{
										
										tick2= 0;
										if (enemyxpos == xpos || enemyypos == ypos)
										{
											if (enemyxpos > xpos)
											enemyPrevState = down;
											else if ( enemyxpos < xpos )
											enemyPrevState = up;
											else if (enemyypos > ypos)
											enemyPrevState = right;
											else if (enemyypos < ypos)
											enemyPrevState = left;
											Enemy_State= Eshoot;
										}
										if (enemyxpos > xpos)
										{
											prevx = enemyypos;
											Enemy_State = Enemy_down;
										}
										else
										Enemy_State = Enemy_up;
									}
									else{
										tick2++;
										Enemy_State = Enemy_wait;
									}
								}
								
								
								else if(  num == 3)  // Button active low
								{
									if (tick2 == 8)
									{
										
										tick2= 0;
										if (enemyxpos == xpos || enemyypos == ypos)
										{
											if (enemyxpos > xpos)
											enemyPrevState = down;
											else if ( enemyxpos < xpos )
											enemyPrevState = up;
											else if (enemyypos > ypos)
											enemyPrevState = right;
											else if (enemyypos < ypos)
											enemyPrevState = left;
											Enemy_State= Eshoot;
										}
										if (enemyypos > ypos)
										{
											prevy = enemyxpos;
											Enemy_State = Enemy_right;
										}
										else
										Enemy_State = Enemy_left;
									}
									else{
										tick2++;
										Enemy_State = Enemy_wait;
									}
								}
								
								else if(  num == 4)  // Button active low
								{
									if (tick2 == 8)
									{
										tick2= 0;
										if (enemyxpos == xpos || enemyypos == ypos)
										{
											if (enemyxpos > xpos)
											enemyPrevState = down;
											else if ( enemyxpos < xpos )
											enemyPrevState = up;
											else if (enemyypos > ypos)
											enemyPrevState = right;
											else if (enemyypos < ypos)
											enemyPrevState = left;
											Enemy_State= Eshoot;
										}
										
							
										if (enemyypos > ypos)
										{
											prevy = enemyxpos;
											Enemy_State = Enemy_right;
										}
										else
										Enemy_State = Enemy_left;
									}
									else{
										tick2++;
										Enemy_State = Enemy_wait;
									}
								}
								
							}
						}
						
						
					
												
						break;
					}
				
				case Enemy_up:
							{
					
						Enemy_State = Enemy_wait;
						break;
				}
				case Enemy_down:
							
					{
						Enemy_State = Enemy_wait;
						break;
				}
				case Enemy_right:
					
					{
					Enemy_State = Enemy_wait;
						break;
}
				case Enemy_left:
			
					{
					Enemy_State = Enemy_wait;
						break;
}
				case Eshoot:
				{
						Enemy_State = Enemy_shooting;
						break;	
				}
				case Enemy_shooting :
				

				
						Enemy_State = Enemy_wait;
										
								
			}
		
			
			
		
			
			switch(Enemy_State)  // State actions
			{
		case eStart:
				{
				createarray();
					map();
					exminus = 128;
					enr = 128;
					enemyxpos = 15;
					enemyypos = 7;
					
					enemyPrevState = down;

					
					break;
				}
				
		case Enemy_up:

					if (enemyxpos < 15)
					{
						unsigned char graphpos = (enemyypos * 16) + (enemyxpos + 1);
						if (gridarr[graphpos] == 1)// if  the spot above current position is lit(wall)
						{
							enemyPrevState = up;
							break;
						}
						exminus = exminus * 2;
						if (enemyxpos == 7 )
						{
							exminus = 1;
						}
						enemyxpos ++;
					}
					
					enemyPrevState = up;
				break;
				case Enemy_down:
				
				enemyPrevState = down;
					
					if (enemyxpos > 0)
					{
						unsigned char graphpos = (enemyypos * 16) + (enemyxpos - 1);
						if (gridarr[graphpos] == 1)// if  the spot below current position is lit(wall)
						{
							enemyPrevState = down;
							break;
						}
						exminus = exminus / 2;
						if (enemyxpos == 8)
						{
							exminus = 128;
						}
						
						
					
						
						enemyxpos --;
						
						
					}
				break;
				case Enemy_right:
					if (enemyypos > 0)
					{
						unsigned char graphpos = ((enemyypos-1) * 16) + (enemyxpos);
						if (gridarr[graphpos] == 1)// if  the spot right of current position is lit(wall)
						{
							enemyPrevState = right;
							break;
						}
						
						enemyypos --;
						enr = enr / 2;

					}
		
		
					enemyPrevState = right;
					break;
				case Enemy_left:
				
				if (enemyypos < 7)
				{
					unsigned char graphpos = ((enemyypos+1) * 16) + (enemyxpos);
					if (gridarr[graphpos] == 1)// if  the spot below current position is lit(wall)
					{
						enemyPrevState = left;
						break;
					}

					enemyypos ++;
					enr = enr * 2;

				}

				
				enemyPrevState = left;
				break;

				

				case Eshoot:
				{
						if (enemyPrevState == up)
						{
							enemytemp = enemyxpos+1;
							enemytemp1 = exminus*2;
							enemyshootR =enr;
							enemysypos = enemyypos;
							
						}
						else if (enemyPrevState == down)
						{
							enemytemp = enemyxpos-1;
							enemytemp1 = exminus/2;
							enemyshootR =enr;
							enemysypos = enemyypos;
							
						}
						else if (enemyPrevState ==right)
						{
							enemytemp = enemyxpos;
							enemytemp1 = exminus;
							enemyshootR =enr/2;
							enemysypos = enemyypos-1;
							
						}
						else if (enemyPrevState == left)
						{
							enemytemp = enemyxpos;
							enemytemp1 = exminus;
							enemyshootR =enr*2;
							enemysypos = enemyypos+1;
							
						}
						break;
				}
				case Enemy_shooting:
				{
					if (enemyPrevState == up)
					{				
						if (enemytemp < 16 &&   enemytemp >= 0 )
						{
							estillshootingup = 1;
						
							unsigned char graphpos = (enemysypos * 16) + (enemytemp); // if bullet hit wall
							if (gridarr[graphpos] == 1)// if  the spot is lit(wall)
							{
								speaker();
								wallhit(graphpos); // turn it off.
								gridarr[graphpos] = 0;
								estillshootingup = 0; // stop bullet
								
								enemytemp1 = 0;
								enemyshootR = 0;
								break;
							}
						
							tick1 ++;
							if (tick1 == 5)
							{
								enemytemp ++;
								enemytemp1 = enemytemp1 * 2;
								tick1 = 0;
							}
						
							if (enemytemp ==8 )
							{
								enemytemp1 = 1;
							}
							break;
						}
						estillshootingup = 0;
					}	
					if (enemyPrevState == down)		
					{
						if (enemytemp >= 0 && enemytemp < 16 && enemyxpos>0 )
						{
							estillshootingdown = 1;
							
							unsigned char graphpos = (enemysypos * 16) + (enemytemp); // if bullet hit wall
							if (gridarr[graphpos] == 1)// if  the spot is lit(wall)
							{
								speaker();
								wallhit(graphpos); // turn it off.
								gridarr[graphpos] = 0;
								
								enemytemp1 = 0;
								enemyshootR = 0;
								estillshootingdown = 0; // stop bullet
								
							}
							if (estillshootingdown == 1)
							
							{
								
								if (enemytemp == 0)
								{
									estillshootingdown = 0;
									enemytemp1 = 0;
									
								}
								tick1 ++;
								if (tick1 == 5)
								{
									enemytemp --;
									enemytemp1 = enemytemp1 / 2;
									tick1 = 0;
								}
								if (enemytemp == 7)
								{
									enemytemp1 = 128;
								}

							}
							
						}
						

					}	
					if (enemyPrevState == right)
					{		
						if (enemysypos >= 0 && enemysypos < 8 )
						{
							estillshootingright = 1;
							
							unsigned char graphpos = (enemysypos * 16) + (enemytemp); // if bullet hit wall
							if (gridarr[graphpos] == 1)// if  the spot is lit(wall)
							{
								speaker();
								wallhit(graphpos); // turn it off.
								gridarr[graphpos] = 0;
								
								enemytemp1 = 0;
								enemyshootR = 0;
								estillshootingright = 0; // stop bullet
								break;
							}
							
							tick1 ++;
							if (tick1 == 5)
							{
								enemysypos --;
								enemyshootR = enemyshootR / 2;
								tick1 = 0;
							}
							
							break;
						}
						else
						estillshootingright = 0;
						
					}
					if (enemyPrevState == left)
					{
						if (enemysypos < 8 && enemysypos >= 0   )
						{
							estillshootingleft = 1;
							
							unsigned char graphpos = (enemysypos * 16) + (enemytemp); // if bullet hit wall
							if (gridarr[graphpos] == 1)// if  the spot is lit(wall)
							{
								speaker();
								wallhit(graphpos); // turn it off.
								gridarr[graphpos] = 0;
								estillshootingleft = 0; // stop bullet
								
								enemytemp1 = 0;
								enemyshootR = 0;
								break;
							}
							
							tick1 ++;
							if (tick1 == 5)
							{
								enemysypos ++;
								enemyshootR = enemyshootR * 2;
								tick1 = 0;
							}
							
							if (enemysypos == 8)
							{
								estillshootingleft = 0;
							}
							
						
						}
						else
						estillshootingright = 0;
						
					}												

				}
				
			
		}
		
		return Enemy_State;
	}		
				

void bullettouch1() // when bullets touch
{
	if ( temp !=0 && enemytemp !=0)
	{
		if (temp == enemytemp && sypos == enemysypos)
		bullettouch = 1;
	}
	else
	bullettouch = 0;
	
}

void speaker() // buzzes when contact made by bullets
{
	int cnt = 0;
	
	
	while(cnt < 500)
	{
		if(cnt % 100 == 22)
		
		{
			PORTA = SetBit (PORTA,2,0);
			map ();
			// ME ----------------
			digitalWrite(4, 0);
			digitalWrite(3, 0);
			digitalWrite(2, 0);
			dataIn(1,3,255);
			dataIn(1,3,255);
			dataIn(1,3,255);
			dataIn(1,3,255);
			
			
			if (xpos < 8)
			{
				dataIn(1,3,255);
				dataIn(1,3,255 - i1);
			}
			else
			{
				dataIn(1,3,255 - i1);
				dataIn(1,3,255);
			}
			dataIn(1,3,r);
			digitalWrite(2, 1);
			// draw enemy location------
			digitalWrite(4, 0);
			digitalWrite(3, 0);
			digitalWrite(2, 0);
			dataIn(1,3,255);
			dataIn(1,3,255);

			
			
			if (enemyxpos < 8)
			{
				dataIn(1,3,255 );
				
				dataIn(1,3,255 - exminus);
			}
			else
			{
				dataIn(1,3,255- exminus);
				dataIn(1,3,255 );

			}
			dataIn(1,3,255);
			dataIn(1,3,255);
			dataIn(1,3,enr);
			// MY BULLETS ..  I THINK================================================================================
			digitalWrite(2, 1);
			digitalWrite(4, 0);
			digitalWrite(3, 0);
			digitalWrite(2, 0);
			
			if (temp < 8)
			{
				dataIn(1,3,255);
				dataIn(1,3,255);
				dataIn(1,3,255);
				dataIn(1,3,255 - temp1);
				dataIn(1,3,255);
				dataIn(1,3,255 - temp1 );
			}
			else
			{
				dataIn(1,3,255);
				dataIn(1,3,255);
				dataIn(1,3,255- temp1 );
				dataIn(1,3,255);
				dataIn(1,3,255 - temp1  );
				dataIn(1,3,255);
			}
			dataIn(1,3,shootR);
			digitalWrite(2, 1);
			// ENEMY BULLETS================================================================================
			digitalWrite(4, 0);
			digitalWrite(3, 0);
			digitalWrite(2, 0);
			
			if (enemytemp < 8)
			{
				dataIn(1,3,255);
				dataIn(1,3,255);
				dataIn(1,3,255);
				dataIn(1,3,255 - enemytemp1);
				dataIn(1,3,255);
				dataIn(1,3,255 - enemytemp1 );
			}
			else
			{
				dataIn(1,3,255);
				dataIn(1,3,255);
				dataIn(1,3,255- enemytemp1 );
				dataIn(1,3,255);
				dataIn(1,3,255 - enemytemp1  );
				dataIn(1,3,255);
			}
			dataIn(1,3,enemyshootR);
			digitalWrite(2, 1);
		
			
			
		}
		if (cnt %100 == 11)
		PORTA = SetBit (PORTA,2,1);
		
	
			
		cnt++;
		
	}
	cnt = 0;
	PORTA = SetBit (PORTA,2,0);
	
	
	
}
void LEDbar() // shows how many special attacks you have left
{
if(specialcount == 2)
{
	PORTA = SetBit (PORTA,7,1);
	PORTA = SetBit (PORTA,6,1);
}
else if(specialcount == 1)
{
	PORTA = SetBit (PORTA,7,0);
	PORTA = SetBit (PORTA,6,1);
}
else if(specialcount == 0)
{
	PORTA = SetBit (PORTA,7,0);
	PORTA = SetBit (PORTA,6,0);
}
}

int main(void)
{
		DDRA = 0xFF; PORTA = 0x00;
		DDRB = 0xFF; PORTB = 0x00;
		DDRC = 0xF0; PORTC = 0x0F;
		DDRD = 0xFF; PORTD = 0x00;
		 unsigned char MOVE_Tick_P = 1;
		 unsigned char en_Tick_P = 1;
		 unsigned char SHOOT_Tick_P = 2;
		unsigned char LI_Tick_P = 10;
		unsigned char LT_Tick_P = 10;
		
		static task task1, task2,task3, task4, task5;
		task *tasks[] = { &task1, &task2,&task3, &task4, &task5 };
		const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
		
		
		task3.state = Begin;//Task initial state.
		task3.period = MOVE_Tick_P;//Task Period.
		task3.elapsedTime = MOVE_Tick_P;//Task current elapsed time.
		task3.TickFct = &Moving;//Function pointer for the tick.

		// Task 2
		task4.state = Shoot_wait;//Task initial state.
		task4.period = SHOOT_Tick_P;//Task Period.
		task4.elapsedTime = SHOOT_Tick_P;//Task current elapsed time.
		task4.TickFct = &Shooting;//Function pointer for the tick.
		
		task1.state = -1;//Task initial state.
		task1.period = LI_Tick_P;//Task Period.
		task1.elapsedTime = LI_Tick_P;//Task current elapsed time.
		task1.TickFct = &LI_Tick;//Function pointer for the tick.

		// Task 2
		task2.state = -1;//Task initial state.
		task2.period = LT_Tick_P;//Task Period.
		task2.elapsedTime = LT_Tick_P;//Task current elapsed time.
		task2.TickFct = &LT_Tick;//Function pointer for the tick.
		
				task5.state = eBegin;//Task initial state.
				task5.period = en_Tick_P;//Task Period.
				task5.elapsedTime = en_Tick_P;//Task current elapsed time.
				task5.TickFct = &Enmove;//Function pointer for the tick.

	TimerSet(1);
	TimerOn();
	unsigned short i; 

    while(1)
    {
		
        for ( i = 0; i < 5; i++ ) {
	        // Task is ready to tick
	        if ( tasks[i]->elapsedTime == tasks[i]->period ) {
		        // Setting next state for task
		        tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
		        // Reset the elapsed time for next tick.
		        tasks[i]->elapsedTime = 0;
	        }
	        tasks[i]->elapsedTime += 1;
        } 

 while (!TimerFlag);
        TimerFlag = 0;
		
		
    }
	
	return 0;
}