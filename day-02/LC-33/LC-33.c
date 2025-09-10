#include <stdio.h>
#include <stdlib.h>

int search(int *nums, int numsSize, int target) {
  int *left = nums;
  int *right = nums + numsSize - 1;
  int *guess = 0;

  // A logica e uma busca binaria adaptada para um array que foi rotacionado
  while (left <= right) {
    guess = left + (right - left) / 2;

    if (*guess == target) {
      return (guess - nums);
    }

    // --- Diferenca principal: Achar a metade ordenada ---
    // Em cada iteracao, uma das metades (esquerda ou direita) estara sempre
    // ordenada. O truque e descobrir qual delas e e se o alvo esta nela.

    // Caso 1: A metade esquerda esta ordenada
    if (*left <= *guess) {
      // O alvo esta na faixa ordenada da esquerda?
      if (target >= *left && target < *guess) {
        right = guess - 1;  // Se sim, busca nessa metade
      } else {
        left = guess + 1;  // Se nao, busca na outra metade
      }

      // Caso 2: A metade direita e que esta ordenada
    } else {
      // O alvo esta na faixa ordenada da direita?
      if (target > *guess && target <= *right) {
        left = guess + 1;  // Se sim, busca nessa metade
      } else {
        right = guess - 1;  // Se nao, busca na outra metade
      }
    }
  }
  return -1;  // Alvo nao encontrado
}

/*
Para compilar e executar:
gcc nome_do_arquivo.c -o meu_programa.out
./meu_programa.out testcase

Formato do arquivo de teste:
Uma unica linha contendo numeros inteiros separados por espacos.
O ultimo numero da linha e o 'target' a ser buscado.
Exemplo: 4 5 6 7 0 1 2 0
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

  int *all_nums = malloc(10 * sizeof(int));
  int count = 0;
  int capacity = 10;
  while (fscanf(file, "%d", &all_nums[count]) == 1) {
    count++;
    if (count >= capacity) {
      capacity *= 2;
      all_nums = realloc(all_nums, capacity * sizeof(int));
    }
  }
  fclose(file);

  if (count < 1) {
    printf("Formato de entrada invalido.\n");
    free(all_nums);
    return 1;
  }

  int target = all_nums[count - 1];
  int numsSize = count - 1;

  int index = search(all_nums, numsSize, target);

  printf("%d\n", index);

  free(all_nums);
  return 0;
}