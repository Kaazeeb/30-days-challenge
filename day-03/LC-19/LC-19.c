#include <stdio.h>
#include <stdlib.h>

struct ListNode {
  int val;
  struct ListNode *next;
};

struct ListNode *removeNthFromEnd(struct ListNode *head, int n) {
  // A logica usa dois ponteiros, 'slow' e 'fast'
  struct ListNode *slow = head;
  struct ListNode *fast = head;

  // O ponteiro 'fast' avanca 'n' posicoes na frente de 'slow'
  for (int i = 0; i < n; ++i) {
    fast = fast->next;
  }

  // Se 'fast' se tornou nulo, significa que 'n' e igual ao tamanho
  // da lista. Logo, o no a ser removido e a cabeca (head).
  if (fast == 0) {
    return slow->next;
  }

  // Move os dois ponteiros juntos ate 'fast' chegar ao ultimo no da lista
  while (fast != 0 && fast->next != 0) {
    slow = slow->next;
    fast = fast->next;
  }

  // Neste ponto, 'slow' esta no no exatamente anterior ao que deve ser
  // removido. A remocao e feita ligando o 'next' de 'slow' ao 'next' do no
  // seguinte.
  slow->next = slow->next->next;
  return head;
}