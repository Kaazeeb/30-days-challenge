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

      slow_ptr++; // Proxima posicao livre e incrementada
    }
    // Se os valores forem iguais, o loop simplesmente avança
  }

  // O valor final de 'slow_ptr' e a quantidade de elementos unicos
  return slow_ptr;
}