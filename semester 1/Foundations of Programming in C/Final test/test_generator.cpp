#include <iostream>
#include <string>
#include <time.h>
#include <algorithm>
#include <vector>
using namespace std;

struct Task
{
  int ID = 0;
  int points = 0;
  string text = "";
  Task *prev = NULL;
  Task *next = NULL;
};
Task *head = NULL;
Task *tail = NULL;
int task_count = 0;

void add_task()
{
  string text;
  int ID, points;
  cout << "Numer zadania: ";
  cin >> ID;
  cout << "Tresc zadania: ";
  cin >> text;
  cout << "Za ile punktow: ";
  cin >> points;

  Task *newTask = new Task();
  newTask->ID = ID;
  newTask->text = text;
  newTask->points = points;
  newTask->prev = NULL;
  newTask->next = NULL;

  task_count += 1;

  if (head == NULL)
  {
    // Lista jest pusta
    head = newTask;
    tail = newTask;
  }
  else
  {
    // Dodanie węzła na koniec listy
    tail->next = newTask;
    newTask->prev = tail;
    tail = newTask;
  }
};
void delete_task()
{
  int task_to_delete_ID;
  cout << "Podaj numer zadania do usuniecia: ";
  cin >> task_to_delete_ID;

  Task *current = head;

  while (current != NULL)
  {
    if (current->ID == task_to_delete_ID)
    {
      // Znaleziono węzeł do usunięcia
      if (current->prev != NULL)
      {
        current->prev->next = current->next;
      }
      else
      {
        // Usuwany węzeł jest pierwszy na liście
        head = current->next;
      }

      if (current->next != NULL)
      {
        current->next->prev = current->prev;
      }
      else
      {
        // Usuwany węzeł jest ostatni na liście
        tail = current->prev;
      }

      task_count -= 1;
      delete current;
      return;
    }

    current = current->next;
  }
  cout << "Zadania o takim numerze nie ma w bazie!";
  system("pause");
};
void modify_task()
{
  int task_to_modify_ID;
  cout << "Podaj numer zadania do zmodyfikowania: ";
  cin >> task_to_modify_ID;

  Task *current = head;

  while (current != NULL)
  {
    if (current->ID == task_to_modify_ID)
    {
      string text;
      int ID, points;
      cout << "Nowy numer zadania: ";
      cin >> ID;
      cout << "Nowa tresc zadania: ";
      cin >> text;
      cout << "Nowa wartosc punktow: ";
      cin >> points;

      current->ID = ID;
      current->points = points;
      current->text = text;

      return;
    }

    current = current->next;
  }
  cout << "Zadania o takim numerze nie ma w bazie!";
  system("pause");
};
void print_all_tasks()
{
  if (task_count == 0)
  {
    cout << "W bazie nie ma zadnych pytan!\n";
    system("pause");
    return;
  }

  Task *current = head;

  cout << "\nWszystkie zadania w bazie: \n";
  while (current != NULL)
  {
    cout << "Zadanie #" << current->ID << " Punkty: " << current->points << "\n";
    cout << "Tresc: " << current->text << "\n\n";
    current = current->next;
  }

  printf("\n");
  system("pause");
};
void generate_test()
{
  int test_task_count;
  cout << "Podaj ile zadan ma byc na kolokwium: ";
  cin >> test_task_count;

  if (test_task_count <= 0)
  {
    cout << "Na kolokwium musi byc przynajmniej 1 zadanie!\n";
    system("pause");
    return;
  }
  if (test_task_count > task_count)
  {
    cout << "W bazie nie ma tyle zadan!\n";
    system("pause");
    return;
  }

  vector<int> UsedTasks;
  int task_order = 1;

  srand(time(NULL));
  while (test_task_count != 0)
  {
    int random_task = rand() % task_count;

    Task *picked = head;
    for (int i = 0; i < random_task; i++)
    {
      picked = picked->next;
    }

    if (!(find(UsedTasks.begin(), UsedTasks.end(), picked->ID) != UsedTasks.end()))
    {
      cout << "Zadanie " << task_order << " (" << picked->points << " pkt)\n";
      cout << picked->text << "\n\n";
      UsedTasks.push_back(picked->ID);
      task_order += 1;
      test_task_count -= 1;
    }
  }
  system("pause");
};

int main()
{
  bool loop = true;

  while (loop)
  {
    system("cls");

    int menu_choice;
    cout << "Wybierz co chcesz zrobic:\n";
    cout << "1. Dodaj zadanie\n";
    cout << "2. Usun zadanie\n";
    cout << "3. Modyfikuj zadanie\n";
    cout << "4. Wypisz wszystkie zadania z bazy\n";
    cout << "5. Wygeneruj kolokwium\n";
    cout << "6. Zakoncz program\n";
    cin >> menu_choice;

    switch (menu_choice)
    {
    case 1:
      add_task();
      break;
    case 2:
      delete_task();
      break;
    case 3:
      modify_task();
      break;
    case 4:
      print_all_tasks();
      break;
    case 5:
      generate_test();
      break;
    case 6:
    default:
      loop = false;
      break;
    }
  }

  return 0;
}