#include <stdio.h>
#include <stdlib.h>

int removeDuplicates(int *nums, int numsSize) {
  // 'slow_ptr' marca a posicao do proximo elemento unico e tambem conta quantos
  // unicos existem. Começa em 1, pois nums[0] e sempre mantido
  int slow_ptr = 1;

  // Percorre o array a partir do segundo elemento para encontrar novos valores.
  for (int i = 1; i < numsSize; i++) {
    // Compara o elemento atual 'nums[i]' com o ultimo unico ja registrado
    // 'nums[slow_ptr - 1]'
    if (nums[i] != nums[slow_ptr - 1]) {
      // Se for um novo valor unico, ele e movido para a posicao 'slow_ptr'
      nums[slow_ptr] = nums[i];

      slow_ptr++;  // Proxima posicao livre e incrementada
    }
    // Se os valores forem iguais, o loop simplesmente avança
  }

  // O valor final de 'slow_ptr' e a quantidade de elementos unicos
  return slow_ptr;
}

/*
Para compilar e executar:
gcc nome_do_arquivo.c -o meu_programa.out
./meu_programa.out testcase

Formato do arquivo de teste:
Uma unica linha contendo numeros inteiros separados por espacos.
Exemplo: 0 0 1 1 1 2 2 3 3 4
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

  int *nums = malloc(10 * sizeof(int));
  int size = 0;
  int capacity = 10;

  while (fscanf(file, "%d", &nums[size]) == 1) {
    size++;
    if (size >= capacity) {
      capacity *= 2;
      nums = realloc(nums, capacity * sizeof(int));
    }
  }
  fclose(file);

  int k = removeDuplicates(nums, size);

  for (int i = 0; i < k; i++) {
    printf("%d ", nums[i]);
  }
  printf("\n");

  free(nums);
  return 0;
}