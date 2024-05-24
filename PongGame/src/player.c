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
void carregar_score(Player jogadores[], int *total_jogadores) {
    FILE *file = fopen(ARQUIVO, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return;
    }

    *total_jogadores = 0;
    char linha[100];
    while (fgets(linha, sizeof(linha), file) != NULL) {
        (*total_jogadores)++;
    }
    rewind(file); // Voltar ao início do arquivo

    for (int i = 0; i < *total_jogadores; i++) {
        if (fscanf(file, "%s %d", jogadores[i].nome, &jogadores[i].gols) != 2) {
            fprintf(stderr, "Erro ao ler dados do arquivo\n");
            fclose(file);
            return;
        }
    }
    fclose(file);
}

int comparar_jogadores(const void *a, const void *b) {
    const Player *jogador_a = (const Player *)a;
    const Player *jogador_b = (const Player *)b;
    
    // Comparar pelo número de gols (em ordem decrescente)
    return jogador_b->gols - jogador_a->gols;
}

void imprimir_score(Player jogadores[], int total_jogadores) {
    printf("Ranking dos jogadores:\n");
    for (int i = 0; i < total_jogadores; i++) {
        printf("%d. Jogador: %s - Gols: %d\n", i+1, jogadores[i].nome, jogadores[i].gols);
    }
}