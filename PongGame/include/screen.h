/**
 * screen.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
 * Reference: https://en.wikipedia.org/wiki/ANSI_escape_code
*/

#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <stdio.h>

// Terminal control sequences
#define ESC            "\033"
#define NORMALTEXT     "[0m"
#define BOLDTEXT       "[1m"
#define ITALICTEXT     "[3m"
#define BLINKTEXT      "[5m"
#define REVERSETEXT    "[7m"
#define HOMECURSOR     "[f"
#define SHOWCURSOR     "[?25h"
#define HIDECURSOR     "[?25l"
#define CLEARSCREEN    "[2J"

// BOX Drawing - Unix like terminals
#define BOX_ENABLE     "(0"
#define BOX_DISABLE    "(B"
#define BOX_VLINE      0x78
#define BOX_HLINE      0x71
#define BOX_UPLEFT     0x6C
#define BOX_UPRIGHT    0x6B
#define BOX_DWNLEFT    0x6D
#define BOX_DWNRIGHT   0x6A
#define BOX_CROSS      0x6E
#define BOX_TLEFT      0X74
#define BOX_TRIGHT     0X75
#define BOX_TUP        0X77
#define BOX_TDOWN      0X76

#define BOX_DIAMOND    0x60
#define BOX_BLOCK      0x61
#define BOX_DOT        0x7E

// screen constants
#define SCRSTARTX      1      // Posição inicial da tela no eixo X
#define SCRENDX        81     // Posição final da tela no eixo X (SCRSTARTX + 80)
#define SCRSTARTY      1      // Posição inicial da tela no eixo Y
#define SCRENDY        29     // Posição final da tela no eixo Y (SCRSTARTY + 28)

#define MINX           1      // Posição mínima no eixo X para varrer (SCRSTARTX)
#define MINY           1      // Posição mínima no eixo Y para varrer (SCRSTARTY)
#define MAXX           80     // Posição máxima no eixo X para varrer (SCRSTARTX + 80 - 1)
#define MAXY           28     // Posição máxima no eixo Y para varrer (SCRSTARTY + 28 - 1)


#define RAQUETE_DISTANCE       2


/**
 * Screen Colors type
*/
typedef enum {BLACK, RED, GREEN, BROWN, BLUE, MAGENTA, CYAN, LIGHTGRAY,
        DARKGRAY, LIGHTRED, LIGHTGREEN, YELLOW, LIGHTBLUE, 
        LIGHTMAGENTA, LIGHTCYAN, WHITE} screenColor; 



/**
 * Move the cursor to position (0,0)
*/
static inline void screenHomeCursor()
{
    printf("%s%s", ESC, HOMECURSOR);
}

/**
 * Show the cursor
*/
static inline void screenShowCursor()
{
    printf("%s%s", ESC, SHOWCURSOR);
}

/**
 * Hide the cursor
*/
static inline void screenHideCursor()
{
    printf("%s%s", ESC, HIDECURSOR);
}

/**
 * Clear the screen
*/
static inline void screenClear()
{
    screenHomeCursor();
    printf("%s%s", ESC, CLEARSCREEN);
}

/**
 * Update screen imediatelly 
*/
static inline void screenUpdate() {
    fflush(stdout);
}

/**
 * Set screen mode to "normal"
*/
static inline void screenSetNormal()
{
    printf("%s%s", ESC, NORMALTEXT);
}

/**
 * Set screen mode to "bold"
*/
static inline void screenSetBold()
{
    printf("%s%s", ESC, BOLDTEXT);
}

/**
 * Set screen mode to "blink"
*/
static inline void screenSetBlink()
{
    printf("%s%s", ESC, BLINKTEXT);
}

/**
 * Set screen mode to "reverse"
*/
static inline void screenSetReverse()
{
    printf("%s%s", ESC, REVERSETEXT);
}

/**
 * Enable BOX characters in terminal
*/
static inline void screenBoxEnable()
{
    printf("%s%s", ESC, BOX_ENABLE);
}

/**
 * Disable BOX characters in terminal
*/
static inline void screenBoxDisable()
{
    printf("%s%s", ESC, BOX_DISABLE);
}

/**
 * Clear the screen, set cursor to home position
 * and optionally draw borders on it.
 * 
 * @param drawBorders if not zero, draw borders on screen.
*/
void screenInit(int drawBorders);

/**
 * Clear the screen and restores to initial state.
*/
void screenDestroy();

void screenDrawBorders();
/**
 * Move cursor to position (x,y)
 * @param x x position
 * @param y y position
 */ 

void screenGotoxy(int x, int y);

/**
 * Define text colors 
 * @param fg foreground color, can assume values from BLACK to WHITE
 * @param bg background color, can assume values from BLACK to LIGHTGRAY
*/
void screenSetColor(screenColor fg, screenColor bg);

#endif /* __SCREEN_H__ */