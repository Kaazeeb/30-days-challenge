#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funcao auxiliar para trocar o valor de duas variaveis inteiras
void swap(int *a, int *b) {
  int x = *a;  // Guarda o valor de 'a' temporariamente
  *a = *b;
  *b = x;
}

void rotate(int **matrix, int matrixSize, int *matrixColSize) {
  // Dica: A rotacao de 90 graus pode ser feita em dois passos:
  // 1. Transpor a matriz (trocar linhas por colunas)
  // 2. Inverter cada linha horizontalmente

  // --- Passo 1: Transpor a matriz ---
  // O loop 'i' vai até o penultimo elemento
  for (int i = 0; i < matrixSize - 1; i++) {
    // O loop 'j' começa de 'i + 1' para percorrer apenas os elementos
    // acima da diagonal principal, trocando-os com os de baixo
    for (int j = i + 1; j < matrixSize; j++) {
      swap(&matrix[i][j], &matrix[j][i]);
    }
  }

  // --- Passo 2: Inverter cada linha ---
  // Percorre todas as linhas da matriz ja transposta
  for (int i = 0; i < matrixSize; i++) {
    // Percorre cada linha ate a metade, trocando os elementos das extremidades
    for (int j = 0; j < matrixSize / 2; j++) {
      // Troca o elemento do inicio com o seu correspondente no final da linha
      swap(&matrix[i][j], &matrix[i][matrixSize - j - 1]);
    }
  }
}

/*
Para compilar e executar:
gcc nome_do_arquivo.c -o meu_programa.out
./meu_programa.out testcase

Formato do arquivo de teste:
Uma matriz NxN. Cada linha da matriz e uma linha no arquivo.
Os numeros de uma linha sao separados por espacos.
Exemplo:
1 2 3
4 5 6
7 8 9
*/
int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Uso: %s <arquivo_de_teste>\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  if (!file) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }

  int n = 0;
  char buffer[4096];
  if (fgets(buffer, sizeof(buffer), file)) {
    char *token = strtok(buffer, " \t\n");
    while (token) {
      n++;
      token = strtok(NULL, " \t\n");
    }
  }

  rewind(file);

  int **matrix = malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++) {
    matrix[i] = malloc(n * sizeof(int));
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fscanf(file, "%d", &matrix[i][j]);
    }
  }
  fclose(file);

  rotate(matrix, n, NULL);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }

  for (int i = 0; i < n; i++) {
    free(matrix[i]);
  }
  free(matrix);

  return 0;
}