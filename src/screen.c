/**
 * screen.c
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include "screen.h"

// Função que desenha as bordas da tela
void screenDrawBorders() 
{
    // Caracteres para desenhar as bordas horizontal e vertical
    char hbc = BOX_HLINE;
    char vbc = BOX_VLINE;

    // Limpa a tela e habilita o desenho da borda
    screenClear();
    screenBoxEnable();
    
    // Desenha a borda superior
    screenGotoxy(MINX, MINY);
    printf("%c", BOX_UPLEFT);
    for (int i = MINX + 1; i < MAXX; i++) {
        screenGotoxy(i, MINY);
        printf("%c", hbc);
    }
    screenGotoxy(MAXX, MINY);
    printf("%c", BOX_UPRIGHT);

    // Desenha as bordas laterais
    for (int i = MINY + 1; i < MAXY; i++) { //provavelmente para colocar o sistema de pontos teremos que alterar aq
        screenGotoxy(MINX, i);
        printf("%c", vbc);
        screenGotoxy(MAXX, i);
        printf("%c", vbc);
    }

    // Desenha a borda inferior
    screenGotoxy(MINX, MAXY);
    printf("%c", BOX_DWNLEFT);
    for (int i = MINX + 1; i < MAXX; i++) {
        screenGotoxy(i, MAXY);
        printf("%c", hbc);
    }
    screenGotoxy(MAXX, MAXY);
    printf("%c", BOX_DWNRIGHT);

    // Desabilita o desenho da borda
    screenBoxDisable();
}

// Função que inicializa a tela
void screenInit(int drawBorders)
{
    // Limpa a tela
    screenClear();

    // Desenha as bordas se a flag drawBorders for verdadeira
    if (drawBorders) {
        screenDrawBorders();
    }

    // Posiciona o cursor no canto superior esquerdo e oculta o cursor
    screenHomeCursor();
    screenHideCursor();
}

// Função que restaura as configurações da tela
void screenDestroy()
{
    // Reset de cores e limpeza da tela
    printf("%s[0;39;49m", ESC);
    screenSetNormal();
    screenClear();
    screenHomeCursor();
    screenShowCursor();
}

// Função que move o cursor para a posição (x, y) na tela
void screenGotoxy(int x, int y)
{
    // Limita as coordenadas dentro dos limites da tela
    x = (x < 0 ? 0 : x >= MAXX ? MAXX - 1 : x);
    y = (y < 0 ? 0 : y >= MAXY ? MAXY - 1 : y);

    // Move o cursor para a posição (x, y)
    printf("%s[f%s[%dB%s[%dC", ESC, ESC, y, ESC, x);
}

// Função que define as cores do texto e do fundo da tela
void screenSetColor(screenColor fg, screenColor bg)
{
    char atr[] = "[0;";

    if (fg > LIGHTGRAY) {
        atr[1] = '1';
        fg -= 8;
    }

    printf("%s%s%d;%dm", ESC, atr, fg + 30, bg + 40);
}

