#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "../include/cli-lib/screen.h"
#include "../include/cli-lib/keyboard.h"
#include "../include/cli-lib/timer.h"

#define MAX_NUMS 100
#define MAX_NOME 20
#define RANKING_FILE "ranking.txt"
#define MAX_RANK 10

typedef struct {
    char nome[MAX_NOME];
    int pontuacao;
} Jogador;


void mostrarNumeros(int *numeros, int qtd) {
    screenClear();
    printf("Memorize os números:\n\n");
    for (int i = 0; i < qtd; i++)
        printf("%d ", numeros[i]);
    printf("\n");

    usleep(3000 * 1000);
    screenClear();
    usleep(1000 * 1000);
    printf("Digite os números na ordem correta:\n\n");
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
    strncpy(novo.nome, nome, MAX_NOME - 1);
    novo.nome[MAX_NOME - 1] = '\0';
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
    screenClear();
    printf("===== RANKING =====\n");

    for (int i = 0; i < total; i++) {
        if (i == 0) {
            screenSetColor(CYAN, BLACK);
        } else if (i == 1) {
            screenSetColor(GREEN, BLACK);
        } else if (i == 2) {
            screenSetColor(YELLOW, BLACK);
        } else {
            screenSetColor(WHITE, BLACK);
        }

        printf("%d. %s - %d\n", i + 1, ranking[i].nome, ranking[i].pontuacao);
    }

    screenSetNormal();
    printf("\nPressione Enter para continuar...");
    getchar();
    getchar();
}

int main() {
    srand(time(NULL));
    screenInit(1);
    keyboardInit();

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

    if (numeros == NULL || resposta == NULL) {
        printf("Erro de alocação de memória!\n");
        screenDestroy();
        keyboardDestroy();
        return 1;
    }


    while (1) {
        for (int i = 0; i < qtdNumeros; i++) {
            numeros[i] = rand() % 100;
        }

        mostrarNumeros(numeros, qtdNumeros);

        for (int i = 0; i < qtdNumeros; i++) {
            printf("Número %d: ", i + 1);
            scanf("%d", &resposta[i]);
        }

        if (verificarResposta(numeros, resposta, qtdNumeros)) {
            screenSetColor(GREEN, BLACK);
            printf("\nCorreto! Próxima rodada...\n");
            screenSetNormal();
            pontuacao++;
            qtdNumeros++;
        } else {
            screenSetColor(RED, BLACK);
            printf("\nErrado! Fim de jogo.\n");
            screenSetNormal();
            break;
        }

        printf("\nPressione Enter para continuar...");
        getchar();
        getchar();
    }

    screenSetColor(YELLOW, BLACK);
    printf("\nPontuação final: %d\n", pontuacao);
    screenSetNormal();

    atualizarRanking(ranking, &totalRanking, nome, pontuacao);
    salvarRanking(ranking, totalRanking);
    exibirRanking(ranking, totalRanking);

    free(numeros);
    free(resposta);
    screenDestroy();
    keyboardDestroy();

    return 0;
}
