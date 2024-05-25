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
#include "player.h"
#include <stdlib.h>
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include <sys/time.h>
#include <unistd.h> // Para usar a função sleep
#include "raquete.h"

Player jogadores[MAX_JOGADORES];

typedef struct {
    int x, y;
} Cords;

Cords cord;

int
raquete_direitaY = 10,
raquete_esquerdaY = 10,
incX = 1,
incY = 1;


Cords printHello(int nextX, int nextY) {
    screenSetColor(YELLOW, DARKGRAY);  // Define as cores de texto e fundo
    screenGotoxy(cord.x, cord.y);  // Move o cursor para a posição (x, y)
    printf(" ");  // Limpa o texto anterior
    cord.x = nextX;  // Atualiza a posição x
    cord.y = nextY;  // Atualiza a posição y
    screenGotoxy(cord.x, cord.y);  // Move o cursor para a nova posição
    printf("o");  // Imprime um caractere na nova posição

    return cord;
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



int main() {
    char j1[MAX_NOME], j2[MAX_NOME];
    int escolha = 0;
    Player jogadores[MAX_JOGADORES];
    int total_jogadores = 0;


    while (escolha != 3) {
        telaInicio();
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer do stdin

        switch (escolha) {
            case 1:
                // Inicializar jogo
                printf("Digite o nome do primeiro jogador: ");
                scanf("%s", j1);
                if (!inicializar_jogador(jogadores, total_jogadores, &jogadores[0], j1)) {
                    break; 
                }

                printf("Digite o nome do segundo jogador: ");
                scanf("%s", j2);
                if (!inicializar_jogador(jogadores, total_jogadores, &jogadores[1], j2)) {
                    break; 
                }

                struct timeval tempo;
                struct timeval startTime;

                gettimeofday(&startTime, NULL); // Referencial para obter os segundos
                static int ch = 0;

                cord.x = 40;
                cord.y = 12;
                int pausa_jogo = 0;
                int pausa_score=0;

                // Inicialização dos sistemas
                screenInit(1);  // Inicializa a tela
                keyboardInit();  // Inicializa configurações do teclado
                timerInit(50);  // Inicializa o temporizador com 50 ms


                screenUpdate();

                while (1) {
                    gettimeofday(&tempo, NULL);
                     
                     // Diferença em segundos
                    
                    

                    if (!pausa_jogo && keyhit()) {
                        ch = readch();


                        
                        pausa_tela(&pausa_jogo, &ch); //Deixa a função em standby

                        if (ch == 10) { // ENTER
                            break;
                        }
                        if (ch == 119) {  // 'W'
                            raquete_esquerdaY = raqueteE_up(raquete_esquerdaY);  
                        }
                        if (ch == 115) { //'S'
                            raquete_esquerdaY = raqueteE_down(raquete_esquerdaY);
                        }
                        if (ch == 105) {  // 'I'
                            raquete_direitaY = raqueteD_up(raquete_direitaY);
                        }
                        if (ch == 107) {  // 'K'
                            raquete_direitaY = raqueteD_down(raquete_direitaY);
                        }

                        printKey(ch);
                        screenUpdate();
                    }

                    // Atualiza o estado do jogo
                    if (!pausa_jogo && timerTimeOver() == 1) {  
                    long segundos = tempo.tv_sec - startTime.tv_sec;
                    screenGotoxy(40, 3); 
                    printf("Tempo: %ld\n", GAME_TIME-segundos);
                    //if(GAME_TIME-segundos<=0) break; //Temporizador 60s 
                    

                        int newX = cord.x + incX;
                        int newY = cord.y + incY; //Inclinação da bola horizontal para andar na diagonal

                        if (newX >= (MAXX - 1)) { // Bateu na direita
                            atualizar_gols(&jogadores[0], 1);  // Gol do jogador 1
                            pausa_gol(&pausa_jogo, &ch, &jogadores[0]);
                            resetar(&newX, &newY);
                            incX = -incX;

                        }  if (newX <= MINX + 1) { // Bateu na esquerda
                            atualizar_gols(&jogadores[1], 1);  // Gol do jogador 2
                            pausa_gol(&pausa_jogo, &ch, &jogadores[1]);
                            resetar(&newX,&newY);
                            incX = -incX;

                        }  if (newX == RAQUETE_DISTANCE+2 && (newY == raquete_esquerdaY || newY == raquete_esquerdaY + 1|| newY == raquete_esquerdaY + 2|| newY == raquete_esquerdaY + 3)) { // Colisão raquete lado esquerdo
                            incX = -incX;

                        }  if (newX == MAXX - (RAQUETE_DISTANCE+1) && (newY == raquete_direitaY ||newY == raquete_direitaY+1 || newY == raquete_direitaY+2 ||newY == raquete_direitaY+3)) { // Colisão raquete lado direito
                            incX = -incX;
                        }

                        if (newY >= MAXY - 1 || newY <= MINY + 1) {
                            incY = -incY;  // Inverte a direção no eixo Y se bater em cima
                        }
                        printHello(newX, newY);  // Atualiza a posição da bola
                        screenGotoxy(24, 12);
                        printf("X:%d Y%d", newX, newY);

                        screenGotoxy(3, 3);
                        exibir_pontuacao(&jogadores[0]);
                        screenGotoxy(MAXX-10, 3);

                        exibir_pontuacao(&jogadores[1]);

                        screenUpdate();
                    }
                }

                // Limpeza dos sistemas
                salvar_score(jogadores);
                keyboardDestroy();  // Restaura configurações do teclado
                screenDestroy();  // Restaura configurações da tela
                timerDestroy();  // Destrói o temporizador

                break;
            case 2:
                // Exibir topscores
                carregar_score(jogadores, &total_jogadores);
                qsort(jogadores, total_jogadores, sizeof(Player), comparar_jogadores);
                imprimir_score(jogadores, total_jogadores);
                break;
            case 3:
                // Sair do programa
                printf("Saindo do programa...\n");
                break;
            default:
                system("clear");
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
