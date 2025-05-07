#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "CLI/cligfx.h"
#include "CLI/cliinput.h"

#define MAX_NUMS 100
#define MAX_NOME 20
#define RANKING_FILE "ranking.txt"
#define MAX_RANK 10

typedef struct {
    char nome[MAX_NOME];
    int pontuacao;
} Jogador;

void mostrarNumeros(int *numeros, int qtd) {
    clearScreen();
    printf("Memorize os numeros:\n\n");
    for (int i = 0; i < qtd; i++)
        printf("%d ", numeros[i]);
    printf("\n");

    sleep(3);          // Exibe os números por 3 segundos
    clearScreen();     // Limpa a tela
    sleep(1);          // Pausa com a tela limpa
    printf("Digite os numeros na ordem correta:\n\n");
}

int verificarResposta(int *original, int *resposta, int qtd) {
    for (int i = 0; i < qtd; i++) {
        if (original[i] != resposta[i])
            return 0;
    }
    return 1;
}

void salvarRanking(Jogador *ranking, int total) {
    FILE *f = fopen(RANKING_FILE, "w");
    if (f == NULL) return;

    for (int i = 0; i < total; i++) {
        fprintf(f, "%s %d\n", ranking[i].nome, ranking[i].pontuacao);
    }

    fclose(f);
}

void carregarRanking(Jogador *ranking, int *total) {
    FILE *f = fopen(RANKING_FILE, "r");
    if (f == NULL) {
        *total = 0;
        return;
    }

    int i = 0;
    while (fscanf(f, "%s %d", ranking[i].nome, &ranking[i].pontuacao) != EOF && i < MAX_RANK) {
        i++;
    }
    *total = i;
    fclose(f);
}

void atualizarRanking(Jogador *ranking, int *total, char *nome, int pontuacao) {
    Jogador novo;
    strncpy(novo.nome, nome, MAX_NOME);
    novo.pontuacao = pontuacao;

    int i;
    for (i = *total; i > 0 && ranking[i - 1].pontuacao < pontuacao; i--) {
        if (i < MAX_RANK) ranking[i] = ranking[i - 1];
    }

    if (i < MAX_RANK) {
        ranking[i] = novo;
        if (*total < MAX_RANK) (*total)++;
    }
}

void exibirRanking(Jogador *ranking, int total) {
    clearScreen();
    printf("===== RANKING =====\n");

    for (int i = 0; i < total; i++) {
        if (i == 0)
            setFgColor(FG_CYAN);
        else if (i == 1)
            setFgColor(FG_GREEN);
        else if (i == 2)
            setFgColor(FG_YELLOW);
        else
            setFgColor(FG_WHITE);

        printf("%d. %s - %d\n", i + 1, ranking[i].nome, ranking[i].pontuacao);
    }

    resetColors();
    waitForEnter();
}

int main() {
    srand(time(NULL));

    Jogador ranking[MAX_RANK];
    int totalRanking;
    carregarRanking(ranking, &totalRanking);

    char nome[MAX_NOME];
    printf("Digite seu nome: ");
    scanf("%s", nome);

    int pontuacao = 0;
    int qtdNumeros = 4;

    int *numeros = malloc(sizeof(int) * MAX_NUMS);
    int *resposta = malloc(sizeof(int) * MAX_NUMS);

    while (1) {
        for (int i = 0; i < qtdNumeros; i++) {
            numeros[i] = rand() % 100;
        }

        mostrarNumeros(numeros, qtdNumeros);

        for (int i = 0; i < qtdNumeros; i++) {
            printf("Numero %d: ", i + 1);
            scanf("%d", &resposta[i]);
        }

        if (verificarResposta(numeros, resposta, qtdNumeros)) {
            setFgColor(FG_GREEN);
            printf("\nCorreto! Proxima rodada...\n");
            resetColors();
            pontuacao++;
            qtdNumeros++;
        } else {
            setFgColor(FG_RED);
            printf("\nErrado! Fim de jogo.\n");
            resetColors();
            break;
        }

        waitForEnter();
    }

    setFgColor(FG_YELLOW);
    printf("\nPontuacao final: %d\n", pontuacao);
    resetColors();

    atualizarRanking(ranking, &totalRanking, nome, pontuacao);
    salvarRanking(ranking, totalRanking);
    exibirRanking(ranking, totalRanking);

    free(numeros);
    free(resposta);
    return 0;
}
