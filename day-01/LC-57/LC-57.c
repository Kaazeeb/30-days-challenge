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
  for (i = 0; i < *returnSize; ++i)
    (*returnColumnSizes)[i] = 2;

  // Otimizacao: realoca 'ans' para o tamanho exato, liberando memoria extra
  ans = realloc(ans, *returnSize * sizeof(int *));
  return ans;
}