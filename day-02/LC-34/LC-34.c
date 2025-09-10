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