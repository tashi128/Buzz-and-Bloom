/*#include <stm32f031x6.h>
#include "display.h"
void initClock(void);
void initSysTick(void);
void SysTick_Handler(void);
void delay(volatile uint32_t dly);
void setupIO();
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py);
void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber);
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode);
volatile uint32_t milliseconds;

const uint16_t beeUp[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,40224,0,0,0,0,65535,65535,0,0,0,0,0,0,0,0,40224,0,40224,0,0,65535,65535,65535,0,0,0,0,0,0,0,0,0,0,0,24327,40224,65535,40224,0,0,0,0,0,0,0,0,0,0,0,24327,24327,40224,24327,40224,24327,0,0,0,0,0,0,0,0,0,0,24327,24327,40224,24327,40224,24327,40224,0,0,0,0,0,0,0,0,0,24327,24327,40224,24327,40224,24327,0,0,0,0,0,0,0,0,0,0,0,24327,40224,24327,40224,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const uint16_t beeDown[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,40224,0,0,0,0,65535,65535,0,0,0,0,0,0,0,0,40224,0,40224,0,0,65535,65535,65535,0,0,0,0,0,0,0,0,0,0,0,24327,40224,65535,40224,0,0,0,0,0,0,0,0,0,0,0,24327,24327,40224,24327,40224,24327,0,0,0,0,0,0,0,0,0,0,24327,24327,40224,24327,40224,24327,40224,0,0,0,0,0,0,0,0,0,24327,24327,40224,24327,40224,24327,0,0,0,0,0,0,0,0,0,0,0,24327,40224,24327,40224,0,0,0,0,0,0,0,0,0,0,0,0,0,40224,0,40224,0,0,0,0,0,0,0,0,0,0,0,0,40224,0,0,0,40224,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const uint16_t smileyy[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,57293,57293,0,0,0,0,0,0,0,0,0,0,40224,40224,40224,57293,57293,57293,40224,40224,0,0,0,0,0,0,0,0,40224,57293,57293,24327,24327,57293,40224,40224,0,0,0,0,0,0,57293,57293,24327,24327,57293,57293,24327,57293,57293,40224,57293,57293,0,0,0,0,57293,24327,24327,24327,57293,57293,57293,57293,24327,24327,24327,57293,0,0,0,0,57293,24327,24327,40224,40224,40224,40224,40224,24327,24327,57293,0,0,0,0,0,40224,24327,24327,57293,40224,40224,40224,57293,24327,57293,57293,0,0,0,0,0,40224,40224,57293,24327,40224,40224,40224,57293,24327,9293,0,0,0,0,0,0,40224,40224,40224,24327,24327,57293,24327,24327,24327,57293,9293,0,0,0,0,0,0,0,57293,24327,24327,57293,24327,24327,24327,57293,9293,9293,0,0,0,0,0,0,57293,24327,24327,57293,57293,57293,57293,0,0,9293,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9293,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9293,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9293,9293,0,0};
const uint16_t deco1[]=
{
0,0,0,0,4,4,4,4,4,0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,65415,65415,65415,248,65415,0,0,0,0,0,0,0,65415,65415,65415,65415,65415,8068,0,0,0,0,0,0,65415,65415,65415,4096,4096,0,0,0,0,0,0,0,0,65415,65415,65415,0,0,0,0,0,0,0,0,0,7936,7936,7936,0,0,0,0,0,0,0,0,7936,7936,65535,7936,0,0,0,0,0,0,0,0,7936,7936,65535,7936,7936,7936,7936,0,0,0,0,0,7936,7936,65535,65535,65535,65535,7936,0,0,0,0,0,7936,7936,7936,7936,7936,7936,7936,0,0,0,0,0,7936,7936,7936,7936,0,0,0,0,0,0,0,0,0,7936,65535,7936,0,0,0,0,0,0,0,0,0,7936,65535,7936,0,0,0,0,0,0,0,0,0,7936,65535,7936,0,0,0,0,0,0,0,0,0,7940,7940,7940,7940,0,0,0,
};
const uint16_t deco2[]= 
	{
0,0,0,0,0,4,4,4,4,4,0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,65415,65415,65415,248,65415,0,0,0,0,0,0,0,65415,65415,65415,65415,65415,8068,0,0,0,0,0,0,65415,65415,65415,4096,4096,0,0,0,0,0,0,0,0,65415,65415,65415,0,0,0,0,0,0,0,0,7936,7936,7936,0,0,0,0,0,0,0,0,7936,7936,65535,7936,0,0,0,0,0,0,0,0,7936,7936,65535,7936,7936,7936,7936,0,0,0,0,0,7936,7936,65535,65535,65535,65535,7936,0,0,0,0,0,7936,7936,7936,7936,7936,7936,7936,0,0,0,0,0,7936,7936,7936,7936,0,0,0,0,0,0,0,0,0,40224,7936,65535,7936,0,0,0,0,0,0,0,40224,40224,7936,65535,7936,0,0,0,0,0,0,65315,40224,40224,7936,65535,40224,0,0,0,0,0,0,0,65315,0,65315,65315,65315,65315,0,0,
	};
const uint16_t deco3[]= 
{
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,4,4,4,4,0,0,0,0,0,0,0,4,4,4,4,4,4,0,0,0,0,7936,7936,4,4,4,4,4,4,7936,7936,0,0,65535,65535,4,4,4,4,4,4,65535,65535,0,0,7936,7936,4,4,4,4,4,4,7936,7936,0,0,0,0,0,4,4,4,4,0,0,0,0,0,0,0,0,0,24327,24327,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};
const uint16_t dg1[]=
{
	0,0,16142,16142,16142,16142,16142,16142,16142,16142,0,0,0,0,0,16142,16142,16142,16142,16142,16142,0,0,0,0,0,16142,16142,16142,16142,16142,16142,16142,16142,0,0,0,0,16142,16142,16142,1994,1994,16142,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,1994,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,1994,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,1994,16142,16142,0,0,0,0,16142,16142,16142,1994,1994,16142,16142,16142,0,0,0,0,16142,16142,16142,16142,16142,16142,16142,16142,0,0,0,0,16142,16142,16142,1994,1994,1994,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,16142,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,16142,16142,16142,0,0,0,0,16142,16142,16142,1994,16142,1994,16142,16142,0,0,0,0,16142,16142,16142,1994,1994,1994,16142,16142,0,0,0,0,0,16142,16142,16142,16142,16142,16142,0,0,0,0,0,0,16142,16142,16142,16142,16142,16142,0,0,0,
};

int main()
{
	int hinverted = 0;
	int vinverted = 0;
	int toggle = 0;
	int hmoved = 0;
	int vmoved = 0;
	uint16_t x = 50;
	uint16_t y = 50;
	uint16_t oldx = x;
	uint16_t oldy = y;
	initClock();
	initSysTick();
	setupIO();
	putImage(20,80,12,16,dg1,0,0);
	putImage(64, 30, 16, 16, smileyy, 0, 0);
	for (int x = 0; x < 20; x++)
	{
		fillRectangle(x+20, 30, 16, 16, 24327);
		putImage(x+20, 30, 16, 16, smileyy, 24327, 24327);
		delay(200);
		//RGBToWord(245,225,70); it's already declared in the display.c file 

	}

	while(1)
	{
		hmoved = vmoved = 0;
		hinverted = vinverted = 0;
		if ((GPIOB->IDR & (1 << 4))==0) // right pressed
		{					
			if (x < 110)
			{
				x = x + 1;
				hmoved = 1;
				hinverted=0;
			}						
		}
		if ((GPIOB->IDR & (1 << 5))==0) // left pressed
		{			
			
			if (x > 10)
			{
				x = x - 1;
				hmoved = 1;
				hinverted=1;
			}			
		}
		if ( (GPIOA->IDR & (1 << 11)) == 0) // down pressed
		{
			if (y < 140)
			{
				y = y + 1;			
				vmoved = 1;
				vinverted = 0;
			}
		}
		if ( (GPIOA->IDR & (1 << 8)) == 0) // up pressed
		{			
			if (y > 16)
			{
				y = y - 1;
				vmoved = 1;
				vinverted = 1;
			}
		}
		if ((vmoved) || (hmoved))
		{
			// only redraw if there has been some movement (reduces flicker)
			fillRectangle(oldx,oldy,12,16,0);
			oldx = x;
			oldy = y;					
			if (hmoved)
			{
				if (toggle)
					putImage(x,y,12,16,deco1,hinverted,0);
				else
					putImage(x,y,12,16,deco2,hinverted,0);
				
				toggle = toggle ^ 1;
			}
			else
			{
				putImage(x,y,12,16,deco3,0,vinverted);
			}
			// Now check for an overlap by checking to see if ANY of the 4 corners of deco are within the target area
			if (isInside(20,80,12,16,x,y) || isInside(20,80,12,16,x+12,y) || isInside(20,80,12,16,x,y+16) || isInside(20,80,12,16,x+12,y+16) )
			{
				printTextX2("GLUG!", 10, 20, RGBToWord(0xff,0xff,0), 0);
			}
		}		
		delay(50);
	}
	return 0;
}
void initSysTick(void)
{
	SysTick->LOAD = 48000;
	SysTick->CTRL = 7;
	SysTick->VAL = 10;
	__asm(" cpsie i "); // enable interrupts
}
void SysTick_Handler(void)
{
	milliseconds++;
}
void initClock(void)
{
// This is potentially a dangerous function as it could
// result in a system with an invalid clock signal - result: a stuck system
        // Set the PLL up
        // First ensure PLL is disabled
        RCC->CR &= ~(1u<<24);
        while( (RCC->CR & (1 <<25))); // wait for PLL ready to be cleared
        
// Warning here: if system clock is greater than 24MHz then wait-state(s) need to be
// inserted into Flash memory interface
				
        FLASH->ACR |= (1 << 0);
        FLASH->ACR &=~((1u << 2) | (1u<<1));
        // Turn on FLASH prefetch buffer
        FLASH->ACR |= (1 << 4);
        // set PLL multiplier to 12 (yielding 48MHz)
        RCC->CFGR &= ~((1u<<21) | (1u<<20) | (1u<<19) | (1u<<18));
        RCC->CFGR |= ((1<<21) | (1<<19) ); 

        // Need to limit ADC clock to below 14MHz so will change ADC prescaler to 4
        RCC->CFGR |= (1<<14);

        // and turn the PLL back on again
        RCC->CR |= (1<<24);        
        // set PLL as system clock source 
        RCC->CFGR |= (1<<1);
}
void delay(volatile uint32_t dly)
{
	uint32_t end_time = dly + milliseconds;
	while(milliseconds != end_time)
		__asm(" wfi "); // sleep
}

void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber)
{
	Port->PUPDR = Port->PUPDR &~(3u << BitNumber*2); // clear pull-up resistor bits
	Port->PUPDR = Port->PUPDR | (1u << BitNumber*2); // set pull-up bit
}
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode)
{
	
	uint32_t mode_value = Port->MODER;
	Mode = Mode << (2 * BitNumber);
	mode_value = mode_value & ~(3u << (BitNumber * 2));
	mode_value = mode_value | Mode;
	Port->MODER = mode_value;
}
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py)
{
	// checks to see if point px,py is within the rectange defined by x,y,w,h
	uint16_t x2,y2;
	x2 = x1+w;
	y2 = y1+h;
	int rvalue = 0;
	if ( (px >= x1) && (px <= x2))
	{
		// ok, x constraint met
		if ( (py >= y1) && (py <= y2))
			rvalue = 1;
	}
	return rvalue;
}

void setupIO()
{
	RCC->AHBENR |= (1 << 18) + (1 << 17); // enable Ports A and B
	display_begin();
	pinMode(GPIOB,4,0);
	pinMode(GPIOB,5,0);
	pinMode(GPIOA,8,0);
	pinMode(GPIOA,11,0);
	enablePullUp(GPIOB,4);
	enablePullUp(GPIOB,5);
	enablePullUp(GPIOA,11);
	enablePullUp(GPIOA,8);
}*/

#include <stm32f031x6.h>
#include "display.h"
#include <stdlib.h>

#define CLAMP(val, min, max) ((val) < (min) ? (min) : ((val) > (max) ? (max) : (val)))

void initClock(void);
void initSysTick(void);
void SysTick_Handler(void);
void delay(volatile uint32_t dly);
void setupIO();
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py);
void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber);
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode);
void turnOnLED(GPIO_TypeDef *Port, uint32_t BitNumber);
void turnOffLED(GPIO_TypeDef *Port, uint32_t BitNumber);

volatile uint32_t milliseconds;

// Original image arrays
const uint16_t beeUp[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,40224,0,0,0,0,65535,65535,0,0,0,0,0,0,0,0,40224,0,40224,0,0,65535,65535,65535,0,0,0,0,0,0,0,0,0,0,0,24327,40224,65535,40224,0,0,0,0,0,0,0,0,0,0,0,24327,24327,40224,24327,40224,24327,0,0,0,0,0,0,0,0,0,0,24327,24327,40224,24327,40224,24327,40224,0,0,0,0,0,0,0,0,0,24327,24327,40224,24327,40224,24327,0,0,0,0,0,0,0,0,0,0,0,24327,40224,24327,40224,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const uint16_t beeDown[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,40224,0,0,0,0,65535,65535,0,0,0,0,0,0,0,0,40224,0,40224,0,0,65535,65535,65535,0,0,0,0,0,0,0,0,0,0,0,24327,40224,65535,40224,0,0,0,0,0,0,0,0,0,0,0,24327,24327,40224,24327,40224,24327,0,0,0,0,0,0,0,0,0,0,24327,24327,40224,24327,40224,24327,40224,0,0,0,0,0,0,0,0,0,24327,24327,40224,24327,40224,24327,0,0,0,0,0,0,0,0,0,0,0,24327,40224,24327,40224,0,0,0,0,0,40224,0,40224,0,0,0,0,0,0,0,0,40224,0,0,0,40224,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const uint16_t smileyy[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,57293,57293,0,0,0,0,0,0,0,0,0,0,40224,40224,40224,57293,57293,57293,40224,40224,0,0,0,0,0,0,0,0,40224,57293,57293,24327,24327,57293,40224,40224,0,0,0,0,0,0,57293,57293,24327,24327,57293,57293,24327,57293,57293,40224,57293,57293,0,0,0,0,57293,24327,24327,24327,57293,57293,57293,57293,24327,24327,24327,57293,0,0,0,0,57293,24327,24327,40224,40224,40224,40224,40224,24327,24327,57293,0,0,0,0,0,40224,24327,24327,57293,40224,40224,40224,57293,24327,57293,57293,0,0,0,0,0,40224,40224,57293,24327,40224,40224,40224,57293,24327,9293,0,0,0,0,0,0,40224,40224,40224,24327,24327,57293,24327,24327,24327,57293,9293,0,0,0,0,0,0,0,57293,24327,24327,57293,24327,24327,24327,57293,9293,9293,0,0,0,0,0,0,57293,24327,24327,57293,57293,57293,57293,0,0,9293,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9293,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9293,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9293,9293,0,0};

// Menu functions
void showMainMenu(int selectedOption);
int handleMenuInput(int currentSelection);


#define CLAMP(val, min, max) ((val) < (min) ? (min) : ((val) > (max) ? (max) : (val)))

int main() {
    // System initialization
    initClock();
    initSysTick();
    setupIO();

    // Configure LEDs
    pinMode(GPIOA, 0, 1);  // Green LED
    pinMode(GPIOA, 1, 1);  // Red LED
    turnOffLED(GPIOA, 0);
    turnOffLED(GPIOA, 1);

    // Main game loop
    while(1) {
        // Menu system
        int menuSelection = 0;
        int gameActive = 1;
        
        // Menu navigation
        while(gameActive) {
            showMainMenu(menuSelection);
            menuSelection = handleMenuInput(menuSelection);
            delay(100);
            
            if(menuSelection == -1) {  // Start Game
                fillRectangle(0, 0, 128, 128, 0);
                gameActive = 0;
            }
            else if(menuSelection == -2) {  // Exit
                fillRectangle(0, 0, 128, 128, 0);
                printText("Goodbye!", 40, 60, RGBToWord(255, 255, 255), 0);
                while(1); // Permanent halt
            }
        }

        // Game session variables
        int round = 1;
        int beeWins = 0;
        int flowerWins = 0;
        uint16_t bee_x = 64, bee_y = 64;
        uint16_t flower_x = 32, flower_y = 96;
        uint16_t old_bee_x = bee_x, old_bee_y = bee_y;
        uint16_t old_flower_x = flower_x, old_flower_y = flower_y;

        // Game rounds loop
        while(round <= 3) {
            // Round initialization
            fillRectangle(0, 0, 128, 128, 0);
            int beeChasing = 1;
            uint32_t startTime = milliseconds;

            // Reset positions
            bee_x = 64;
            bee_y = 64;
            flower_x = 32;
            flower_y = 96;
            
            // Draw initial positions
            putImage(flower_x, flower_y, 16, 16, smileyy, 0, 0);
            putImage(bee_x, bee_y, 12, 16, beeUp, 0, 0);

            // Single round gameplay
            while(beeChasing && (milliseconds - startTime) < 30000) {
                // Player 1 (Bee) controls
                if((GPIOB->IDR & (1 << 4)) == 0) bee_x++;  // Right
                if((GPIOB->IDR & (1 << 5)) == 0) bee_x--;  // Left
                if((GPIOA->IDR & (1 << 8)) == 0) bee_y--;  // Up
                if((GPIOA->IDR & (1 << 11)) == 0) bee_y++; // Down

                // Player 2 (Flower) controls
                if((GPIOB->IDR & (1 << 4)) == 0) flower_x++;  // Share Right
                if((GPIOB->IDR & (1 << 5)) == 0) flower_x--;  // Share Left
                if((GPIOA->IDR & (1 << 8)) == 0) flower_y--;  // Share Up
                if((GPIOA->IDR & (1 << 11)) == 0) flower_y++; // Share Down

                // Clamp positions
                bee_x = CLAMP(bee_x, 10, 118);
                bee_y = CLAMP(bee_y, 16, 140);
                flower_x = CLAMP(flower_x, 10, 118);
                flower_y = CLAMP(flower_y, 16, 140);

                // Update positions
                if(bee_x != old_bee_x || bee_y != old_bee_y) {
                    fillRectangle(old_bee_x, old_bee_y, 12, 16, 0);
                    putImage(bee_x, bee_y, 12, 16, beeUp, 0, 0);
                    old_bee_x = bee_x;
                    old_bee_y = bee_y;
                }

                if(flower_x != old_flower_x || flower_y != old_flower_y) {
                    fillRectangle(old_flower_x, old_flower_y, 16, 16, 0);
                    putImage(flower_x, flower_y, 16, 16, smileyy, 0, 0);
                    old_flower_x = flower_x;
                    old_flower_y = flower_y;
                }

                // Collision detection
                if(abs(bee_x - flower_x) < 12 && abs(bee_y - flower_y) < 16) {
                    printText("BEE WINS!", 10, 20, RGBToWord(255, 0, 0), 0);
                    turnOnLED(GPIOA, 1);
                    beeChasing = 0;
                    beeWins++;
                    delay(2000);
                }

                delay(50);
            }

            if(beeChasing) {
                printText("FLOWER WINS!", 10, 20, RGBToWord(0, 255, 0), 0);
                flowerWins++;
                delay(2000);
            }

            round++;
        }

        // Final results
        fillRectangle(0, 0, 128, 128, 0);
        if(beeWins > flowerWins) {
            printText("WINNER IS BEE!", 10, 40, RGBToWord(255, 0, 0), 0);
        } else if(flowerWins > beeWins) {
            printText("WINNER IS FLOWER!", 10, 40, RGBToWord(0, 255, 0), 0);
        } else {
            printText("IT'S A TIE!", 30, 40, RGBToWord(255, 255, 0), 0);
        }
        
        // Restart prompt
        printText("Press any button", 10, 70, RGBToWord(255, 255, 255), 0);
        printText("to continue...", 20, 90, RGBToWord(255, 255, 255), 0);
        
        // Wait for restart input
        while(1) {
            if((GPIOB->IDR & (1 << 4)) == 0 ||
               (GPIOB->IDR & (1 << 5)) == 0 ||
               (GPIOA->IDR & (1 << 8)) == 0 ||
               (GPIOA->IDR & (1 << 11)) == 0) {
                delay(200);
                break;
            }
        }
    }
}



// ================== SYSTEM INIT FUNCTIONS ==================
void initSysTick(void) {
    SysTick->LOAD = 48000;
    SysTick->CTRL = 7;
    SysTick->VAL = 10;
    __asm(" cpsie i ");
}

void SysTick_Handler(void) {
    milliseconds++;
}


void initClock(void) {
    // Enable HSI (8MHz internal RC oscillator)
    RCC->CR |= RCC_CR_HSION;
    while((RCC->CR & RCC_CR_HSIRDY) == 0); // Wait for HSI ready

    // Configure FLASH latency for 48MHz (1 wait state)
    FLASH->ACR |= FLASH_ACR_LATENCY;
    
    // Configure PLL for 48MHz output (HSI/2 * 12 = 48MHz)
    RCC->CFGR &= ~RCC_CFGR_PLLMUL; // Clear PLL multiplier bits
    RCC->CFGR |= RCC_CFGR_PLLMUL12; // 12x multiplier
    RCC->CFGR &= ~RCC_CFGR_PLLSRC;  // Select HSI/2 as PLL source
    
    // Enable PLL
    RCC->CR |= RCC_CR_PLLON;
    while((RCC->CR & RCC_CR_PLLRDY) == 0); // Wait for PLL lock
    
    // Switch to PLL clock source
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    
    // Wait until PLL becomes system clock
    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
    
    // Set APB prescaler to 1 (no division)
    RCC->CFGR &= ~RCC_CFGR_PPRE;
}



// ================== HELPER FUNCTIONS ==================
void delay(volatile uint32_t dly) {
    uint32_t end_time = dly + milliseconds;
    while(milliseconds != end_time)
        __asm(" wfi ");
}

void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber) {
    Port->PUPDR = Port->PUPDR &~(3u << BitNumber*2);
    Port->PUPDR = Port->PUPDR | (1u << BitNumber*2);
}

void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode) {
    uint32_t mode_value = Port->MODER;
    Mode = Mode << (2 * BitNumber);
    mode_value = mode_value & ~(3u << (BitNumber * 2));
    mode_value = mode_value | Mode;
    Port->MODER = mode_value;
}

void turnOnLED(GPIO_TypeDef *Port, uint32_t BitNumber) {
    Port->ODR |= (1 << BitNumber);
}

void turnOffLED(GPIO_TypeDef *Port, uint32_t BitNumber) {
    Port->ODR &= ~(1 << BitNumber);
}

int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py) {
    uint16_t x2 = x1 + w;
    uint16_t y2 = y1 + h;
    return (px >= x1) && (px <= x2) && (py >= y1) && (py <= y2);
}

// ================== HARDWARE SETUP ==================
void setupIO() {
    RCC->AHBENR |= (1 << 18) + (1 << 17);
    display_begin();
    pinMode(GPIOB,4,0);
    pinMode(GPIOB,5,0);
    pinMode(GPIOA,8,0);
    pinMode(GPIOA,11,0);
    enablePullUp(GPIOB,4);
    enablePullUp(GPIOB,5);
    enablePullUp(GPIOA,8);
    enablePullUp(GPIOA,11);


}

// ================== MENU FUNCTIONS ==================

	void showMainMenu(int selectedOption) {
    fillRectangle(0, 0, 128, 128, 0);
    printText("BUZZ AND BLOOM", 10, 20, RGBToWord(255, 255, 0), 0);
    
    if(selectedOption == 0) {
        printText("> START GAME", 10, 60, RGBToWord(0, 255, 0), 0);
        printText("  EXIT", 40, 90, RGBToWord(128, 128, 128), 0);
    } else {
        printText("  START GAME", 10, 60, RGBToWord(128, 128, 128), 0);
        printText("> EXIT", 40, 90, RGBToWord(255, 0, 0), 0);
    }
}

int handleMenuInput(int currentSelection) {
    static uint32_t lastInput = 0;
    const uint32_t debounceTime = 200;
    
    // Improved debounce check
    if((milliseconds - lastInput) < debounceTime) return currentSelection;
    
    // Check button states
    uint8_t rightPressed = (GPIOB->IDR & (1 << 4)) == 0;
    uint8_t leftPressed = (GPIOB->IDR & (1 << 5)) == 0;
    uint8_t selectPressed = (GPIOA->IDR & (1 << 11)) == 0;

    if(rightPressed || leftPressed || selectPressed) {
        lastInput = milliseconds;
        
        if(rightPressed) return 1;
        if(leftPressed) return 0;
        if(selectPressed) return currentSelection == 0 ? -1 : -2;
    }
    
    return currentSelection;
}



