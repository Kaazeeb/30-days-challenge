#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * A funcao insere um 'newInterval' em uma lista de 'intervals' ja ordenada
 * e sem sobreposicao. A logica e dividida em tres partes:
 * 1. Adicionar todos os intervalos que terminam antes do novo intervalo
 * comecar.
 * 2. Juntar o novo intervalo com todos os intervalos sobrepostos.
 * 3. Adicionar o resto dos intervalos.
 */
int **insert(int **intervals, int intervalsSize, int *intervalsColSize,
             int *newInterval, int newIntervalSize, int *returnSize,
             int **returnColumnSizes) {
  // Aloca espaco para o pior caso: o novo intervalo e adicionado sem se juntar
  // a nenhum outro
  int **ans = malloc((intervalsSize + 1) * sizeof(int *));
  // 'ptr' e um ponteiro auxiliar para preencher o array 'ans'
  int **ptr = ans;
  int i = 0;

  // --- Fase 1: Adiciona intervalos que estao totalmente antes do novo
  // intervalo --- Loop enquanto o fim do intervalo atual for menor que o inicio
  // do novo intervalo
  for (; i < intervalsSize && intervals[i][1] < newInterval[0]; ++i, ++ptr) {
    *ptr = malloc(2 * sizeof(int));
    // Copia o intervalo de 'intervals' para 'ans'
    memcpy(*ptr, intervals[i], 2 * sizeof(int));
  }

  // --- Fase 2: Junta o novo intervalo com os intervalos sobrepostos ---
  // Primeiro, ajusta o inicio do novo intervalo. Se o intervalo atual comeca
  // antes, o novo intervalo deve comecar onde o intervalo atual comeca
  if (i < intervalsSize) {
    newInterval[0] =
        (newInterval[0] < intervals[i][0]) ? newInterval[0] : intervals[i][0];
  }

  // Agora, avanca por todos os intervalos que se sobrepoem e ajusta o fim do
  // novo intervalo
  for (; i < intervalsSize && intervals[i][0] <= newInterval[1]; ++i) {
    // O fim do novo intervalo sera o maior entre o seu fim atual e o fim do
    // intervalo sobreposto
    newInterval[1] =
        (newInterval[1] > intervals[i][1]) ? newInterval[1] : intervals[i][1];
  }

  // Adiciona o novo intervalo (ja mesclado) ao resultado
  *ptr = malloc(2 * sizeof(int));
  memcpy(*ptr, newInterval, 2 * sizeof(int));
  ++ptr;

  // --- Fase 3: Adiciona os intervalos restantes ---
  // Adiciona todos os intervalos que comecam depois do novo intervalo (ja
  // mesclado)
  for (; i < intervalsSize; ++i, ++ptr) {
    *ptr = malloc(2 * sizeof(int));
    memcpy(*ptr, intervals[i], 2 * sizeof(int));
  }

  // Calcula o tamanho final do array de resultado usando aritmetica de
  // ponteiros
  *returnSize = ptr - ans;

  // Aloca e preenche o array com os tamanhos das colunas (sempre 2)
  *returnColumnSizes = malloc(*returnSize * sizeof(int));
  for (i = 0; i < *returnSize; ++i) (*returnColumnSizes)[i] = 2;

  // Otimizacao: realoca 'ans' para o tamanho exato, liberando memoria extra
  ans = realloc(ans, *returnSize * sizeof(int *));
  return ans;
}

/*
Para compilar e executar:
gcc nome_do_arquivo.c -o meu_programa.out
./meu_programa.out testcase

Formato do arquivo de teste:
Uma unica linha contendo numeros inteiros separados por espacos.
Os pares de numeros representam os intervalos. Os dois ultimos
numeros na linha sao o 'newInterval'.
Exemplo: 1 3 6 9 2 5
Corresponde a: intervals = [[1,3],[6,9]], newInterval = [2,5]
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

  if (count < 2 || count % 2 != 0) {
      printf("Formato de entrada invalido.\n");
      free(all_nums);
      return 1;
  }
  
  int newInterval[] = {all_nums[count - 2], all_nums[count - 1]};
  int intervalsSize = (count / 2) - 1;
  int **intervals = malloc(intervalsSize * sizeof(int *));

  for (int i = 0; i < intervalsSize; i++) {
    intervals[i] = malloc(2 * sizeof(int));
    intervals[i][0] = all_nums[i * 2];
    intervals[i][1] = all_nums[i * 2 + 1];
  }

  int returnSize;
  int *returnColumnSizes;
  
  int **result = insert(intervals, intervalsSize, NULL, newInterval, 2, &returnSize, &returnColumnSizes);

for (int i = 0; i < returnSize; i++) {
    printf("%d %d ", result[i][0], result[i][1]);
  }
  printf("\n");

  free(all_nums);
  for (int i = 0; i < intervalsSize; i++) {
    free(intervals[i]);
  }
  free(intervals);
  for (int i = 0; i < returnSize; i++) {
    free(result[i]);
  }
  free(result);
  free(returnColumnSizes);

  return 0;
}