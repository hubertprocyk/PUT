#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int data;
  struct Node *next;
};

Node *head = NULL;

void appendNode(int value)
{
  Node *newNode = new Node();
  newNode->data = value;
  newNode->next = NULL;

  if (head == NULL)
  {
    // Lista jest pusta
    head = newNode;
  }
  else
  {
    // Dodanie węzła na koniec listy
    Node *current = head;
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = newNode;
  }
}
void deleteOneMatchingNode(int key)
{
  Node *current = head;
  Node *prevNode = NULL;
  int deleted = 0; // Zmienna informująca, czy znaleziono chociaż jeden element o podanym kluczu

  while (current != NULL)
  {
    if (current->data == key)
    {
      // Znaleziono węzeł do usunięcia
      if (prevNode != NULL)
      {
        prevNode->next = current->next;
      }
      else
      {
        // Usuwany węzeł jest głową listy
        head = current->next;
      }

      delete current;
      deleted = 1; // Ustawienie flagi, że znaleziono chociaż jeden element o podanym kluczu

      // Przechodzenie dalej po liście
      current = current->next;
    }
    else
    {
      // Przechodzenie dalej po liście
      prevNode = current;
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
}
void printList()
{
  Node *current = head;

  printf("Lista: ");

  while (current != NULL)
  {
    printf("%d ", current->data);
    current = current->next;
  }

  printf("\n");
}

int main()
{
  appendNode(1);
  appendNode(2);
  appendNode(2);
  appendNode(2);
  appendNode(3);
  appendNode(3);

  printList();

  deleteOneMatchingNode(2);
  printList();

  deleteAllNodes();
  printList();

  return 0;
}