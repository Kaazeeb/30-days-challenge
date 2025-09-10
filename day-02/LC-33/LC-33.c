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