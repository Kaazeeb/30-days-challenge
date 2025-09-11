#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int val;
  struct Node *prev;
  struct Node *next;
  struct Node *child;
} Node;

Node *flatten(Node *head) {
  // 'stored' funciona como uma pilha para guardar os ponteiros 'next' originais
  // quando um 'child' e encontrado e precisa ser processado
  Node *stored[1001];
  int i = 0;  // 'i' e o indice do topo da pilha 'stored'
  Node *ptr = head;

  // Loop principal para atravessar a lista ate o fim
  while (ptr) {
    // Se o no atual tem um filho, a logica de achatamento e acionada
    if (ptr->child) {
      // Se o no atual tambem tem um proximo, esse proximo e guardado na pilha
      if (ptr->next) {
        stored[i] = ptr->next;
        i++;
      }
      // O proximo do no atual passa a ser o seu filho
      ptr->next = ptr->child;
      // O ponteiro 'prev' do novo proximo (o antigo filho) e ligado ao no atual
      ptr->next->prev = ptr;
      // A referencia ao filho e removida, pois ele ja foi incorporado a lista
      ptr->child = 0;
    }

    // Se o ponteiro chegou ao fim de um ramo E a pilha nao esta vazia
    if (!ptr->next && i > 0) {
      // O proximo do no atual sera o no que esta no topo da pilha
      ptr->next = stored[i - 1];
      // O topo da pilha e decrementado (desempilhar)
      i--;
      // O ponteiro 'prev' do no que foi religado e ajustado
      ptr->next->prev = ptr;
    }
    // Avanca o ponteiro para o proximo no da lista linearizada
    ptr = ptr->next;
  }
  return head;
}