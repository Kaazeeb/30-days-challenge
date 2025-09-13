int countPrimes(int n) {
  // Trata o caso base onde nao ha primos.
  if (n <= 2) return 0;

  // Tamanho do array para os numeros impares de 3 ate n.
  int num_elements = (n - 2) / 2;
  bool *arr = malloc(num_elements * sizeof(bool));
  // Inicializa todos como 'false' (primo). 'true' significa composto.
  memset(arr, false, num_elements * sizeof(bool));

  // O crivo de Eratostenes so precisa verificar ate a raiz de n.
  int limit = sqrt(n);

  // Itera sobre os impares (3, 5, 7...) que podem ser primos.
  for (int i = 3; i <= limit; i += 2) {
    // Pula se o numero 'i' ja foi marcado como multiplo de um primo menor.
    // A expressao (i - 3) / 2 converte o numero 'i' para seu indice no array.
    if (arr[(i - 3) / 2] == true) continue;

    // Marca todos os multiplos impares de 'i' como compostos, comecando de i*i.
    for (int j = i * i; j < n; j += i + i) {
      arr[(j - 3) / 2] = true;
    }
  }

  // Comeca em 1 para contar o primo par (2), que foi excluido do crivo.
  int count = 1;
  // Conta os numeros que nao foram marcados como compostos.
  for (int i = 0; i < num_elements; ++i) {
    if (arr[i] == false) ++count;
  }

  return count;
}