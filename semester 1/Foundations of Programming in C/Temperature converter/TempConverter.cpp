#include <iostream>
#include <algorithm>
#include <time.h>
#include "header.h"
using namespace std;

int main()
{
  bool loop = true;

  double temperatureHistory[100];
  char scaleHistory[100];
  int dataCounter = 0;
  int *dataCounterPointer = &dataCounter;

  while (loop)
  {
    system("cls");

    printMenu();
    int menuChoice;
    scanf_s("%d", &menuChoice);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    double inputTemperatureValue = 0.0;
    double *inputTemperaturePointer = &inputTemperatureValue;

    switch (menuChoice)
    {
    case 1:
      inputF(inputTemperaturePointer);
      if (check(inputTemperatureValue, 'F'))
      {
        double computedTemperature = FtoC(inputTemperatureValue);
        printf_s("%fF = %fC\n", inputTemperatureValue, computedTemperature);
        saveToHistory(dataCounterPointer, temperatureHistory, inputTemperatureValue, computedTemperature, scaleHistory, 'F', 'C');
      }
      else
      {
        printf_s("Podano temperature z poza zakresu!\n");
      }

      break;
    case 2:
      inputF(inputTemperaturePointer);
      if (check(inputTemperatureValue, 'F'))
      {
        double computedTemperature = FtoK(inputTemperatureValue);
        printf_s("%fF = %fK\n", inputTemperatureValue, computedTemperature);
        saveToHistory(dataCounterPointer, temperatureHistory, inputTemperatureValue, computedTemperature, scaleHistory, 'F', 'K');
      }
      else
      {
        printf_s("Podano temperature z poza zakresu!\n");
      }

      break;
    case 3:
      inputC(inputTemperaturePointer);
      if (check(inputTemperatureValue, 'C'))
      {
        double computedTemperature = CtoF(inputTemperatureValue);
        printf_s("%fC = %fF\n", inputTemperatureValue, computedTemperature);
        saveToHistory(dataCounterPointer, temperatureHistory, inputTemperatureValue, computedTemperature, scaleHistory, 'C', 'F');
      }
      else
      {
        printf_s("Podano temperature z poza zakresu!\n");
      }

      break;
    case 4:
      inputC(inputTemperaturePointer);
      if (check(inputTemperatureValue, 'C'))
      {
        double computedTemperature = CtoK(inputTemperatureValue);
        printf_s("%fC = %fK\n", inputTemperatureValue, computedTemperature);
        saveToHistory(dataCounterPointer, temperatureHistory, inputTemperatureValue, computedTemperature, scaleHistory, 'C', 'K');
      }
      else
      {
        printf_s("Podano temperature z poza zakresu!\n");
      }

      break;
    case 5:
      inputK(inputTemperaturePointer);
      if (check(inputTemperatureValue, 'K'))
      {
        double computedTemperature = KtoC(inputTemperatureValue);
        printf_s("%fK = %fC\n", inputTemperatureValue, computedTemperature);
        saveToHistory(dataCounterPointer, temperatureHistory, inputTemperatureValue, computedTemperature, scaleHistory, 'K', 'C');
      }
      else
      {
        printf_s("Podano temperature z poza zakresu!\n");
      }

      break;
    case 6:
      inputK(inputTemperaturePointer);
      if (check(inputTemperatureValue, 'K'))
      {
        double computedTemperature = KtoF(inputTemperatureValue);
        printf_s("%fK = %fF\n", inputTemperatureValue, computedTemperature);
        saveToHistory(dataCounterPointer, temperatureHistory, inputTemperatureValue, computedTemperature, scaleHistory, 'K', 'F');
      }
      else
      {
        printf_s("Podano temperature z poza zakresu!\n");
      }

      break;
    case 7:
      printHistoryMenu();
      int historyMenuChoice;
      scanf_s("%d", &historyMenuChoice);

      switch (historyMenuChoice)
      {
      case 1:
        printHistory(dataCounterPointer, temperatureHistory, scaleHistory, 'F');
        break;
      case 2:
        printHistory(dataCounterPointer, temperatureHistory, scaleHistory, 'C');
        break;
      case 3:
        printHistory(dataCounterPointer, temperatureHistory, scaleHistory, 'K');
        break;
      case 4:
        // 0 -> dowolny znak nie wywolujacy filtra
        printHistory(dataCounterPointer, temperatureHistory, scaleHistory, '0');
        break;
      default:
        printf_s("Podano nieprawidlowa wartosc. Program wroci do menu glownego.\n");
        continue;
      }

      break;
    case 8:
      if (dataCounter == 0)
        printf_s("Nie ma nic w historii.\n");
      else
      {
        printHistory(dataCounterPointer, temperatureHistory, scaleHistory, '0');
        printf_s("Wybierz wpis do usuniecia: ");
        char str[280];
        scanf_s("%[^\n]", str, 280);
        int historyEntryToRemove = convertToInteger(str, sizeof(str));
        if (conversionFailed || historyEntryToRemove < 0 || historyEntryToRemove > dataCounter / 2)
        {
          printf_s("Podanej wartosci nie udalo sie przekonwertowac na liczbe calkowita lub nie ma w historii wpisu o takim numerze.\n");
          break;
        }
        else
        {
          int arrayOffset = (historyEntryToRemove - 1) * 2;

          copy(temperatureHistory + arrayOffset + 2, temperatureHistory + (dataCounter - 1) * 2 + 1, temperatureHistory + arrayOffset);
          copy(scaleHistory + arrayOffset + 2, scaleHistory + (dataCounter - 1) * 2 + 1, scaleHistory + arrayOffset);

          dataCounter -= 2;
        }
      }

      break;
    case 9:
      if (dataCounter == 0)
        printf_s("Nie ma nic w historii.\n");
      else
      {
        printHistory(dataCounterPointer, temperatureHistory, scaleHistory, '0');
        printf_s("Wybierz wpis do modyfikacji: ");
        char str[280];
        scanf_s("%[^\n]", str, 280);
        int historyEntryToModify = convertToInteger(str, sizeof(str));

        if (conversionFailed || historyEntryToModify < 0 || historyEntryToModify > dataCounter / 2)
        {
          printf_s("Podanej wartosci nie udalo sie przekonwertowac na liczbe calkowita lub nie ma w historii wpisu o takim numerze.\n");
          break;
        }
        else
        {
          int arrayOffset = (historyEntryToModify - 1) * 2;

          printModifyMenu();
          char str[280];
          scanf_s("%[^\n]", str, 280);
          int modifyMenuChoice = convertToInteger(str, sizeof(str));

          if (conversionFailed)
          {
            printf_s("Podano nieprawidlowa wartosc. Program wroci do menu glownego.\n");
          }

          double modifyTemperatureValue = 0.0;
          double *modifyTemperaturePointer = &modifyTemperatureValue;

          switch (modifyMenuChoice)
          {
          case 1:
            inputF(modifyTemperaturePointer);
            if (check(inputTemperatureValue, 'F'))
            {
              double computedTemperature = FtoC(modifyTemperatureValue);
              printf_s("%f = %f\n", modifyTemperatureValue, computedTemperature);
              modifyHistory(arrayOffset, temperatureHistory, modifyTemperatureValue, computedTemperature, scaleHistory, 'F', 'C');
            }
            else
            {
              printf_s("Podano temperature z poza zakresu!\n");
            }
            break;
          case 2:
            inputF(modifyTemperaturePointer);
            if (check(inputTemperatureValue, 'F'))
            {
              double computedTemperature = FtoK(modifyTemperatureValue);
              printf_s("%f = %f\n", modifyTemperatureValue, computedTemperature);
              modifyHistory(arrayOffset, temperatureHistory, modifyTemperatureValue, computedTemperature, scaleHistory, 'F', 'K');
            }
            else
            {
              printf_s("Podano temperature z poza zakresu!\n");
            }
            break;
          case 3:
            inputC(modifyTemperaturePointer);
            if (check(inputTemperatureValue, 'C'))
            {
              double computedTemperature = CtoF(modifyTemperatureValue);
              printf_s("%f = %f\n", modifyTemperatureValue, computedTemperature);
              modifyHistory(arrayOffset, temperatureHistory, modifyTemperatureValue, computedTemperature, scaleHistory, 'C', 'F');
            }
            else
            {
              printf_s("Podano temperature z poza zakresu!\n");
            }
            break;
          case 4:
            inputC(modifyTemperaturePointer);
            if (check(inputTemperatureValue, 'C'))
            {
              double computedTemperature = CtoK(modifyTemperatureValue);
              printf_s("%f = %f\n", modifyTemperatureValue, computedTemperature);
              modifyHistory(arrayOffset, temperatureHistory, modifyTemperatureValue, computedTemperature, scaleHistory, 'C', 'K');
            }
            else
            {
              printf_s("Podano temperature z poza zakresu!\n");
            }
            break;
          case 5:
            inputK(modifyTemperaturePointer);
            if (check(inputTemperatureValue, 'K'))
            {
              double computedTemperature = KtoC(modifyTemperatureValue);
              printf_s("%f = %f\n", modifyTemperatureValue, computedTemperature);
              modifyHistory(arrayOffset, temperatureHistory, modifyTemperatureValue, computedTemperature, scaleHistory, 'K', 'C');
            }
            else
            {
              printf_s("Podano temperature z poza zakresu!\n");
            }
            break;
          case 6:
            inputK(modifyTemperaturePointer);
            if (check(inputTemperatureValue, 'K'))
            {
              double computedTemperature = KtoF(modifyTemperatureValue);
              printf_s("%f = %f\n", modifyTemperatureValue, computedTemperature);
              modifyHistory(arrayOffset, temperatureHistory, modifyTemperatureValue, computedTemperature, scaleHistory, 'K', 'F');
            }
            else
            {
              printf_s("Podano temperature z poza zakresu!\n");
            }
            break;
          default:
            printf_s("Nieprawidlowy wybor!\n");
            break;
          }
        }
      }
      break;
    case 10:
    {
    }
      if (dataCounter >= 100)
      {
        printf_s("Historia pelna!");
      }
      else
      {
        printf_s("Liczba losowych liczb: ");

        char str[280];
        scanf_s("%[^\n]", str, 280);
        int randomNumbersToGenerate = convertToInteger(str, sizeof(str));

        if (conversionFailed)
        {
          printf_s("Podanej wartosci nie udalo sie przekonwertowc na liczbe calkowita. Uzywam domyslnej wartosci 10.");
          randomNumbersToGenerate = 10;
        }

        if (dataCounter + randomNumbersToGenerate * 2 > 100)
        {
          printf_s("W historii nie ma miejsca na tyle liczb. Czy wygerenowac tylko tyle ile sie zmiesci? [T/N]: ");
          char randomConfirm;
          scanf_s("%c*f", &randomConfirm, 1);
          if (randomConfirm == 'N' || randomConfirm == 'n')
            continue;
          else
          {
            randomNumbersToGenerate = (100 - dataCounter) / 2;
          }
        }

        srand(time(0));
        for (int i = 0; i < randomNumbersToGenerate; i++)
        {
          int x = rand() % 1000 + 1;
          double randomTemperature = (double)x;
          int conversion = rand() % 6 + 1;

          double computedTemperature;

          switch (conversion)
          {
          case 1:
            randomTemperature -= 469.67;
            computedTemperature = FtoC(randomTemperature);
            printf_s("%f = %f\n", randomTemperature, computedTemperature);
            saveToHistory(dataCounterPointer, temperatureHistory, randomTemperature, computedTemperature, scaleHistory, 'F', 'C');
            break;
          case 2:
            randomTemperature -= 469.67;
            computedTemperature = FtoK(randomTemperature);
            printf_s("%f = %f\n", randomTemperature, computedTemperature);
            saveToHistory(dataCounterPointer, temperatureHistory, randomTemperature, computedTemperature, scaleHistory, 'F', 'K');
            break;
          case 3:
            randomTemperature -= 273.15;
            computedTemperature = CtoF(randomTemperature);
            printf_s("%f = %f\n", randomTemperature, computedTemperature);
            saveToHistory(dataCounterPointer, temperatureHistory, randomTemperature, computedTemperature, scaleHistory, 'C', 'F');
            break;
          case 4:
            randomTemperature -= 273.15;
            computedTemperature = CtoK(randomTemperature);
            printf_s("%f = %f\n", randomTemperature, computedTemperature);
            saveToHistory(dataCounterPointer, temperatureHistory, randomTemperature, computedTemperature, scaleHistory, 'C', 'K');
            break;
          case 5:
            computedTemperature = KtoC(randomTemperature);
            printf_s("%f = %f\n", randomTemperature, computedTemperature);
            saveToHistory(dataCounterPointer, temperatureHistory, randomTemperature, computedTemperature, scaleHistory, 'K', 'C');
            break;
          case 6:
            computedTemperature = KtoF(randomTemperature);
            printf_s("%f = %f\n", randomTemperature, computedTemperature);
            saveToHistory(dataCounterPointer, temperatureHistory, randomTemperature, computedTemperature, scaleHistory, 'K', 'F');
            break;
          }
        }
      }

      break;
    default:
      printf_s("Podano nieprawidlowa wartosc. Program zakonczy dzialanie\n");
      loop = false;
      continue;
    }

    // godziny szukania w internecie jak sprawic by program zaczekal na input przed kolejnym wykonaniem petli
    // z niezrozumialych do konca dla mnie przyczyn wszystkie inne sposoby na pobranie znaku byly pomijane
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
  }

  return 0;
}