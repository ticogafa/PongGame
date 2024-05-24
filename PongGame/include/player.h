#ifndef __PLAYER_H__
#define __PLAYER_H__

#define MAX_JOGADORES 2  // Número de jogadores
#define MAX_NOME 50      // Tamanho máximo do nome do jogador
#define ARQUIVO "scores.txt"  // Nome do arquivo de pontuação

typedef struct {
    char nome[MAX_NOME];
    int gols;
} Player;


void inicializar_jogador(Player *jogador, const char *nome);

void atualizar_gols(Player *jogador, int gols);

void exibir_pontuacao(Player *jogador);

void salvar_score(Player jogadores[]);

void carregar_score(Player jogadores[]);

void exibir_topscores(Player jogadores[]);
#endif 