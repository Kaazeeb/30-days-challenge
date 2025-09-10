#include <stdio.h>
#include <stdlib.h>

int search(int *nums, int numsSize, int target) {
  int *left = nums;                  // ponteiro para o inicio da busca
  int *right = nums + numsSize - 1;  // ponteiro para o fim da busca
  int *guess = NULL;                 // ponteiro para o elemento do meio

  // Loop enquanto a janela de busca for valida
  while (left <= right) {
    // Calcula o ponteiro do meio com aritmetica de ponteiros
    guess = left + (right - left) / 2;

    // Compara o valor apontado por 'guess' com o alvo
    // retorna o indice (diferenca de ponteiros)
    if (*guess == target) return (guess - nums);

    if (*guess < target) {
      // O alvo esta na metade direita
      left = guess + 1;  // ajusta o ponteiro de inicio
    } else {
      // O alvo esta na metade esquerda
      right = guess - 1;  // ajusta o ponteiro de fim
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
Exemplo: -1 0 3 5 9 12 9
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