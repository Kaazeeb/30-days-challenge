#include <stdio.h>
#include <stdlib.h>

struct ListNode {
  int val;
  struct ListNode *next;
};

struct ListNode *middleNode(struct ListNode *head) {
  // A logica usa dois ponteiros: 'mid' (lento) e 'head' (rapido)
  struct ListNode *mid = head;

  // O loop continua enquanto o ponteiro rapido e o proximo dele nao forem nulos
  while (head != 0 && head->next != 0) {
    // O ponteiro lento avanca uma posicao por vez
    mid = mid->next;
    // O ponteiro rapido avanca duas posicoes por vez
    head = head->next->next;
  }
  // Quando o ponteiro rapido chega ao fim, o lento esta no meio
  return mid;
}