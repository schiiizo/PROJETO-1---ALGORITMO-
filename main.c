#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_PALAVRAS 10
#define TAM_PALAVRA 5
#define MAX_TENTATIVAS 6

char* palavras[NUM_PALAVRAS] = {
    "apple", "beach", "cloud", "drink", "empty", "fancy", "great", "happy", "jolly", "koala"
};

char* escolherPalavra();
char* checarPalavra(char* palavra, char* tentativas);
void adicionarScore(char* nomeJogador, char* palavra, int tentativas, double tempoTotal);
void limparBufferEntrada();
void toLowerCase(char* str);

int main() {
    srand(time(NULL));

    char* palavraSorteada = escolherPalavra();
    int tentativasRestantes = MAX_TENTATIVAS;
    char tentativas[TAM_PALAVRA + 1] = "";
    char tentativa;
    char nomeJogador[50];
    clock_t inicio = clock();

    printf("Bem-vindo ao jogo da forca!\n");
    printf("A palavra sorteada tem %d letras. Boa sorte!\n", TAM_PALAVRA);

    while (tentativasRestantes > 0) {
        printf("\nPalavra atual: %s\n", checarPalavra(palavraSorteada, tentativas));
        printf("Tentativas restantes: %d\n", tentativasRestantes);
        printf("Digite uma letra ou a palavra completa: ");
        scanf(" %c", &tentativa);
        limparBufferEntrada();
        tentativa = tolower(tentativa);

        if (tentativa == palavraSorteada[0]) {
            printf("Parabéns! Você acertou a palavra!\n");
            printf("Digite seu nome: ");
            scanf("%s", nomeJogador);
            limparBufferEntrada();
            clock_t fim = clock();
            double tempoTotal = (double)(fim - inicio) / CLOCKS_PER_SEC;
            adicionarScore(nomeJogador, palavraSorteada, MAX_TENTATIVAS - tentativasRestantes + 1, tempoTotal);
            return 0;
        }

        if (!isalpha(tentativa)) {
            printf("Entrada inválida. Por favor, digite apenas uma letra ou a palavra completa.\n");
            continue;
        }

        if (strchr(tentativas, tentativa) != NULL) {
            printf("Você já tentou esta letra. Tente outra.\n");
            continue;
        }

        strncat(tentativas, &tentativa, 1);

        printf("Letra incorreta.\n");
        tentativasRestantes--;
    }

    printf("\nSuas tentativas acabaram! A palavra correta era: %s\n", palavraSorteada);

    return 0;
}

char* escolherPalavra() {
    int indice = rand() % NUM_PALAVRAS;
    return palavras[indice];
}

char* checarPalavra(char* palavra, char* tentativas) {
    static char resultado[TAM_PALAVRA + 1];
    strcpy(resultado, palavra);
    for (int i = 0; i < TAM_PALAVRA; i++) {
        if (strchr(tentativas, palavra[i]) == NULL) {
            resultado[i] = '_';
        }
    }
    return resultado;
}

void adicionarScore(char* nomeJogador, char* palavra, int tentativas, double tempoTotal) {
    printf("Nome do jogador: %s\n", nomeJogador);
    printf("Palavra: %s\n", palavra);
    printf("Número de tentativas: %d\n", tentativas);
    printf("Tempo total até acertar (em segundos): %.2lf\n", tempoTotal);
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}
