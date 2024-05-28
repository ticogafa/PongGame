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

typedef struct {
    int x, y;
    int ativa;
} Bala;

Bala bala_esquerda = {0, 0, 0};  // Bala disparada pela raquete esquerda
Bala bala_direita = {0, 0, 0};   // Bala disparada pela raquete direita

int raquete_direitaY = 10,
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
    printf("᳂");  // Imprime um caractere na nova posição

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

int atualizar_bala(Bala* bala, int incX) {
    int bala_direita_gol=0;
    int bala_esquerda_gol=0;
    if (bala->ativa) {
        // Limpa a posição anterior da bala
        screenGotoxy(bala->x, bala->y);
        printf(" ");

        // Atualiza a posição da bala
        bala->x += incX;

        // Verifica colisão com as bordas da tela
        if (bala->x >= MAXX || bala->x <= MINX) {
            bala->ativa = 0;  // Desativa a bala ao sair da tela
        }
        // Verifica colisão da bala esquerda com a raquete direita
        else if (bala == &bala_esquerda &&
                 bala->x == MAXX - (RAQUETE_DISTANCE + 1) &&
                 (bala->y >= raquete_direitaY && bala->y <= raquete_direitaY + 3)) {
            bala->ativa = 0;
            atualizar_gols(&jogadores[1], 1);  // Pontuação para o jogador 1 (direita)
            bala_esquerda_gol=1;
            return bala_esquerda_gol;
        }
        // Verifica colisão da bala direita com a raquete esquerda
        else if (bala == &bala_direita &&
                    bala->x == RAQUETE_DISTANCE + 2 &&
                 (bala->y >= raquete_esquerdaY && bala->y <= raquete_esquerdaY + 3)) {
            bala->ativa = 0;
            bala_direita_gol=1;
            atualizar_gols(&jogadores[0], 1);  // Pontuação para o jogador 0 (esquerda)
            return bala_direita_gol;
            
        }
        // Se não houve colisão, desenha a bala na nova posição
        else {
            screenGotoxy(bala->x, bala->y);
            printf("-");  // Desenha a bala na nova posição
        }
    }
}

int main() {
    char j1[MAX_NOME], j2[MAX_NOME];
    int escolha = 0;
    Player jogadores[MAX_JOGADORES];
    int total_jogadores = 0;
    int contador_incial = 0;
    struct timeval tempo;
    struct timeval startTime;
   
    
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



                
                gettimeofday(&startTime, NULL); // Referencial para obter os segundos
                static int ch = 0;

                cord.x = 40;
                cord.y = 12;
                int pausa_jogo = 0;
                int pausa_score = 0;
                int modo_tiro = 0;
                int bala_direita_gol=0;
                int bala_esquerda_gol=0;

                // Inicialização dos sistemas
                screenInit(1);  // Inicializa a tela
                keyboardInit();  // Inicializa configurações do teclado
                timerInit(50);  // Inicializa o temporizador com 50 ms
                screenUpdate();

                while (1) {
                    gettimeofday(&tempo, NULL);
                    long segundos = tempo.tv_sec - startTime.tv_sec;
                    long tempo_jogo=GAME_TIME-segundos;

                    if (segundos >= 25 && segundos < 30) {
                        screenGotoxy(25, 3);
                        printf("SHOWDOWN COMEÇA EM %ld", tempo_jogo-30);
                    } 
                    
                    else if (segundos == 30) {
                        screenGotoxy(25, 3);
                        printf("                                     ");
                    }
                    else if((segundos>30&&segundos<60) || segundos<25){
                    
                    screenGotoxy(40, 3);
                    printf("%ld", tempo_jogo);
                    screenUpdate();
                    if(segundos>30&&segundos<60){
                        modo_tiro=1;
                    }
                    }


                     if(tempo_jogo<0){
                         int resultado = ganhador(jogadores[0], jogadores[1]);
                        timerDestroy();
                        if (resultado == 0) {
                            screenGotoxy(20, 5); 
                            printf("O jogador %s é o vencedor! aperte C para sair", jogadores[0].nome);
                            if(ch==99) break;   
                          
                            
                        } else if (resultado == 1) {
                            screenGotoxy(20, 5);
                            printf("O jogador %s é o vencedor! aperte C para sair", jogadores[1].nome);
                            if(ch==99) break;
                            
                        } else if(resultado==-1) {
                            screenGotoxy(40, 5);
                            printf("Houve um empate! ! aperte C para sair");
                            if(ch==99) break;
            
                        }
                    }

                    if (!pausa_jogo && keyhit()) {
                        ch = readch();

                        segundos=pausa_tela(&pausa_jogo, &ch, &startTime, segundos); //Deixa a função em standby
                        
                        if (ch == 10) { // ENTER
                            break;
                        }
                        if (ch == 119) {  // 'W'
                            raquete_esquerdaY = raqueteE_up(raquete_esquerdaY, modo_tiro); 
                        }
                        if (ch == 115) { //'S'
                            raquete_esquerdaY = raqueteE_down(raquete_esquerdaY, modo_tiro);
                        }
                        if (ch == 105) {  // 'I'
                            raquete_direitaY = raqueteD_up(raquete_direitaY, modo_tiro);
                        }
                        if (ch == 107) {  // 'K'
                            raquete_direitaY = raqueteD_down(raquete_direitaY, modo_tiro);
                        }
                        if (modo_tiro) {
                            if (ch == 97 && !bala_esquerda.ativa) {  // 'A' para atirar da raquete esquerda
                                bala_esquerda.x = RAQUETE_DISTANCE + 2;
                                bala_esquerda.y = raquete_esquerdaY + 1;
                                bala_esquerda.ativa = 1;
                            }
                            if (ch == 108 && !bala_direita.ativa) {  // 'L' para atirar da raquete direita
                                bala_direita.x = MAXX - (RAQUETE_DISTANCE + 1);
                                bala_direita.y = raquete_direitaY + 1;
                                bala_direita.ativa = 1;
                            }
                        }

                        //printKey(ch);
                        screenUpdate();
                    }

                    // Atualiza o estado do jogo
                    if (!pausa_jogo && timerTimeOver() == 1) {  
                        
                        if (!modo_tiro) {
                            int newX = cord.x + incX;
                            int newY = cord.y + incY; //Inclinação da bola horizontal para andar na diagonal

                            if (newX >= (MAXX - 1)) { // Bateu na direita
                                atualizar_gols(&jogadores[0], 1);  // Gol do jogador 1
                               segundos= pausa_gol(&pausa_jogo, &ch, &jogadores[0], &startTime, segundos);
                                resetar(&newX, &newY);
                                countdown(1);
                                incX = -incX;

                            }  if (newX <= MINX + 1) { // Bateu na esquerda
                                atualizar_gols(&jogadores[1], 1);  // Gol do jogador 2
                                segundos=pausa_gol(&pausa_jogo, &ch, &jogadores[1], &startTime, segundos);
                                resetar(&newX,&newY);
                                countdown(1);
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



                        } else {//MODO TIRO ATIVADO
                            timerInit(12);
                            
                            if(bala_esquerda_gol=atualizar_bala(&bala_esquerda, 1)==1) {
                                atualizar_gols(&jogadores[0], 1);
                                raqueteD_piscar(raquete_direitaY, modo_tiro);

                            } // Atualiza a bala disparada pela raquete esquerda
                            if (bala_direita_gol=atualizar_bala(&bala_direita, -1)==1){
                                atualizar_gols(&jogadores[1], 1);
                                raqueteE_piscar(raquete_esquerdaY, modo_tiro);
                            }  // Atualiza a bala disparada pela raquete direita
                        }

                        screenGotoxy(3, 3);
                        exibir_pontuacao(&jogadores[0]);
                        screenGotoxy(MAXX-20, 3);
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