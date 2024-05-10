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
#include <sys/time.h>

int raqueteDireitaY = 10;
int raqueteEsquerdaY=10; 

 // Posição inicial da raquete
 typedef struct {
    int score;
    char name[50];
 }Player;

 Player A_player;
 Player B_player;

typedef struct{
int x;
int y;      // Posição inicial da bola na tela (x, y)
}Cords;
Cords cord;

int incX = 1;
int incY = 1;

Cords printHello(int nextX, int nextY) {
    screenSetColor(YELLOW, DARKGRAY);  // Define as cores de texto e fundo
    screenGotoxy(cord.x, cord.y);  // Move o cursor para a posição (x, y)
    printf(" ");  // Limpa o texto anterior
    cord.x = nextX;  // Atualiza a posição x
    cord.y = nextY;  // Atualiza a posição y
    screenGotoxy(cord.x, cord.y);  // Move o cursor para a nova posição
    printf("o");  // Imprime um caractere na nova posição (originalmente um HelloWorld)

    return cord;

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


    

    if (ch == 27)  // Se o código for o de "Esc", ajusta a posição
        screenGotoxy(36, 23);
    else
        screenGotoxy(39, 23);

    printf("%d ", ch);  // Imprime o código da tecla
    while (keyhit()) {  // Enquanto houver teclas pressionadas
        printf("%d ", readch());  // Imprime o código dos caracteres adicionais
    }
}


// Corrige a função para mover a raquete para cima sem apagar fora dos limites da tela
int moverRaqueteDireitaParaCima() {
    
        if (raqueteDireitaY > MINY + 4 ) {  // Apenas apaga se não estiver na parte superior da raquete
            screenGotoxy(MAXX - 2, raqueteDireitaY);  // Apaga a o ultimo pixel da raquete
            printf(" ");
            screenGotoxy(MAXX - 2, raqueteDireitaY + 1);  // Apaga a o ultimo pixel da raquete
            printf(" ");
            screenGotoxy(MAXX - 2, raqueteDireitaY + 2);  // Apaga a o ultimo pixel da raquete
            printf(" ");
            screenGotoxy(MAXX - 2, raqueteDireitaY + 3);  // Apaga a o ultimo pixel da raquete
            printf(" ");
            


        
        
        raqueteDireitaY-=3;  // Move para cima miny-4=

        // Desenha a nova posição da raquete
        screenGotoxy(MAXX - 2, raqueteDireitaY);  // Parte superior
        printf("Y");
        screenGotoxy(MAXX - 2, raqueteDireitaY + 1);  // Parte do meio
        printf("|");
        screenGotoxy(MAXX - 2, raqueteDireitaY + 2);  // Parte inferior
        printf("|");
        screenGotoxy(MAXX - 2, raqueteDireitaY + 3);  // Parte inferior
        printf("|");
        screenUpdate();  // Atualiza a tela para refletir as mudanças
    }
    return raqueteDireitaY;
}

// Corrige a função para mover a raquete para baixo sem apagar fora dos limites da tela
int moverRaqueteDireitaParaBaixo() {
    if (raqueteDireitaY < MAXY - 2) {
          // Verifica se não está no limite inferior
        
        screenGotoxy(MAXX - 2, raqueteDireitaY);  //Precisa apagar o primeiro pixel da raquete
        printf(" ");
        screenGotoxy(MAXX - 2, raqueteDireitaY+1);  //Precisa apagar o primeiro pixel da raquete
        printf(" ");
        screenGotoxy(MAXX - 2, raqueteDireitaY+2);  //Precisa apagar o primeiro pixel da raquete
        printf(" ");
        screenGotoxy(MAXX - 2, raqueteDireitaY+3);  //Precisa apagar o primeiro pixel da raquete
        printf(" ");        
        
        raqueteDireitaY+=3;  // Move para baixo
        
        // Desenha a nova posição da raquete
        screenGotoxy(MAXX - 2, raqueteDireitaY );  // Posição superior
        printf("Y");
        screenGotoxy(MAXX - 2, raqueteDireitaY+1);  // Posição do meio
        printf("|");
        screenGotoxy(MAXX - 2, raqueteDireitaY + 2);  // Posição inferior
        printf("|");
        screenGotoxy(MAXX - 2, raqueteDireitaY + 3);  // Posição inferior
        printf("|");
        screenUpdate();  // Atualiza a tela para mostrar as mudanças
    


        screenUpdate();  // Atualiza a tela,
    }
    return raqueteDireitaY;
}

//Raquetes arrow up arrow down
int moverRaqueteEsquerdaParaCima() {

    if (raqueteEsquerdaY > MINY + 1) {// Verifica se não está no limite superior
        screenGotoxy(2, raqueteEsquerdaY+2); //Apaga o pixel da ultima parte da raquete
        printf(" ");
        screenGotoxy(2, raqueteEsquerdaY+1); //Apaga o pixel da ultima parte da raquete
        printf(" ");
        screenGotoxy(2, raqueteEsquerdaY); //Apaga o pixel da ultima parte da raquete
        printf(" ");
        raqueteEsquerdaY-=3;  // Move para cima



        screenGotoxy(2, raqueteEsquerdaY);          // Referencia do nosso Y
        printf("Y");
        screenGotoxy(2, raqueteEsquerdaY+1);
        printf("|");
        screenGotoxy(2, raqueteEsquerdaY+2);
        printf("|");

        screenUpdate();
    }
    return raqueteEsquerdaY;
}

int moverRaqueteEsquerdaParaBaixo() {
    if (raqueteEsquerdaY < MAXY - 3) {// Verifica se não está no limite inferior

        screenGotoxy(2, raqueteEsquerdaY); // Move cursor para a posição da raquete
        printf(" ");
        screenGotoxy(2, raqueteEsquerdaY+1); // Move cursor para a posição da raquete
        printf(" ");
        screenGotoxy(2, raqueteEsquerdaY+2); // Move cursor para a posição da raquete
        printf(" ");


        raqueteEsquerdaY+=3;// Move para baixo 3 pixels

 
        screenGotoxy(2, raqueteEsquerdaY);  // Move cursor para a posição da raquete
        printf("Y");
        screenGotoxy(2, raqueteEsquerdaY+1);
        printf("|");  
        screenGotoxy(2, raqueteEsquerdaY+2);
        printf("|");    



        screenUpdate();  // Atualiza a tela
    }
    return raqueteEsquerdaY;
}

//Para desenvolver a função de colisão precisamos armazenar as cordenadas X e Y atuais da raquete e inverter o movimento da bola caso ela atinga essas coordenadas (eu acho!?)

int main() {
    struct timeval startTime; // Para armazenar o tempo de início
    gettimeofday(&startTime, NULL); // Obtemos o tempo atual para começar o cronômetro
    static int ch = 0;  // Variável para armazenar o código da tecla pressionada
    A_player.score=0;
    B_player.score=0;
    cord.x=40;
    cord.y=12;
    incX=1;
    incY=1;
    // Inicialização dos sistemas
    screenInit(1);  // Inicializa a tela, talvez com bordas
    keyboardInit();  // Inicializa configurações do teclado
    timerInit(50);  // Inicializa o temporizador com 50 ms

    // Desenha a posição inicial do elemento
    printHello(cord.x, cord.y);
    printRaquetes();

    screenUpdate();  // Atualiza a tela para mostrar mudanças

    // Loop principal do programa
    while (1) {  // Continua até que "Enter" seja pressionado
         struct timeval currentTime; // Para capturar o tempo atual
        gettimeofday(&currentTime, NULL); // Obtemos o tempo atual
        
        long elapsedSeconds = currentTime.tv_sec - startTime.tv_sec; // Diferença em segundos
        screenGotoxy(40, 3);
        printf("%ld", elapsedSeconds);
        if(ch == 10) break;

        // Manipulação da entrada do usuário
        if (keyhit()) {  // Se uma tecla foi pressionada

            ch = readch();

            if (ch == 119) {  // Se a tecla for 'W'
                raqueteEsquerdaY= moverRaqueteEsquerdaParaCima();  // Move a raquete para cima
            }if (ch == 115) {  // Se a tecla for 'S'
                raqueteEsquerdaY = moverRaqueteEsquerdaParaBaixo();  // Move a raquete para baixo
            }  // Lê o caractere pressionado

             if (ch == 105) {  // Se a tecla for 'W'
                raqueteDireitaY= moverRaqueteDireitaParaCima();  // Move a raquete para cima
                
            }if (ch == 107) {  // Se a tecla for 'S'
                raqueteDireitaY= moverRaqueteDireitaParaBaixo();  // Move a raquete para baixo
            }  // Lê o caractere pressionado
            printKey(ch);
            screenGotoxy(24, 12);

              // Mostra o código da tecla

            screenUpdate();  // Atualiza a tela
        }

        // Atualiza o estado do jogo
        if (timerTimeOver() == 1) {  // Verifica se o temporizador terminou
            int newX = cord.x + incX; 
            int newY = cord.y + incY; //Inclinação da bola horizontal para andar na diagonal


            if (newX >= (MAXX - 1)||newX <= MINX + 1) {
                incX=-incX;
                if(newX >= (MAXX - 1)) A_player.score++; //BATEU NA ESQUERDA

                else if(newX <= MINX + 1) B_player.score++;//BATEU NA DIREITA
            // Inverte a direção no eixo X
            }
            if (newY >= MAXY - 1 || newY <= MINY + 1) {
                incY = -incY;  // Inverte a direção no eixo Y
            }

            else if((newX >= raqueteEsquerdaY && newY <= raqueteEsquerdaY+2)&&newX == 2){//COLISÃO LADO ESQUERDO
                incX=-incX;
                incY=-incY;
                

                }
            else if((newX >= raqueteDireitaY && newY <= raqueteDireitaY+2)&&newX == MAXX-2){//COLISÃO LADO DIREITO
               
                incX=-incX;
                incY=-incY;

                }
                
            printHello(newX, newY);  // Atualiza a posição do elemento
            screenGotoxy(24, 4);
            printf("X: %d Y: %d", newX, newY);
            screenUpdate();  // Atualiza a tela para mostrar mudanças
        }
    }

    // Limpeza dos sistemas
    keyboardDestroy();  // Restaura configurações do teclado
    screenDestroy();  // Restaura configurações da tela
    timerDestroy();  // Destrói o temporizador

    return 0;  // Sai do programa
}