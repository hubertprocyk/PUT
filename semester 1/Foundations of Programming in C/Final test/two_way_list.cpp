#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int key;
  Node *prev;
  Node *next;
};

Node *head = NULL;
Node *tail = NULL;

void appendNode(int value)
{
  Node *newNode = new Node();
  newNode->key = value;
  newNode->prev = NULL;
  newNode->next = NULL;

  if (head == NULL)
  {
    // Lista jest pusta
    head = newNode;
    tail = newNode;
  }
  else
  {
    // Dodanie węzła na koniec listy
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
  }
}
void deleteOneMatchingNode(int key)
{
  Node *current = head;

  while (current != NULL)
  {
    if (current->key == key)
    {
      // Znaleziono węzeł do usunięcia
      if (current->prev != NULL)
      {
        current->prev->next = current->next;
      }
      else
      {
        // Usuwany węzeł jest głową listy
        head = current->next;
      }

      if (current->next != NULL)
      {
        current->next->prev = current->prev;
      }
      else
      {
        // Usuwany węzeł jest ogonem listy
        tail = current->prev;
      }

      delete current;
      return;
    }

    current = current->next;
  }

  printf("Element o kluczu %d nie zostal znaleziony.\n", key);
}
void deleteAllMatchingNodes(int key)
{
  struct Node *current = head;
  struct Node *nextNode;
  int deleted = 0;

  while (current != NULL)
  {
    if (current->key == key)
    {
      // Znaleziono węzeł do usunięcia
      nextNode = current->next;

      if (current->prev != NULL)
      {
        current->prev->next = current->next;
      }
      else
      {
        // Usuwany węzeł jest głową listy
        head = current->next;
      }

      if (current->next != NULL)
      {
        current->next->prev = current->prev;
      }
      else
      {
        // Usuwany węzeł jest ogonem listy
        tail = current->prev;
      }

      delete current;
      deleted = 1;

      // Przechodzenie dalej po liście
      current = nextNode;
    }
    else
    {
      // Przechodzenie dalej po liście
      current = current->next;
    }
  }

  if (deleted == 0)
    printf("Element o kluczu %d nie zostal znaleziony.\n", key);
}
void deleteAllNodes()
{
  Node *current = head;
  Node *nextNode;

  while (current != NULL)
  {
    nextNode = current->next;
    delete current;
    current = nextNode;
  }

  head = NULL;
  tail = NULL;
}
void printList()
{
  Node *current = head;

  printf("Lista: ");
  while (current != NULL)
  {
    printf("%d ", current->key);
    current = current->next;
  }

  printf("\n");
}
void printListBackwards()
{
  struct Node *current = tail;

  printf("Lista w odwrotnej kolejności: ");

  while (current != NULL)
  {
    printf("%d ", current->key);
    current = current->prev;
  }

  printf("\n");
}

int main()
{
  // Dodanie węzłów do listy
  appendNode(1);
  appendNode(2);
  appendNode(2);
  appendNode(2);
  appendNode(3);
  appendNode(3);

  printList();

  deleteOneMatchingNode(3);
  printList();
  printListBackwards();

  deleteAllMatchingNodes(2);
  printList();

  deleteAllNodes();
  printList();

  return 0;
}
