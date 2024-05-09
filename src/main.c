/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/
/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
 * 
 * 
 * 
 * 
Para compilar os arquivos

Escreva no terminal:

1.   gcc -I./include src/*.c -o PongGame

2.  ./PongGame

*/
#include <stdlib.h>
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int raqueteDireitaY = 10;
int raqueteEsquerdaY=10;  // Posição inicial da raquete
int x = 40, y = 12;  // Posição inicial do elemento na tela (x, y)

int incX = 1;
int incY = 1;


void telaInicio() {
    system("clear"); // Limpa a tela

    printf("\n\n\n");
    printf("       JOGO DO PONG\n\n");
    printf("   Instruções:\n");
    printf("   - Use as teclas W e S para mover a raquete esquerda\n");
    printf("   - Use as teclas I e K para mover a raquete direita\n");
    printf("   - Pressione qualquer tecla para começar o jogo\n\n");
    printf("   Boa sorte!\n\n");

    getchar(); // Aguarda o jogador pressionar uma tecla
}


void printHello(int nextX, int nextY) {
    screenSetColor(YELLOW, DARKGRAY);  // Define as cores de texto e fundo
    screenGotoxy(x, y);  // Move o cursor para a posição (x, y)
    printf(" ");  // Limpa o texto anterior
    x = nextX;  // Atualiza a posição x
    y = nextY;  // Atualiza a posição y
    screenGotoxy(x, y);  // Move o cursor para a nova posição
    printf("o");  // Imprime um caractere na nova posição (originalmente um HelloWorld)
}
void printRaquetes() {

    screenGotoxy(MINX+1, raqueteEsquerdaY);  // Move o cursor para a nova posição
    printf("|");
    screenGotoxy(MINX+1, raqueteEsquerdaY-1);
    printf("|");

    screenGotoxy(MAXX-2, raqueteDireitaY);  // Move o cursor para a nova posição
    printf("|");
    screenGotoxy(MAXX-2, raqueteDireitaY-1);
    printf("|");


    
      // Imprime um caractere na nova posição (originalmente um HelloWorld)
}

void printKey(int ch) {
    screenSetColor(YELLOW, DARKGRAY);  // Define as cores para texto e fundo
    screenGotoxy(MINX, MAXY+7);  // Move o cursor para a posição para imprimir o código da tecla
    printf("Raquete Esquerda: W up S down/ Raquete Direita I up K down:");

    

    if (ch == 27)  // Se o código for o de "Esc", ajusta a posição
        screenGotoxy(36, 23);
    else
        screenGotoxy(39, 23);

    printf("%d ", ch);  // Imprime o código da tecla
    while (keyhit()) {  // Enquanto houver teclas pressionadas
        printf("%d ", readch());  // Imprime o código dos caracteres adicionais
    }
}


void moverRaqueteDireitaParaCima() {
    if (raqueteDireitaY > MINY + 2) {  // Verifica se não está no limite superior
        raqueteDireitaY--;  // Move para cima

        // Corrigido para garantir que não apaga fora da tela
        if (raqueteDireitaY - 1 >= MINY) {
            screenGotoxy(MAXX - 2, raqueteDireitaY - 1);  // Apaga a posição acima da raquete
            printf(" ");
        }

        // Desenha a raquete na nova posição
        screenGotoxy(MAXX - 2, raqueteDireitaY);  // Parte superior
        printf("|");
        screenGotoxy(MAXX - 2, raqueteDireitaY + 1);  // Parte do meio
        printf("|");
        screenGotoxy(MAXX - 2, raqueteDireitaY + 2);  // Parte inferior
        printf("|");

        // Corrigido para evitar escrever fora da tela
        if (raqueteDireitaY + 3 <= MAXY) {
            screenGotoxy(MAXX - 2, raqueteDireitaY + 3);  // Apaga a posição abaixo da raquete
            printf(" ");  
        }

        screenUpdate();  // Atualiza a tela para refletir mudanças
    }
}


void moverRaqueteDireitaParaBaixo() {
    if (raqueteDireitaY < MAXY - 2) {  // Verifica se não está no limite inferior
        raqueteDireitaY++;  // Move a raquete para baixo
        // Limpa a posição anterior
        screenGotoxy(MAXX - 2, raqueteDireitaY - 2);  // Apaga a parte superior da raquete
        printf(" ");

        // Desenha a nova posição da raquete
        screenGotoxy(MAXX - 2, raqueteDireitaY - 1);  // Posição superior da raquete
        printf("|");
        screenGotoxy(MAXX - 2, raqueteDireitaY);  // Posição do meio da raquete
        printf("|");
        screenGotoxy(MAXX - 2, raqueteDireitaY + 1);  // Posição inferior da raquete
        printf("|");

        screenUpdate();  // Atualiza a tela para mostrar as mudanças
    }
        
        screenGotoxy(24, 12);
        printf("Raquete %d, o minY é %d, o maxy %d", raqueteDireitaY, MINY, MAXY);
        screenUpdate();  // Atualiza a tela,
}

//Raquetes arrow up arrow down
void moverRaqueteEsquerdaParaCima() {
    if (raqueteEsquerdaY > MINY + 2) {  // Verifica se não está no limite superior
        raqueteEsquerdaY--;  // Move para cima
        screenGotoxy(2, raqueteEsquerdaY+2); // Move cursor para a posição da raquete
        printf(" ");
        
        screenGotoxy(2, raqueteEsquerdaY-1);
        printf("|");
        screenGotoxy(2, raqueteEsquerdaY);  // Move cursor para a posição da raquete
        printf("|");
        screenGotoxy(2, raqueteEsquerdaY+1);
        printf("|");

        screenUpdate();
    }
}

void moverRaqueteEsquerdaParaBaixo() {
    if (raqueteEsquerdaY < MAXY - 2) {  // Verifica se não está no limite inferior
        raqueteEsquerdaY++;  // Move para baixo
        screenGotoxy(2, raqueteEsquerdaY-2); // Move cursor para a posição da raquete
        printf(" "); 
        
        screenGotoxy(2,raqueteEsquerdaY+1);
        printf("|");
        screenGotoxy(2, raqueteEsquerdaY);  // Move cursor para a posição da raquete
        printf("|");
        screenGotoxy(2, raqueteEsquerdaY-1);
        printf("|");  


        screenUpdate();  // Atualiza a tela
    }
}

//Para desenvolver a função de colisão precisamos armazenar as cordenadas X e Y atuais da raquete e inverter o movimento da bola caso ela atinga essas coordenadas (eu acho!?)

int main() {
    telaInicio();
    static int ch = 0;  // Variável para armazenar o código da tecla pressionada

    // Inicialização dos sistemas
    screenInit(1);  // Inicializa a tela, talvez com bordas
    keyboardInit();  // Inicializa configurações do teclado
    timerInit(50);  // Inicializa o temporizador com 50 ms

    // Desenha a posição inicial do elemento
    printHello(x, y);
    printRaquetes();

    screenUpdate();  // Atualiza a tela para mostrar mudanças

    // Loop principal do programa
    while (ch != 10) {  // Continua até que "Enter" seja pressionado
        
       
        // Manipulação da entrada do usuário
        if (keyhit()) {  // Se uma tecla foi pressionada

            ch = readch();
            if (ch == 119) {  // Se a tecla for 'W'
                moverRaqueteEsquerdaParaCima();  // Move a raquete para cima
            }if (ch == 115) {  // Se a tecla for 'S'
                moverRaqueteEsquerdaParaBaixo();  // Move a raquete para baixo
            }  // Lê o caractere pressionado

             if (ch == 105) {  // Se a tecla for 'W'
                moverRaqueteDireitaParaCima();  // Move a raquete para cima
            }if (ch == 107) {  // Se a tecla for 'S'
                moverRaqueteDireitaParaBaixo();  // Move a raquete para baixo
            }  // Lê o caractere pressionado
            printKey(ch);
              // Mostra o código da tecla
            screenUpdate();  // Atualiza a tela
        }

        // Atualiza o estado do jogo
        if (timerTimeOver() == 1) {  // Verifica se o temporizador terminou
            int newX = x + incX; 
            int newY = y + incY; 
            if (newX >= (MAXX - 2) || newX <= MINX + 1) {
            incX = -incX;  // Inverte a direção no eixo X

            //if (newX)
    

}

if (newY >= MAXY - 1 || newY <= MINY + 1) {
    incY = -incY;  // Inverte a direção no eixo Y
    
}

            printHello(newX, newY);  // Atualiza a posição do elemento
            screenUpdate();  // Atualiza a tela para mostrar mudanças
        }
    }

    // Limpeza dos sistemas
    keyboardDestroy();  // Restaura configurações do teclado
    screenDestroy();  // Restaura configurações da tela
    timerDestroy();  // Destrói o temporizador

    return 0;  // Sai do programa
}