#include "player.h"
#include <stdio.h>
#include <string.h>

// Definição da estrutura

void inicializar_jogador(Player *jogador, const char *nome) {
    strcpy(jogador->nome, nome);
    jogador->gols = 0;
}

void atualizar_gols(Player *jogador, int gols) {
    jogador->gols += gols;
}

void exibir_pontuacao(Player *jogador) {
    printf("%s\n", jogador->nome);
    printf("Score: %d", jogador->gols);
}

void salvar_score(Player jogadores[MAX_JOGADORES]) {
    FILE *file = fopen(ARQUIVO, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita");
        return;
    }
    for (int i = 0; i < MAX_JOGADORES; i++) {
        fprintf(file, "%s %d\n", jogadores[i].nome, jogadores[i].gols);
    }
    fclose(file);
}

void carregar_score(Player jogadores[]) {
    FILE *file = fopen(ARQUIVO, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return;
    }
    char linha[100];
    int cont;
    while(fgets(linha, 100, file)){
        cont++;
    }
    int i = 0;
    while (i < MAX_JOGADORES && fscanf(file, "%s %d", jogadores[i].nome, &jogadores[i].gols) != EOF) {
        i++;
    }
    fclose(file);
}

