void selection_sort(int* nums, int nums_size) {
  // 'i' marca o inicio da parte nao ordenada do array. O loop vai ate o 
  // penultimo elemento, pois o ultimo estara ordenado por consequencia.
  for (int i = 0; i < nums_size - 1; ++i) {
    // Variaveis para guardar o menor valor e seu indice na parte nao ordenada.
    int min = nums[i];
    int index = i;

    // Procura pelo menor elemento no restante do array (a parte nao ordenada).
    for (int j = i + 1; j < nums_size; ++j) {
      // Se encontrar um elemento menor que o 'min' atual.
      if (nums[j] < min) {
        // Atualiza o indice e o valor do menor elemento.
        index = j;
        min = nums[j];
      }
    }
    
    // Coloca o elemento que estava em 'i' na posicao do menor encontrado.
    nums[index] = nums[i];
    // Coloca o menor elemento encontrado na posicao 'i', ordenando-a.
    nums[i] = min;
  }
}