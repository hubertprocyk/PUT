#include <iostream>
#include <string>
using namespace std;

struct Boat
{
  int pojemnosc = 0;
  string kolor = "";
  string typ = "";
  Boat *next = NULL;
};
struct Res
{
  string day;
  Boat boat;
  Res *next;
};
struct Lease
{
  string day;
  Boat boat;
  Lease *next;
};

Boat *head_boats = NULL;
Res *head_res = NULL;
Lease *head_lease = NULL;

void add_boat()
{
  string kolor, typ;
  int pojemnosc;
  cout << "Typ lodki: ";
  cin >> typ;
  cout << "Kolor lodki: ";
  cin >> kolor;
  cout << "Pojemnosc lodki: ";
  cin >> pojemnosc;

  Boat *newBoat = new Boat();
  newBoat->kolor = kolor;
  newBoat->typ = typ;
  newBoat->pojemnosc = pojemnosc;
  newBoat->next = NULL;

  if (head_boats == NULL)
  {
    // Lista jest pusta
    head_boats = newBoat;
  }
  else
  {
    // Dodanie węzła na koniec listy
    Boat *current = head_boats;
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = newBoat;
  }
}
void add_res()
{
  string day;
  cout << "Dzien: ";
  cin >> day;
  Res *newRes = new Res();
  newRes->day = day;
  newRes->next = NULL;

  if (head_res == NULL)
  {
    // Lista jest pusta
    head_res = newRes;
  }
  else
  {
    // Dodanie węzła na koniec listy
    Res *current = head_res;
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = newRes;
  }
}
void add_lease()
{
  string day;
  cout << "Dzien: ";
  cin >> day;
  Lease *newLease = new Lease();
  newLease->day = day;
  newLease->next = NULL;

  if (head_lease == NULL)
  {
    // Lista jest pusta
    head_lease = newLease;
  }
  else
  {
    // Dodanie węzła na koniec listy
    Lease *current = head_lease;
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = newLease;
  }
}
void delete_res()
{
  string day;
  cout << "Dzien: ";
  cin >> day;

  Res *current = head_res;
  Res *prevNode = NULL;
  int deleted = 0; // Zmienna informująca, czy znaleziono chociaż jeden element o podanym kluczu

  while (current != NULL)
  {
    if (current->day == day)
    {
      // Znaleziono węzeł do usunięcia
      if (prevNode != NULL)
      {
        prevNode->next = current->next;
      }
      else
      {
        // Usuwany węzeł jest głową listy
        head_res = current->next;
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
    printf("Nie znaleziono takiego elementu.\n");
}
// void delete_lease() {} to samo co delete_res tylko nazwy pozmieniać

int main()
{
  bool loop = true;

  while (loop)
  {
    system("cls");

    int menu_choice;
    cout << "Wybierz co chcesz zrobic:\n";
    cout << "1. Dodaj lodke\n";
    cout << "2. Dodaj rezerwacje\n";
    cout << "3. Usun rezerwacje\n";
    cout << "4. Dodaj wypozyczenie\n";
    cout << "5. Usun wypozyczenie\n";
    cout << "6. Zamknij program\n";
    cin >> menu_choice;

    switch (menu_choice)
    {
    case 1:
      add_boat();
      break;
    case 2:
      add_res();
      break;
    case 3:
      delete_res();
      break;
    case 4:
      add_lease();
      break;
    case 5:
      // delete_lease();
      break;
    case 6:
    default:
      loop = false;
      break;
    }
  }

  return 0;
}