#include "player.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_JOGADORES 100

// Definição da estrutura
typedef struct Node { // Define a lista encadeada
    Player jogador;
    struct Node *prox;
} Node;

// Função para carregar jogadores do arquivo e armazenar em uma lista encadeada
void carregar_jogadores(Node **head, int *total_jogadores) {
    // Abrir arquivo para leitura
    FILE *file = fopen(ARQUIVO, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para leitura"); // Imprime a mensagem de erro
        *total_jogadores = 0; // Zera o total de jogadores
        return; 
    }

    *total_jogadores = 0; // Inicializa o total de jogadores como zero
    Node *current = NULL; // Ponteiro para o nó atual, NULL inicialmente
    while(1) {
        Node *new_node = malloc(sizeof(Node)); // Aloca memória para o novo nó
        if (fscanf(file, "%s %d", new_node->jogador.nome, &new_node->jogador.gols) != 2) { // Se não puder ler dois valores (nome e gols), libera a memória do nó e sai do loop
            free(new_node); 
            break;
        }
        new_node->prox = NULL; // Define o ponteiro para o próximo nó como NULL

        // Insere o novo nó na lista encadeada
        if (*head == NULL) {
            *head = new_node; // Se a lista estiver vazia, o novo nó é o primeiro
        } else {
            current->prox = new_node; // Se não, o novo nó é o próximo do nó atual
        }
        current = new_node; // O nó atual passa a ser o novo nó
        (*total_jogadores)++; // Incrementa o total de jogadores
    }

    fclose(file);
}

// Função para inicializar um jogador
int inicializar_jogador(Player jogadores[], int total_jogadores, Player *novo_jogador, const char *nome) {
    // Carregar jogadores do arquivo
    Node *head = NULL;
    int total_jogadores_arquivo = 0;
    carregar_jogadores(&head, &total_jogadores_arquivo);

    // Verificar se já existe um jogador com o mesmo nome no arquivo
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current->jogador.nome, nome) == 0) {
            system("clear");
            printf("Erro: Já existe um jogador com o nome '%s' no arquivo.\n", nome);
            // Liberar a memória da lista encadeada
            while (head != NULL) {
                Node *temp = head;
                head = head->prox;
                free(temp);
            }
            return 0;
        }
        current = current->prox;
    }

    // Verificar se já existe um jogador com o mesmo nome na lista atual
    for (int i = 0; i < total_jogadores; i++) {
        if (strcmp(jogadores[i].nome, nome) == 0) {
            system("clear");
            printf("Erro: Já existe um jogador com o nome '%s'.\n", nome);
            // Liberar a memória da lista encadeada
            while (head != NULL) {
                Node *temp = head;
                head = head->prox;
                free(temp);
            }
            return 0;
        }
    }

    // Liberar a memória da lista encadeada
    while (head != NULL) {
        Node *temp = head;
        head = head->prox;
        free(temp);
    }

    strcpy(novo_jogador->nome, nome);
    novo_jogador->gols = 0;
    return 1;
}

void atualizar_gols(Player *jogador, int gols) {
    jogador->gols += gols;
}

void exibir_pontuacao(Player *jogador) {
    printf("%s - %d\n", jogador->nome, jogador->gols);
}

void salvar_score(Player jogadores[]) {
    FILE *file = fopen(ARQUIVO, "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita");
        return;
    }
    for (int i = 0; i < 2; i++) {
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
            fprintf(stderr, "Erro ao ler a linha %d do arquivo.\n", i + 1);
            break;
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
    system("clear");
    printf("Ranking dos jogadores:\n");

    for (int i = 0; i < total_jogadores; i++) {
        printf("%d. %s - Gols: %d\n", i + 1, jogadores[i].nome, jogadores[i].gols);
    }
}

int ganhador(Player jogador_a, Player jogador_b) {
    if (jogador_a.gols > jogador_b.gols) {
        return 0; // jogador_a é o ganhador
    } else if (jogador_a.gols < jogador_b.gols) {
        return 1; // jogador_b é o ganhador
    } else {
        return -1; // empate
    }
}