// is_ipv4 usa uma maquina de estados para validar a string.
// Cada 'state' representa uma expectativa diferente: inicio de um numero,
// meio de um numero, fim de um numero, etc.
bool is_ipv4(char* query) {
  // state: 0=inicio de octeto, 1=lendo octeto, 2=fim de octeto (pre-ponto),
  // 3=lendo octeto final, 4=fim de octeto final (pre-fim da string)
  int state = 0;

  int num_el = 0;   // Contador de octetos (elementos)
  int num_dig = 0;  // Contador de digitos no octeto atual
  int val;          // Valor numerico do octeto atual

  while (true) {
    // STATE 0: Esperando o primeiro digito de um octeto.
    if (state == 0) {
      // Nao e um digito, invalido.
      if (*query < '0' || *query > '9') return false;

      // Regra: "0" e valido, mas "01" nao e (zero a esquerda).
      // Se o primeiro digito e '0', o octeto so pode ser "0".
      if (*query == '0') {
        // Se for o 4o octeto, vai para o estado final de "0".
        if (num_el == 3) {
          state = 4;
        } else {  // Senao, vai para o estado que espera um ponto.
          state = 2;
        }
      } else {  // Se o primeiro digito e 1-9.
        ++num_dig;
        val = *query - '0';
        // Se for o 4o octeto, vai para o estado de ler o octeto final.
        if (num_el == 3) {
          state = 3;
        } else {  // Senao, vai para o estado de ler um octeto normal.
          state = 1;
        }
      }
      // STATE 1: Lendo o 2o ou 3o digito de um octeto nao-final.
    } else if (state == 1) {
      // Se encontrou um ponto, o octeto acabou. Prepara para o proximo.
      if (*query == '.') {
        num_dig = 0;
        ++num_el;
        state = 0;
      } else if (*query < '0' || *query > '9') {
        return false;  // Caractere invalido.
      } else {
        ++num_dig;
        val = 10 * val + *query - '0';
        if (val > 255) return false;  // Valor do octeto > 255.
        // Se completou 3 digitos, o proximo deve ser um ponto.
        if (num_dig == 3) state = 2;
      }
      // STATE 2: Fim de um octeto nao-final. O proximo DEVE ser um ponto.
    } else if (state == 2) {
      if (*query == '.') {
        num_dig = 0;
        ++num_el;
        state = 0;
      } else
        return false;  // Se nao for ponto, e invalido.
      // STATE 3: Lendo o 2o ou 3o digito do octeto FINAL.
    } else if (state == 3) {
      // Se chegou ao fim da string, o IP e valido.
      if (*query == 0) {
        return true;
      } else if (*query < '0' || *query > '9') {
        return false;  // Caractere invalido.
      } else {
        ++num_dig;
        val = 10 * val + *query - '0';
        if (val > 255) return false;
        // Se completou 3 digitos, o proximo DEVE ser o fim da string.
        if (num_dig == 3) state = 4;
      }
      // STATE 4: Fim do octeto FINAL. O proximo DEVE ser o fim da string.
    } else {
      if (*query == 0) return true;
      return false;  // Se nao for o fim da string, e invalido.
    }
    ++query;
  }
}

// Funcao auxiliar que verifica se um caractere e um digito hexadecimal.
bool is_valid_char(char c) {
  if (c >= '0' && c <= '9') return true;
  if (c >= 'a' && c <= 'f') return true;
  if (c >= 'A' && c <= 'F') return true;
  return false;
}

// is_ipv6 usa uma maquina de estados similar a is_ipv4 para validar
// o formato canonico de 8 blocos de 4 digitos hexadecimais.
bool is_ipv6(char* query) {
  // state: 0=inicio de bloco, 1=lendo bloco, 2=fim de bloco (pre-dois-pontos),
  // 3=lendo bloco final, 4=fim de bloco final (pre-fim da string)
  int state = 0;

  int num_el = 0;   // Contador de blocos
  int num_dig = 0;  // Contador de digitos no bloco atual

  while (true) {
    // STATE 0: Esperando o primeiro digito de um bloco.
    if (state == 0) {
      if (!is_valid_char(*query)) return false;

      ++num_dig;
      // Se for o 8o bloco, vai para o estado de ler o bloco final.
      if (num_el == 7) {
        state = 3;
      } else {  // Senao, vai para o estado de ler um bloco normal.
        state = 1;
      }
      // STATE 1: Lendo um bloco nao-final (ate 4 digitos).
    } else if (state == 1) {
      // Se encontrou ':', o bloco acabou. Prepara para o proximo.
      if (*query == ':') {
        num_dig = 0;
        ++num_el;
        state = 0;
      } else if (!is_valid_char(*query)) {
        return false;
      } else {
        ++num_dig;
        // Se completou 4 digitos, o proximo deve ser ':'.
        if (num_dig > 4) return false;
        if (num_dig == 4) state = 2;
      }
      // STATE 2: Fim de um bloco nao-final (com 4 digitos). O proximo DEVE ser
      // ':'.
    } else if (state == 2) {
      if (*query == ':') {
        num_dig = 0;
        ++num_el;
        state = 0;
      } else
        return false;
      // STATE 3: Lendo o bloco FINAL.
    } else if (state == 3) {
      // Se chegou ao fim da string, e valido.
      if (*query == 0) {
        return true;
      } else if (!is_valid_char(*query)) {
        return false;
      } else {
        ++num_dig;
        // Se completou 4 digitos, o proximo DEVE ser o fim da string.
        if (num_dig > 4) return false;
        if (num_dig == 4) state = 4;
      }
      // STATE 4: Fim do bloco FINAL (com 4 digitos). O proximo DEVE ser o fim
      // da string.
    } else {
      if (*query == 0) return true;
      return false;
    }
    ++query;
  }
}

// Funcao principal que determina se a string e um IPv4, IPv6 valido ou nenhum
// dos dois.
char* validIPAddress(char* queryIP) {
  // A logica aqui e simples: tenta validar como IPv4. Se falhar, tenta como
  // IPv6. Se ambos falharem, nao e nenhum dos dois.
  if (is_ipv4(queryIP)) {
    return "IPv4";
  } else if (is_ipv6(queryIP)) {
    return "IPv6";
  }
  return "Neither";
}