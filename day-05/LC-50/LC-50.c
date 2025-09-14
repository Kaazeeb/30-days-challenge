double myPow(double x, long long n) {
  // Caso base da recursao. Qualquer numero elevado a 0 e 1.
  if (n == 0) return 1;

  // Trata o caso de expoente negativo.
  if (n < 0) {
    // Usa a propriedade x^-n = (1/x)^n.
    return myPow(1 / x, -n);

    // Se n for par
  } else if (n % 2 == 0) {
    // Usa a propriedade x^n = (x*x)^(n/2), dividindo o problema pela metade.
    return myPow(x * x, n / 2);

    // Se n for impar.
  } else {
    // Usa a propriedade x^n = x * x^(n-1). O resto vira um caso de n par.
    // A divisao inteira n/2 para n impar e igual a (n-1)/2.
    return x * myPow(x * x, n / 2);
  }
}