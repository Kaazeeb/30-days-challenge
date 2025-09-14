char *decode_recurs(char *s, char **ans) {
  // O laco principal processa a string ate o fim de um segmento ']' ou da
  // string toda '\0'.
  while (*s != ']' && *s != '\0') {
    // Verifica se o caractere atual e um digito para uma repeticao.
    if (*s >= '0' && *s <= '9') {
      // Converte a sequencia de digitos para um numero inteiro.
      int val = 0;
      while (*s >= '0' && *s <= '9') {
        val = 10 * val + (*s - '0');
        s++;
      }
      s++;  // Avanca o ponteiro para depois do '['.

      // Marca o inicio do segmento no buffer de resposta.
      char *seg_start = *ans;
      // Chamada recursiva para decodificar o segmento interno uma vez.
      s = decode_recurs(s, ans);
      // Calcula o tamanho do segmento que foi decodificado.
      int seg_len = *ans - seg_start;

      // Repete o segmento decodificado (val - 1) vezes.
      for (int i = 0; i < val - 1; i++) {
        // Copia o bloco de memoria do segmento para a posicao atual.
        memcpy(*ans, seg_start, seg_len);
        // Avanca o ponteiro de escrita no buffer de resposta.
        *ans += seg_len;
      }
      // Se nao for um digito, deve ser uma letra.
    } else {
      // Copia o caractere da string de entrada para a de saida.
      **ans = *s;
      // Avanca o ponteiro de escrita para a proxima posicao.
      ++(*ans);
      // Avanca o ponteiro de leitura para o proximo caractere.
      ++s;
    }
  }
  // Retorna o ponteiro de leitura avancado para depois do ']'.
  return ++s;
}

char *decodeString(char *s) {
  // Aloca um buffer de memoria grande o suficiente para a resposta.
  char *ans = malloc(112345 * sizeof(char));
  // Cria um ponteiro que servira como 'cabeca de escrita'.
  char *ptr = ans;

  // Inicia o processo de decodificacao recursiva.
  decode_recurs(s, &ptr);

  // Adiciona o terminador nulo no final da string de resposta.
  *ptr = '\0';
  // Retorna o inicio do buffer com a string decodificada.
  return ans;
}