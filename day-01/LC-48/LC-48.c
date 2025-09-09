// Funcao auxiliar para trocar o valor de duas variaveis inteiras
void swap(int *a, int *b) {
  int x = *a; // Guarda o valor de 'a' temporariamente
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