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