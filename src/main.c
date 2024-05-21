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
 typedef struct Player {
    char nome[50];
    int score;
    struct Player *next;
} Player;


 Player A_player;
 Player B_player;

typedef struct{
int x;
int y;      // Posição inicial da bola na tela (x, y)
}Cords;
Cords cord;

int incX = 1;
int incY = 1;


void telaInicio() {
    system("clear"); // Limpa a tela
    
    printf("\n\n\n");
    printf("       JOGO DO PONG\n\n");
    printf("   Instruções:\n");
    printf("   - Use as teclas W e S para mover a raquete esquerda\n");
    printf("   - Use as teclas I e K para mover a raquete direita\n");
    printf("   - Pressione qualquer tecla para começar o jogo\n");
    printf("   - Cadastre seu nome e se divirta!!\n");
    printf("   -Para sair no meio do jogo, pressione ENTER, para pausar pressione ESC\n\n");
    printf("   Boa sorte!\n\n");

    getchar(); // Aguarda o jogador pressionar uma tecla
    
    

}

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
    
        if (raqueteDireitaY > MINY + 2 ) {  // Apenas apaga se não estiver na parte superior da raquete
            screenGotoxy(MAXX - 2, raqueteDireitaY);  // Apaga a o ultimo pixel da raquete
            printf(" ");
            screenGotoxy(MAXX - 2, raqueteDireitaY + 1);  // Apaga a o ultimo pixel da raquete
            printf(" ");
            screenGotoxy(MAXX - 2, raqueteDireitaY + 2);  // Apaga a o ultimo pixel da raquete
            printf(" ");
            screenGotoxy(MAXX - 2, raqueteDireitaY + 3);  // Apaga a o ultimo pixel da raquete
            printf(" ");
            
        raqueteDireitaY-=2;  // Move para cima miny-4=

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
    if (raqueteDireitaY < MAXY - 5) {
          // Verifica se não está no limite inferior
        
        screenGotoxy(MAXX - 2, raqueteDireitaY+3);  //Precisa apagar o primeiro pixel da raquete
        printf(" ");
        screenGotoxy(MAXX - 2, raqueteDireitaY+2);  //Precisa apagar o primeiro pixel da raquete
        printf(" ");
        screenGotoxy(MAXX - 2, raqueteDireitaY+1);  //Precisa apagar o primeiro pixel da raquete
        printf(" ");
        screenGotoxy(MAXX - 2, raqueteDireitaY);  //Precisa apagar o primeiro pixel da raquete
        printf(" ");        
        
        raqueteDireitaY+=2;  // Move para baixo
        
        // Desenha a nova posição da raquete
        screenGotoxy(MAXX - 2, raqueteDireitaY+3);  // Posição superior
        printf("Y");
        screenGotoxy(MAXX - 2, raqueteDireitaY+2);  // Posição do meio
        printf("|");
        screenGotoxy(MAXX - 2, raqueteDireitaY + 1);  // Posição inferior
        printf("|");
        screenGotoxy(MAXX - 2, raqueteDireitaY);  // Posição inferior
        printf("|");
        screenUpdate();  // Atualiza a tela para mostrar as mudanças
    


        screenUpdate();  // Atualiza a tela,
    }
    return raqueteDireitaY;
}

//Raquetes arrow up arrow down
int moverRaqueteEsquerdaParaCima() {

    if (raqueteEsquerdaY > MINY + 2) {// Verifica se não está no limite superior
        screenGotoxy(2, raqueteEsquerdaY+1); //Apaga o pixel da ultima parte da raquete
        printf(" ");
        screenGotoxy(2, raqueteEsquerdaY+2); //Apaga o pixel da ultima parte da raquete
        printf(" ");
        screenGotoxy(2, raqueteEsquerdaY+3); //Apaga o pixel da ultima parte da raquete
        printf(" ");
        screenGotoxy(2, raqueteEsquerdaY); //Apaga o pixel da ultima parte da raquete
        printf(" ");        
        raqueteEsquerdaY-=2;  // Move para cima



        screenGotoxy(2, raqueteEsquerdaY);          // Referencia do nosso Y
        printf("Y");
        screenGotoxy(2, raqueteEsquerdaY+1);
        printf("|");
        screenGotoxy(2, raqueteEsquerdaY+2);
        printf("|");
        screenGotoxy(2, raqueteEsquerdaY+3);
        printf("|");        

        screenUpdate();
    }
    return raqueteEsquerdaY;
}

int moverRaqueteEsquerdaParaBaixo() {
    if (raqueteEsquerdaY < MAXY - 5) {// Verifica se não está no limite inferior

        screenGotoxy(2, raqueteEsquerdaY+3); // Move cursor para a posição da raquete
        printf(" ");
        screenGotoxy(2, raqueteEsquerdaY+2); // Move cursor para a posição da raquete
        printf(" ");
        screenGotoxy(2, raqueteEsquerdaY+1); // Move cursor para a posição da raquete
        printf(" ");
        screenGotoxy(2, raqueteEsquerdaY); // Move cursor para a posição da raquete
        printf(" ");        


        raqueteEsquerdaY+=2;// Move para baixo 2 pixels

 
        screenGotoxy(2, raqueteEsquerdaY+3);  // Move cursor para a posição da raquete
        printf("Y");
        screenGotoxy(2, raqueteEsquerdaY+2);
        printf("|");  
        screenGotoxy(2, raqueteEsquerdaY+1);
        printf("|");
        screenGotoxy(2, raqueteEsquerdaY);
        printf("|");               

        

        screenUpdate();  // Atualiza a tela
    }
    return raqueteEsquerdaY;
}

void pausa(int *pausa, int *ch, int numCaracteres) {
    if (*ch == 27) { // Se a tecla "ESC" for pressionada, alterna o estado de pausa
        *pausa = !(*pausa);
        *ch = 0; // Limpa a tecla pressionada para evitar que a ação de pausa seja executada várias vezes
    }
    if (*pausa) {
        screenGotoxy(10, 10);
        printf("Jogo pausado. Pressione 'C' para continuar.");
        screenUpdate();
        while (*ch != 99) {  // Espera até que a tecla 'C' seja pressionada 
            if (keyhit()) { // Verifica se alguma tecla foi pressionada
                *ch = readch(); // Checa qual tecla foi pressionada, caso tenha sido 'C', o while é interrompido
            }
        }
        *pausa = 0; // Sai da pausa ao pressionar 'C'
        *ch = 0; // Limpa a tecla pressionada para evitar que a ação de despausar seja executada várias vezes
        screenGotoxy(10, 10); // Posiciona o cursor na posição onde o printf foi feito
        for (int i = 0; i < numCaracteres; i++) {
            printf(" "); // Sobrescreve os caracteres com espaços em branco
        }
        screenUpdate(); // Atualiza a tela para mostrar as mudanças
    }
}


void pausagol(int *pausa, int *ch, int numCaracteres) {
    pausa !=pausa;
    if (*pausa) {
        screenGotoxy(10, 10);
        printf("GOOOLL! para continuar aperte C");
        screenUpdate();
        while (*ch != 99) {  // Espera até que a tecla 'C' seja pressionada 
            if (keyhit()) { // Verifica se alguma tecla foi pressionada
                *ch = readch(); // Checa qual tecla foi pressionada, caso tenha sido 'C', o while é interrompido
            }
        }
        *pausa = 0; // Sai da pausa ao pressionar 'C'
        *ch = 0; // Limpa a tecla pressionada para evitar que a ação de despausar seja executada várias vezes
        screenGotoxy(10, 10); // Posiciona o cursor na posição onde o printf foi feito
        for (int i = 0; i < numCaracteres; i++) {
            printf(" "); // Sobrescreve os caracteres com espaços em branco
        }
        screenUpdate(); // Atualiza a tela para mostrar as mudanças
    }
}


void ler(Player *nomes) {
  FILE *fp;
  fp = fopen("pontuacao.txt", "r"); // Abre o arquivo em modo leitura ("r")
  char ch;
  
  if (fp != NULL) {  // Verifica se o arquivo foi aberto com sucesso
    while ((ch = fgetc(fp)) != EOF) { // Lê e imprime caractere por caractere
      putchar(ch);
    }

    fclose(fp);  // Fecha o arquivo após a leitura
  } else {
    printf("Falha ao abrir o arquivo.\n");
  }
}

int checagem(const char *nome) {
    FILE *fp;
    fp = fopen("pontuacao.txt", "r"); // Abre o arquivo em modo leitura ("r")
    char linha[100]; // Assumindo que cada linha tem no máximo 100 caracteres
    int encontrado = 0;

    if (fp != NULL) {  // Verifica se o arquivo foi aberto com sucesso
        while (fgets(linha, sizeof(linha), fp) != NULL) {
            // Remove a quebra de linha do final da linha lida
            linha[strcspn(linha, "\n")] = '\0';

            // Compara o nome lido do arquivo com o nome fornecido
            if (strcmp(linha, nome) == 0) {
                encontrado = 1;  // Marca como encontrado se os nomes forem iguais
                break;  // Sai do loop se o nome for encontrado
            }
        }
        fclose(fp);  // Fecha o arquivo após a leitura
    } else {
        printf("Falha ao abrir o arquivo.\n");
    }

    return encontrado;  // Retorna 1 se o nome foi encontrado, 0 se não
}


void escrever(Player *head) {
    FILE *fp;
    fp = fopen("pontuacao.txt", "a");
    
    if (fp != NULL) {  // Verifica se o arquivo foi aberto com sucesso
        Player *current = head;
        while (current != NULL) {
            fprintf(fp, "Nome: %s, Pontuação: %d\n", current->nome, current->score);
            current = current->next;
        }
        fclose(fp);  // Fecha o arquivo após o uso
    } else {
        printf("Falha ao abrir o arquivo.\n");
    }
}

void adicionar_jogador(Player **head, char *nome, int score) {
    int flag = 0;
    while (flag != 1) {
    if (!checagem(nome)) {  // Verifica se o nome não existe no arquivo
        Player *new_player = (Player *)malloc(sizeof(Player));
        if (new_player != NULL) {
            snprintf(new_player->nome, sizeof(new_player->nome), "%s", nome);
            new_player->score = score;
            new_player->next = *head;
            *head = new_player;
            printf("Jogador %s adicionado com sucesso!\n", nome);
            flag = 1;
        } else {
            printf("Falha ao alocar memória para o novo jogador.\n");
        }
    } 
    else {
        printf("O nome %s já existe. Por favor, insira outro nome.\n", nome);
        printf("Novo nome: ");
        scanf("%s", nome);
    }
    }
}




void resetar(Cords *cord,int x,int y) {
    cord->x = x;  // Posição inicial da bola (x)
    cord->y = y;  // Posição inicial da bola (y)
    int raqueteDireitaY = 10;  // Posição inicial da raquete direita
    int raqueteEsquerdaY = 10;  // Posição inicial da raquete esquerda
}


//Para desenvolver a função de colisão precisamos armazenar as cordenadas X e Y atuais da raquete e inverter o movimento da bola caso ela atinga essas coordenadas (eu acho!?)

int main() {
    Player *head = NULL;
    Player A_player;
    Player B_player;
    int checar;
    A_player.score=0;
    B_player.score=0;
    
    telaInicio();
    
    while (1) {
        for (int i = 0; i < 4; i++) {
            if (i == 1) {
                printf("Digite o nome de jogador do lado A: ");
                scanf("%s", A_player.nome);
                ler(&A_player);
                adicionar_jogador(&head, A_player.nome, A_player.score);// adiciona os jogadores ao arquivo txt pontuacao
            }
            if (i == 2) {
                printf("Digite o nome de jogador do lado B: ");
                scanf("%s", B_player.nome);
                ler(&B_player);//le os jogadores
                adicionar_jogador(&head, B_player.nome, B_player.score);// adiciona os jogadores ao arquivo txt pontuacao
                }
            if (i == 3) {
                break;
            }
        }
        escrever(head);// Escreve os dados dos jogadores no arquivo após cada ciclo
        break;
        //aq posso colocar uma condição para sair e ir para o jogo
    }

    // Libera a memória alocada para a lista de jogadores
    Player *current = head;
    while (current != NULL) {
        Player *temp = current;
        current = current->next;
        free(temp);
    }
    
    struct timeval startTime; // Para armazenar o tempo de início
    gettimeofday(&startTime, NULL); // Obtemos o tempo atual para começar o cronômetro
    static int ch = 0;  // Variável para armazenar o código da tecla pressionada
    cord.x=40;
    cord.y=12;
    incX=1;
    incY=1;
    int pausa_jogo=0;
    int numCaracteres = 43;
    int pontuação;
    
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
        struct timeval tempo ; // Para capturar o tempo atual
        gettimeofday(&tempo, NULL); // Obtemos o tempo atual
        long elapsedSeconds = tempo.tv_sec - startTime.tv_sec; // Diferença em segundos
        screenGotoxy(40, 3);
       pausa(&pausa_jogo, &ch, numCaracteres);//função para pausar o jogo
        // Manipulação da entrada do usuário
        if (!pausa_jogo && keyhit()) {  // Se uma tecla foi pressionada e o jogo não está pausado
            ch = readch();
            if(ch == 10){//tentativa de reiniciar o jogo com o enter
                break;
            }
            if (ch == 119) {  // Se a tecla for 'W'
                raqueteEsquerdaY= moverRaqueteEsquerdaParaCima();  // Move a raquete para cima
                if (ch == 119) {  // Se a tecla for 'W'
                if (raqueteEsquerdaY > MINY + 1) { // Verifica se a raquete não está no limite superior
                    raqueteEsquerdaY = moverRaqueteEsquerdaParaCima();  // Move a raquete para cima
                }
                } 
            } else if (ch == 115) {  // Se a tecla for 'S'
                raqueteEsquerdaY = moverRaqueteEsquerdaParaBaixo();  // Move a raquete para baixo
            }  // Lê o caractere pressionado

             if (ch == 105) {  // Se a tecla for 'I'
                raqueteDireitaY= moverRaqueteDireitaParaCima();  // Move a raquete para cima
                
            }if (ch == 107) {  // Se a tecla for 'K'
                raqueteDireitaY= moverRaqueteDireitaParaBaixo();  // Move a raquete para baixo
            }
            printKey(ch);
            screenUpdate();  // Atualiza a tela
        }
        // Atualiza o estado do jogo
        if (!pausa_jogo && timerTimeOver() == 1) {  // Verifica se o temporizador terminou e o jogo não está pausado
            int newX = cord.x + incX; 
            int newY = cord.y + incY; //Inclinação da bola horizontal para andar na diagonal

            if (newX >= (MAXX - 1) || newX <= MINX + 1) {
                incX=-incX;
                if (newX >= (MAXX - 1)){
                A_player.score++;//BATEU NA ESQUERDA
                pausagol(&pausa_jogo, &ch, numCaracteres);//função para pausar o jogo
               
                }
                else if (newX <= MINX + 1){
                B_player.score++;//BATEU NA DIREITA
                pausagol(&pausa_jogo, &ch, numCaracteres);//função para pausar o jogo
               
                } 
            }

            if (newY >= MAXY - 1 || newY <= MINY + 1) {
                incY = -incY;  // Inverte a direção no eixo Y
            } else if ((newX >= 2 && newX <= 3) && (newY >= raqueteEsquerdaY && newY <= raqueteEsquerdaY + 2)) { //COLISÃO LADO ESQUERDO
                incX=-incX;
                incY=-incY;
            } else if ((newX >= MAXX - 4 && newX <= MAXX - 3) && (newY >= raqueteDireitaY && newY <= raqueteDireitaY + 2)) { //COLISÃO LADO DIREITO
                incX=-incX;
                incY=-incY;
            }

            printHello(newX, newY);  // Atualiza a posição do elemento
            screenGotoxy(24, 4);
            printf("X: %d Y: %d", newX, newY);
            screenGotoxy(24, 3);
            printf("A: %d B: %d", A_player.score, B_player.score);

            screenUpdate();  // Atualiza a tela para mostrar mudanças
        }
    }

    // Limpeza dos sistemas
    keyboardDestroy();  // Restaura configurações do teclado
    screenDestroy();  // Restaura configurações da tela
    timerDestroy();  // Destrói o temporizador

    return 0;  // Sai do programa
}
