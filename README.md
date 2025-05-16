Projeto da disciplina: Programação Imperava e Funcional

Instituição de ensino: Cesar School

Profº Diego de Freitas


# Memorize
Jogo da memória em C, onde temos que memorizar os números apresentados pelo programa, e informa-los corretamente quando perguntado, a cada acerto mais um número é adicionado a próxima rodada, o jogo continua sendo executado até o jogador errar, e ao final da rodada o programa apresenta um ranking.

**Estrutura do projeto:**

incluir

fonte

LICENÇA

Makefile

LEIA-ME.md



**Instruções Compilar e Executar**


1. Navegue até o diretório do projeto:
   ```sh
   https://github.com/tfsLua/Memorize
   ```
2. Compile o arquivo
   ```sh
   cd gcc jogo_memoria.c -o jogo_memoria
   ```
3. Execute o arquivo
   ```sh 
   jogo_memoria.c
   ```

## Autores
- Mariana Ferreira [[@mwndrly](https://github.com/mwndrly)]
- Priscila Maciel [[@PriscilaMdeLima](https://github.com/PriscilaMdeLima)]
- Thaissa Fernandes [[@tfsLua](https://github.com/tfsLua)]
- João Lira [[@joaosanli](https://github.com/joaosanli)]

## Fluxo da Mecânica do Jogo
1. Início do Jogo
   
•	O programa inicia com a configuração da tela (screenInit) e do teclado (keyboardInit).

•	O ranking de jogadores é carregado do arquivo ranking.txt.

•	O jogador insere seu nome.

3. Preparação dos Vetores
   
•	São alocados dois vetores de inteiros com até 100 posições:

o	numeros: guarda a sequência gerada aleatoriamente.

o	resposta: armazena os números digitados pelo jogador.

5. Loop Principal do Jogo
   
O loop principal (while (1)) contém a mecânica central:

a. Geração da Sequência

for (int i = 0; i < qtdNumeros; i++) {
    numeros[i] = rand() % 100;
}

•	Gera uma sequência aleatória de qtdNumeros valores entre 0 e 99.

•	Para o numero, int, estar entre 0 e 99, o operador % pega o resto da divisão por 100.

b. Exibição para o Jogador

mostrarNumeros(numeros, qtdNumeros);

•	Mostra os números por 3 segundos.

•	Limpa a tela e dá 1 segundo antes de pedir as respostas.

c. Entrada do Jogador

for (int i = 0; i < qtdNumeros; i++) {
    printf("Número %d: ", i + 1);
    scanf("%d", &resposta[i]);
}

•	O jogador deve digitar os números na mesma ordem.

d. Verificação da Resposta

if (verificarResposta(numeros, resposta, qtdNumeros)) {
    // Acertou
    pontuacao++;
    qtdNumeros++;
} else {
    // Errou
    break;
}

•	Se estiver tudo certo:

o	A pontuação é incrementada.

o	O número de elementos na próxima rodada aumenta, para aumentar o grau de dificuldade a cada rodada.

•	Se errar, o jogo termina.


**Ranking de Jogadores**

Após o término:

1.	A pontuação do jogador é salva usando:
   
o	atualizarRanking(...)

o	salvarRanking(...)

3.	O ranking é exibido com cores diferentes para os 3 primeiros colocados usando screenSetColor.
   

**Funções Auxiliares**

mostrarNumeros(...)

•	Exibe os números gerados.

•	Usa usleep para atrasar a execução, simulando o tempo de memorização.

verificarResposta(...)

•	Compara a sequência digitada com a original.

carregarRanking(...), salvarRanking(...), atualizarRanking(...)

•	Lida com o carregamento, salvamento e atualização do ranking no arquivo ranking.txt.


**Resumo da Mecânica**

Etapa	Ação

Início	Jogador digita o nome

Rodada	Mostra n números aleatórios

Resposta	Jogador digita os n números na ordem correta

Verificação	Se correto, n++ e pontuação aumenta

Fim	Se errar, exibe pontuação final e ranking atualizado


