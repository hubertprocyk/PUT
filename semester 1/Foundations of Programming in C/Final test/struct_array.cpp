#include <stdio.h>
#include <stdlib.h>

#define MAX_USERS 10

// Struktura przechowująca dane użytkownika
struct User
{
  int id;
  char name[50];
  char surname[50];
};

// Tablica struktur przechowująca dane użytkowników
User users[MAX_USERS];

// Zmienna do śledzenia liczby aktualnie przechowywanych użytkowników
int userCount = 0;

// Funkcja dodająca nowego użytkownika do tablicy
void addUser()
{
  if (userCount < MAX_USERS)
  {
    printf("Podaj ID, imię i nazwisko użytkownika (oddzielone spacjami): ");
    scanf("%d %s %s", &users[userCount].id, users[userCount].name, users[userCount].surname);
    userCount++;
    printf("Użytkownik dodany.\n");
  }
  else
  {
    printf("Tablica użytkowników jest pełna. Nie można dodać kolejnego użytkownika.\n");
  }
}

// Funkcja wyświetlająca wszystkich użytkowników
void displayUsers()
{
  if (userCount > 0)
  {
    printf("ID\tImię\tNazwisko\n");
    for (int i = 0; i < userCount; i++)
    {
      printf("%d\t%s\t%s\n", users[i].id, users[i].name, users[i].surname);
    }
  }
  else
  {
    printf("Brak użytkowników do wyświetlenia.\n");
  }
}

// Funkcja modyfikująca użytkownika po ID
void modifyUserById()
{
  int targetId;
  printf("Podaj ID użytkownika do modyfikacji: ");
  scanf("%d", &targetId);

  int foundIndex = -1;
  for (int i = 0; i < userCount; i++)
  {
    if (users[i].id == targetId)
    {
      foundIndex = i;
      break;
    }
  }

  if (foundIndex != -1)
  {
    printf("Podaj nowe imię i nazwisko użytkownika (oddzielone spacjami): ");
    scanf("%s %s", users[foundIndex].name, users[foundIndex].surname);
    printf("Dane użytkownika zaktualizowane.\n");
  }
  else
  {
    printf("Użytkownik o podanym ID nie istnieje.\n");
  }
}

int main()
{
  int choice;

  do
  {
    printf("\nMenu:\n");
    printf("1. Dodaj użytkownika\n");
    printf("2. Wyświetl wszystkich użytkowników\n");
    printf("3. Zmodyfikuj użytkownika po ID\n");
    printf("0. Zakończ program\n");
    printf("Wybierz opcję: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
      addUser();
      break;
    case 2:
      displayUsers();
      break;
    case 3:
      modifyUserById();
      break;
    case 0:
      printf("Zakończono program.\n");
      break;
    default:
      printf("Nieprawidłowy wybór. Wybierz ponownie.\n");
    }
  } while (choice != 0);

  return 0;
}