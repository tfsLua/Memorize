#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "cli-lib/cli.h"

#define MAX_NUMS 100
#define MAX_NOME 20
#define RANKING_FILE "ranking.txt"
#define MAX_RANK 10

typedef struct {
    char nome[MAX_NOME];
    int pontuacao;
} Jogador;

void mostrarNumeros(int *numeros, int qtd) {
    cli_clear();
    cli_printf("Memorize os números:\n\n");
    for (int i = 0; i < qtd; i++)
        cli_printf("%d ", numeros[i]);
    cli_printf("\n");

    cli_sleep(3000);    // Pausa de 3 segundos
    cli_clear();        // Limpa a tela
    cli_sleep(1000);    // Pausa de 1 segundo
    cli_printf("Digite os números na ordem correta:\n\n");
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
    cli_clear();
    cli_printf("===== RANKING =====\n");

    for (int i = 0; i < total; i++) {
        if (i == 0)
            cli_set_fg_color(CLI_COLOR_CYAN);
        else if (i == 1)
            cli_set_fg_color(CLI_COLOR_GREEN);
        else if (i == 2)
            cli_set_fg_color(CLI_COLOR_YELLOW);
        else
            cli_set_fg_color(CLI_COLOR_WHITE);

        cli_printf("%d. %s - %d\n", i + 1, ranking[i].nome, ranking[i].pontuacao);
    }

    cli_reset_colors();
    cli_printf("\nPressione Enter para continuar...");
    getchar();
}

int main() {
    srand(time(NULL));
    cli_init();

    Jogador ranking[MAX_RANK];
    int totalRanking;
    carregarRanking(ranking, &totalRanking);

    char nome[MAX_NOME];
    cli_printf("Digite seu nome: ");
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
            cli_printf("Número %d: ", i + 1);
            scanf("%d", &resposta[i]);
        }

        if (verificarResposta(numeros, resposta, qtdNumeros)) {
            cli_set_fg_color(CLI_COLOR_GREEN);
            cli_printf("\nCorreto! Próxima rodada...\n");
            cli_reset_colors();
            pontuacao++;
            qtdNumeros++;
        } else {
            cli_set_fg_color(CLI_COLOR_RED);
            cli_printf("\nErrado! Fim de jogo.\n");
            cli_reset_colors();
            break;
        }

        cli_printf("\nPressione Enter para continuar...");
        getchar();
        getchar();
    }

    cli_set_fg_color(CLI_COLOR_YELLOW);
    cli_printf("\nPontuação final: %d\n", pontuacao);
    cli_reset_colors();

    atualizarRanking(ranking, &totalRanking, nome, pontuacao);
    salvarRanking(ranking, totalRanking);
    exibirRanking(ranking, totalRanking);

    free(numeros);
    free(resposta);
    cli_close();
    return 0;
}
