#include <iostream>
using namespace std;

int main()
{
  int player1Points = 0, player2Points = 0, round = 0;
  bool gameFinished = false;
  while (!gameFinished)
  {
    system("cls");
    round += 1;

    char player1Move, player2Move;
    cout << "Runda " << round << ", Ruch gracza 1 [K/P/N]: ";
    cin >> player1Move;
    system("cls");
    cout << "Runda " << round << ", Ruch gracza 2 [K/P/N]: ";
    cin >> player2Move;
    system("cls");

    // Check moves
    if (player1Move == player2Move)
    {
      cout << "Remis!\n";
      system("pause");
    }
    if (player1Move == 'K')
    {
      if (player2Move == 'N')
      {
        player1Points += 1;
        cout << "Punkt zdobywa Gracz 1!\n";
        system("pause");
      }
      else
      {
        player2Points += 1;
        cout << "Punkt zdobywa Gracz 2!\n";
        system("pause");
      }
    }
    if (player1Move == 'P')
    {
      if (player2Move == 'K')
      {
        player1Points += 1;
        cout << "Punkt zdobywa Gracz 1!\n";
        system("pause");
      }
      else
      {
        player2Points += 1;
        cout << "Punkt zdobywa Gracz 2!\n";
        system("pause");
      }
    }
    if (player1Move == 'N')
    {
      if (player2Move == 'P')
      {
        player1Points += 1;
        cout << "Punkt zdobywa Gracz 1!\n";
        system("pause");
      }
      else
      {
        player2Points += 1;
        cout << "Punkt zdobywa Gracz 2!\n";
        system("pause");
      }
    }

    // Win
    if (player1Points == 5)
    {
      gameFinished = true;
      cout << "Wygrywa Gracz 1!";
    }
    if (player2Points == 5)
    {
      gameFinished = true;
      cout << "Wygrywa Gracz 2!";
    }
  }
  return 0;
}