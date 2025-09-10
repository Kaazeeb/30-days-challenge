#include <stdio.h>
#include <stdlib.h>

int *searchRange(int *nums, int numsSize, int target, int *returnSize) {
  // Aloca e prepara o array de retorno com os valores padrao
  int *ans = malloc(2 * sizeof(int));
  *returnSize = 2;
  ans[0] = ans[1] = -1;

  int *left = nums;
  int *right = nums + numsSize - 1;
  int *guess;

  // --- Primeira busca: encontrar o limite esquerdo ---
  while (left <= right) {
    guess = left + (right - left) / 2;

    // Logica para empurrar a busca para a esquerda
    if (*guess < target) {
      left = guess + 1;
    } else {
      right = guess - 1;
    }

    // Guarda o indice se for um alvo valido
    if (*guess == target) {
      ans[0] = guess - nums;
    }
  }
  // Se o limite esquerdo nao foi achado, o alvo nao existe
  if (ans[0] == -1) return ans;

  // --- Segunda busca: encontrar o limite direito ---
  // Otimizacao: comeca a busca a partir do limite esquerdo ja encontrado
  left = nums + ans[0];
  right = nums + numsSize - 1;
  while (left <= right) {
    guess = left + (right - left) / 2;

    // Logica para empurrar a busca para a direita
    if (*guess > target) {
      right = guess - 1;
    } else {
      left = guess + 1;
    }

    // Guarda o indice se for um alvo valido
    if (*guess == target) {
      ans[1] = guess - nums;
    }
  }
  return ans;
}

/*
Para compilar e executar:
gcc nome_do_arquivo.c -o meu_programa.out
./meu_programa.out testcase

Formato do arquivo de teste:
Uma unica linha contendo numeros inteiros separados por espacos.
O ultimo numero da linha e o 'target' a ser buscado.
Exemplo: 5 7 7 8 8 10 8
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
  int returnSize;

  int *result = searchRange(all_nums, numsSize, target, &returnSize);

  printf("%d %d\n", result[0], result[1]);

  free(result);
  free(all_nums);
  return 0;
}