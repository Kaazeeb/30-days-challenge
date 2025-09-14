int findTheWinner(int n, int k) {
  if (n == 1) return 1;  // Caso base

  // Mapeia o vencedor do subproblema (n-1) de volta para o circulo atual (n).
  // A formula desloca a posicao do vencedor anterior em 'k' lugares,
  // usa o modulo 'n' para simular o comportamento circular,
  // e ajusta o indice de 1-based para 0-based (-1) e de volta (+1)
  return (findTheWinner(n - 1, k) + k - 1) % n + 1;
}