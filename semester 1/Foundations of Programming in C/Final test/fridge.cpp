#include <iostream>
#include <string>
using namespace std;

struct Produkt
{
  string nazwa = "";
  int ilosc = 0;
  int termin = 0;
  Produkt *next = NULL;
};
Produkt *head = NULL;

void add_product()
{
  string nazwa;
  int ilosc, termin;
  cout << "Podaj nazwe produktu: ";
  cin >> nazwa;
  cout << "Podaj ilosc produktu: ";
  cin >> ilosc;
  cout << "Podaj ile dni przydatności ma produkt: ";
  cin >> termin;

  Produkt *nowyProdukt = new Produkt();
  nowyProdukt->ilosc = ilosc;
  nowyProdukt->nazwa = nazwa;
  nowyProdukt->termin = termin;
  nowyProdukt->next = NULL;

  if (head == NULL)
  {
    // lista jest pusta
    head = nowyProdukt;
  }
  else
  {
    Produkt *current = head;
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = nowyProdukt;
  }
};
void delete_product()
{
  string nazwa;
  cout << "Wpisz nazwe produktu, ktory chcesz usunac: ";
  cin >> nazwa;

  Produkt *current = head;
  Produkt *prev = NULL;
  while (current != NULL)
  {
    if (current->nazwa == nazwa)
    {
      // Znaleziono węzeł do usunięcia
      if (prev != NULL)
      {
        prev->next = current->next;
      }
      else
      {
        // Usuwany węzeł jest głową listy
        head = current->next;
      }

      delete current;
      return;
    }
    else
    {
      // Przechodzenie dalej po liście
      prev = current;
      current = current->next;
    }
    current = current->next;
  }
};
void alert(int currentDay)
{
  Produkt *current = head;

  while (current != NULL)
  {
    if (current->termin - currentDay == 1)
    {
      cout << "UWAGA, jutro " << current->nazwa << " sie przeterminuje!\n";
    }
    if (current->termin <= currentDay)
    {
      cout << "ALERT, " << current->nazwa << " jest przeterminowana!\n";
    }

    current = current->next;
  }
  cout << "\n";
};
void print_products()
{
  Produkt *current = head;

  cout << "Wszystkie produkty: \n";
  while (current != NULL)
  {
    cout << current->ilosc << "x " << current->nazwa << ", do " << current->termin << " dnia\n";
    current = current->next;
  }
  cout << "\n";
  system("pause");
};

int main()
{
  int day = 0;
  bool loop = true;
  while (loop)
  {
    system("cls");

    cout << "Dzien " << day << "\n";
    alert(day);

    int menu_choice;
    cout << "Wybierz co chcesz zrobic:\n";
    cout << "1. Dodaj produkt\n";
    cout << "2. Zuzyj produkt\n";
    cout << "3. Uplyw czasu 1 dzien\n";
    cout << "4. Uplyw czasu 3 dni\n";
    cout << "5. Uplyw czasu tydzien\n";
    cout << "6. Wypisz produkty\n";
    cout << "7. Zakoncz program\n";
    cin >> menu_choice;

    switch (menu_choice)
    {
    case 1:
      add_product();
      break;
    case 2:
      delete_product();
      break;
    case 3:
      day += 1;
      break;
    case 4:
      day += 3;
      break;
    case 5:
      day += 7;
      break;
    case 6:
      print_products();
      break;
    case 7:
    default:
      loop = false;
      break;
    }
  }

  return 0;
}