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
const uint16_t smileyy[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,57293,57293,0,0,0,0,0,0,0,0,0,0,40224,40224,40224,57293,57293,57293,40224,40224,0,0,0,0,0,0,0,0,40224,57293,57293,24327,24327,57293,40224,40224,0,0,0,0,0,0,57293,57293,24327,24327,57293,57293,24327,57293,57293,40224,57293,57293,0,0,0,0,57293,24327,24327,24327,57293,57293,57293,57293,24327,24327,24327,57293,0,0,0,0,57293,24327,24327,40224,40224,40224,40224,40224,24327,24327,57293,0,0,0,0,0,40224,24327,24327,57293,40224,40224,40224,57293,24327,57293,57293,0,0,0,0,0,40224,40224,57293,24327,40224,40224,40224,57293,24327,9293,0,0,0,0,0,0,40224,40224,40224,24327,24327,57293,24327,24327,24327,57293,9293,0,0,0,0,0,0,0,57293,24327,24327,57293,24327,24327,24327,57293,9293,9293,0,0,0,0,0,0,57293,24327,24327,57293,57293,57293,57293,0,0,9293,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9293,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9293,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9293,9293,0,0};const uint16_t deco1[]=
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
#include <stdlib.h> // For random number generation

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

const uint16_t beeUp[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,40224,0,0,0,0,65535,65535,0,0,0,0,0,0,0,0,40224,0,40224,0,0,65535,65535,65535,0,0,0,0,0,0,0,0,0,0,0,24327,40224,65535,40224,0,0,0,0,0,0,0,0,0,0,0,24327,24327,40224,24327,40224,24327,0,0,0,0,0,0,0,0,0,0,24327,24327,40224,24327,40224,24327,40224,0,0,0,0,0,0,0,0,0,24327,24327,40224,24327,40224,24327,0,0,0,0,0,0,0,0,0,0,0,24327,40224,24327,40224,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const uint16_t beeDown[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,40224,0,0,0,0,65535,65535,0,0,0,0,0,0,0,0,40224,0,40224,0,0,65535,65535,65535,0,0,0,0,0,0,0,0,0,0,0,24327,40224,65535,40224,0,0,0,0,0,0,0,0,0,0,0,24327,24327,40224,24327,40224,24327,0,0,0,0,0,0,0,0,0,0,24327,24327,40224,24327,40224,24327,40224,0,0,0,0,0,0,0,0,0,24327,24327,40224,24327,40224,24327,0,0,0,0,0,0,0,0,0,0,0,24327,40224,24327,40224,0,0,0,0,0,0,0,0,0,0,0,0,0,40224,0,40224,0,0,0,0,0,0,0,0,0,0,0,0,40224,0,0,0,40224,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const uint16_t smileyy[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,57293,57293,0,0,0,0,0,0,0,0,0,0,40224,40224,40224,57293,57293,57293,40224,40224,0,0,0,0,0,0,0,0,40224,57293,57293,24327,24327,57293,40224,40224,0,0,0,0,0,0,57293,57293,24327,24327,57293,57293,24327,57293,57293,40224,57293,57293,0,0,0,0,57293,24327,24327,24327,57293,57293,57293,57293,24327,24327,24327,57293,0,0,0,0,57293,24327,24327,40224,40224,40224,40224,40224,24327,24327,57293,0,0,0,0,0,40224,24327,24327,57293,40224,40224,40224,57293,24327,57293,57293,0,0,0,0,0,40224,40224,57293,24327,40224,40224,40224,57293,24327,9293,0,0,0,0,0,0,40224,40224,40224,24327,24327,57293,24327,24327,24327,57293,9293,0,0,0,0,0,0,0,57293,24327,24327,57293,24327,24327,24327,57293,9293,9293,0,0,0,0,0,0,57293,24327,24327,57293,57293,57293,57293,0,0,9293,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9293,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9293,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9293,9293,0,0};

int main() {
    uint16_t bee_x = 50;
    uint16_t bee_y = 50;
    uint16_t flower_x = 100;
    uint16_t flower_y = 80;
    uint16_t old_bee_x = bee_x;
    uint16_t old_flower_x = flower_x;
    uint16_t old_bee_y = bee_y;
    uint16_t old_flower_y = flower_y;
    int beeChasing = 1; // 1 when bee is chasing, 0 when flower is caught
    int round = 1;
    int beeWins = 0;
    int flowerWins = 0;
    uint32_t startTime;

    initClock();
    initSysTick();
    setupIO();

    // Initialize LEDs
    pinMode(GPIOA, 0, 1); // Green LED (PA0) as output
    pinMode(GPIOA, 1, 1); // Red LED (PA1) as output
    turnOffLED(GPIOA, 0); // Turn off Green LED initially
    turnOffLED(GPIOA, 1); // Turn off Red LED initially

    while (round <= 3) {
        bee_x = 50;
        bee_y = 50;
        flower_x = 100;
        flower_y = 80;
        beeChasing = 1;
        startTime = milliseconds;

        // Turn on Green LED when the bee is chasing
        turnOnLED(GPIOA, 0);
        turnOffLED(GPIOA, 1);

        putImage(flower_x, flower_y, 16, 16, smileyy, 0, 0);
        putImage(bee_x, bee_y, 12, 16, beeUp, 0, 0);

        while (beeChasing && (milliseconds - startTime) < 30000) {
            int bee_moved = 0, flower_moved = 0;

            // Bee movement
            if ((GPIOB->IDR & (1 << 4)) == 0) bee_x = (bee_x < 110) ? bee_x + 1 : bee_x;
            if ((GPIOB->IDR & (1 << 5)) == 0) bee_x = (bee_x > 10) ? bee_x - 1 : bee_x;
            if ((GPIOA->IDR & (1 << 11)) == 0) bee_y = (bee_y < 140) ? bee_y + 1 : bee_y;
            if ((GPIOA->IDR & (1 << 8)) == 0) bee_y = (bee_y > 16) ? bee_y - 1 : bee_y;

            // Flower movement (random escape)
            int flower_move = rand() % 4; // Random direction (0: up, 1: down, 2: left, 3: right)
            switch (flower_move) {
                case 0: flower_y = (flower_y > 16) ? flower_y - 1 : flower_y; break; // Up
                case 1: flower_y = (flower_y < 140) ? flower_y + 1 : flower_y; break; // Down
                case 2: flower_x = (flower_x > 10) ? flower_x - 1 : flower_x; break; // Left
                case 3: flower_x = (flower_x < 110) ? flower_x + 1 : flower_x; break; // Right
            }

            if ((bee_x != old_bee_x) || (bee_y != old_bee_y)) {
                fillRectangle(old_bee_x, old_bee_y, 12, 16, 0);
                old_bee_x = bee_x;
                old_bee_y = bee_y;
                putImage(bee_x, bee_y, 12, 16, beeUp, 0, 0);
            }

            if ((flower_x != old_flower_x) || (flower_y != old_flower_y)) {
                fillRectangle(old_flower_x, old_flower_y, 16, 16, 0);
                old_flower_x = flower_x;
                old_flower_y = flower_y;
                putImage(flower_x, flower_y, 16, 16, smileyy, 0, 0);
            }

            // Check if the bee catches the flower
            if (isInside(flower_x, flower_y, 16, 16, bee_x, bee_y)) {
                printTextX2("BEE WINS!", 10, 20, RGBToWord(255, 0, 0), 0);
                turnOnLED(GPIOA, 1); // Turn on Red LED when caught
                turnOffLED(GPIOA, 0); // Turn off Green LED
                beeChasing = 0; // Stop movement
                beeWins++;
                putImage(bee_x, bee_y, 12, 16, beeDown, 0, 0); // Show beeDown when flower is caught
            }

            delay(50);
        }

        if (beeChasing) {
            printTextX2("FLOWER WINS!", 10, 20, RGBToWord(0, 255, 0), 0);
            flowerWins++;
        }

        round++;
        delay(2000); // Delay before starting the next round
    }

    // Determine the overall winner after 3 rounds
    if (beeWins > flowerWins) {
        printTextX2("BEE WINNER!", 10,20, RGBToWord(255, 0, 0), 0);
    } else if (flowerWins > beeWins) {
        printTextX2("FLOWER WINNER!", 10, 20, RGBToWord(0, 255, 0), 0);
    } else {
        printTextX2("IT'S A TIE!", 10, 20, RGBToWord(255, 255, 0), 0);
    }

    while (1); // Infinite loop to keep the game result displayed
}

void initSysTick(void) {
    SysTick->LOAD = 48000;
    SysTick->CTRL = 7;
    SysTick->VAL = 10;
    __asm(" cpsie i "); // enable interrupts
}

void SysTick_Handler(void) {
    milliseconds++;
}

void initClock(void) {
    RCC->CR &= ~(1u<<24);
    while( (RCC->CR & (1 <<25)));

    FLASH->ACR |= (1 << 0);
    FLASH->ACR &=~((1u << 2) | (1u<<1));
    FLASH->ACR |= (1 << 4);
    RCC->CFGR &= ~((1u<<21) | (1u<<20) | (1u<<19) | (1u<<18));
    RCC->CFGR |= ((1<<21) | (1<<19) ); 
    RCC->CFGR |= (1<<14);
    RCC->CR |= (1<<24);        
    RCC->CFGR |= (1<<1);
}

void delay(volatile uint32_t dly) {
    uint32_t end_time = dly + milliseconds;
    while(milliseconds != end_time)
        __asm(" wfi "); // sleep
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
    Port->ODR |= (1 << BitNumber); // Set the bit to turn on the LED
}

void turnOffLED(GPIO_TypeDef *Port, uint32_t BitNumber) {
    Port->ODR &= ~(1 << BitNumber); // Clear the bit to turn off the LED
}

int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py) {
    uint16_t x2,y2;
    x2 = x1+w;
    y2 = y1+h;
    int rvalue = 0;
    if ( (px >= x1) && (px <= x2)) {
        if ( (py >= y1) && (py <= y2))
            rvalue = 1;
    }
    return rvalue;
}

void setupIO() {
    RCC->AHBENR |= (1 << 18) + (1 << 17); // enable Ports A and B
    display_begin();
    pinMode(GPIOB,4,0); // Bee right
    pinMode(GPIOB,5,0); // Bee left
    pinMode(GPIOA,8,0); // Bee up
    pinMode(GPIOA,11,0); // Bee down
    enablePullUp(GPIOB,4);
    enablePullUp(GPIOB,5);
    enablePullUp(GPIOA,8);
    enablePullUp(GPIOA,11);
}