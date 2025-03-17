#include <stm32f031x6.h>
#include "display.h"
#include <stdlib.h>


#define CLAMP_X(val) CLAMP(val, 0, 116)  // 128-12=116
#define CLAMP_Y(val) CLAMP(val, 0, 112)  // 128-16=112
#define CLAMP(val, min, max) ((val) < (min) ? (min) : ((val) > (max) ? (max) : (val)))




void initClock(void);
void initSysTick(void);
void SysTick_Handler(void);
void delay(volatile uint32_t dly);
void setupIO();
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py);
void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber);
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode);



volatile uint32_t milliseconds;

// Original image arrays
const uint16_t beeUp[] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,65287,65287,65287,0,0,0,0,0,0,0,0,0,0,0,0,0,65287,65287,65287,0,0,0,0,0,0,0,0,0,0,0,65287,0,65287,0,65287,0,65287,0,0,0,0,0,0,0,0,0,65287,0,65287,0,65287,0,65287,53502,0,0,0,0,0,0,0,0,65287,0,65287,0,65287,0,65287,53502,0,0,0,0,0,0,0,0,65287,0,65287,0,65287,0,65287,53502,0,0,0,0,0,0,0,0,65287,0,65287,0,65287,0,65287,53502,0,0,0,0,0,0,0,0,65287,0,65287,0,65287,0,65287,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const uint16_t beeDown[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,65287,65287,65287,65287,65287,65287,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,65287,65287,65287,65287,65287,65287,65287,65287,0,0,0,0,0,0,0,0,0,0,0,0,0,0,65287,65287,0,0,0,0,0,0,0,0,65287,65287,65287,65287,65287,65287,65287,65287,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,65287,65287,65287,65287,65287,65287,0,0,0,0,0,0,0,0,0,53502,0,53502,53502,53502,53502,0,53502,0,0,0,0,0,0,0,0,53502,0,0,0,0,0,0,53502,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
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
            // Player 1 (Bee) controls - Normal directions
            if((GPIOB->IDR & (1 << 4)) == 0) bee_x++;  // Right
            if((GPIOB->IDR & (1 << 5)) == 0) bee_x--;  // Left
            if((GPIOA->IDR & (1 << 8)) == 0) bee_y--;  // Up
            if((GPIOA->IDR & (1 << 11)) == 0) bee_y++; // Down

            // Player 2 (Flower) controls - Reverse directions using same buttons
            if((GPIOB->IDR & (1 << 4)) == 0) flower_x--;  // When Right pressed, move left
            if((GPIOB->IDR & (1 << 5)) == 0) flower_x++;  // When Left pressed, move right
            if((GPIOA->IDR & (1 << 8)) == 0) flower_y++;  // When Up pressed, move down
            if((GPIOA->IDR & (1 << 11)) == 0) flower_y--; // When Down pressed, move up

            // Keep both characters on screen
            bee_x = CLAMP(bee_x, 0, 116);     // 128 - 12 (bee width)
            bee_y = CLAMP(bee_y, 0, 112);     // 128 - 16 (bee height)
            flower_x = CLAMP(flower_x, 0, 112); // 128 - 16 (flower size)
            flower_y = CLAMP(flower_y, 0, 112); // 128 - 16 (flower size)

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

            // Accurate collision detection using bounding boxes
            if(bee_x < flower_x + 16 && 
                bee_x + 12 > flower_x && 
                bee_y < flower_y + 16 && 
                bee_y + 16 > flower_y) {
                printText("BEE WINS!", 10, 20, RGBToWord(255, 0, 0), 0);
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


int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py) {
    uint16_t x2 = x1 + w;
    uint16_t y2 = y1 + h;
    return (px >= x1) && (px <= x2) && (py >= y1) && (py <= y2);
}


// ================== HARDWARE SETUP ==================
void setupIO() {
    RCC->AHBENR |= (1 << 18) | (1 << 17);  // Enable GPIOB and GPIOA
    display_begin();

    // Bee controls
    pinMode(GPIOB, 4, 0);    // Right
    pinMode(GPIOB, 5, 0);    // Left
    pinMode(GPIOA, 8, 0);    // Up
    pinMode(GPIOA, 11, 0);   // Down
    
    // Flower controls (new pins)
    pinMode(GPIOA, 0, 0);    // Right
    pinMode(GPIOA, 1, 0);    // Left
    pinMode(GPIOB, 0, 0);    // Up
    pinMode(GPIOB, 1, 0);    // Down

    // Enable pull-ups for all buttons
    enablePullUp(GPIOB, 4);
    enablePullUp(GPIOB, 5);
    enablePullUp(GPIOA, 8);
    enablePullUp(GPIOA, 11);
    enablePullUp(GPIOA, 0);
    enablePullUp(GPIOA, 1);
    enablePullUp(GPIOB, 0);
    enablePullUp(GPIOB, 1);

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



