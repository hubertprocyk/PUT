#pragma once

bool conversionFailed = false;
double convertToDouble(const char vector[], int size)
{
  double result = 0.0;
  double fractionalMultiplier = 0.1;
  bool isNegative = false;
  bool isFractional = false;
  bool signRecognised = false;

  for (int i = 0; i < size; ++i)
  {
    if (vector[i] == '\0')
    {
      break;
    }

    if (isdigit(vector[i]))
    {
      if (isFractional)
      {
        result += (vector[i] - '0') * fractionalMultiplier;
        fractionalMultiplier *= 0.1;
      }
      else
      {
        result = result * 10.0 + (vector[i] - '0');
      }
    }
    else if (vector[i] == '.' && isFractional == false)
    {
      isFractional = true;
    }
    else if (vector[i] == '-' && signRecognised == false)
    {
      signRecognised = true;
      isNegative = true;
    }
    else if (vector[i] == '+' && signRecognised == false)
    {
      signRecognised = true;
      continue;
    }
    else
    {
      if (conversionFailed == false)
      {
        printf_s("Wow wow. Very double. Much digit. So wise\n");
        conversionFailed = true;
      }
    }
  }
  return isNegative ? -result : result;
}
int convertToInteger(const char vector[], int size)
{
  int result = 0;
  bool isNegative = false;

  for (int i = 0; i < size; ++i)
  {
    if (vector[i] == '\0')
      break;

    if (isdigit(vector[i]))
    {
      result = result * 10 + (vector[i] - '0');
    }
    else if (vector[i] == '-' && i == 0)
    {
      isNegative = true;
    }
    else if (vector[i] == '+' && i == 0)
    {
      continue;
    }
    else
    {
      if (conversionFailed == false)
      {
        printf_s("Damn it CJ. YOU HAD ONE JOB!\n");
        conversionFailed = true;
      }
    }
  }

  return isNegative ? -result : result;
}

void printMenu()
{
  printf_s("Turbo Konwerter Temperatur\n");
  printf_s("1: Fahr -> Celsius\n");
  printf_s("2: Fahr -> Kelvin\n");
  printf_s("3: Celsius -> Fahr\n");
  printf_s("4: Celsius -> Kelvin\n");
  printf_s("5: Kelvin -> Celsius\n");
  printf_s("6: Kelvin -> Fahr\n");
  printf_s("7: Pokaz historie\n");
  printf_s("8: Usun z historii\n");
  printf_s("9: Modyfikuj historie\n");
  printf_s("10: Wypelnij historie losowymi liczbami\n");
  printf_s("11: Zakoncz dzialanie programu\n");
  printf_s("Wybierz akcje: ");
}

void inputF(double *globalTemperaturePointer)
{
  printf_s("Podaj temperature w Fahr: ");
  char str[280];
  scanf_s("%[^\n]", str, 280);
  double stopnie = convertToDouble(str, sizeof(str));
  if (conversionFailed)
  {
    printf_s("Podanej wartosci nie udalo sie przekonwertowac na liczbe zmiennoprzecinkowa. Uzywam domyslnej wartosci 68.");
    stopnie = 70;
  }
  *globalTemperaturePointer = stopnie;
}
void inputC(double *globalTemperaturePointer)
{
  printf_s("Podaj temperature w Celsjuszach: ");
  char str[280];
  scanf_s("%[^\n]", str, 280);
  double stopnie = convertToDouble(str, sizeof(str));
  if (conversionFailed)
  {
    printf_s("Podanej wartosci nie udalo sie przekonwertowac na liczbe zmiennoprzecinkowa. Uzywam domyslnej wartosci 20.");
    stopnie = 20;
  }
  *globalTemperaturePointer = stopnie;
}
void inputK(double *globalTemperaturePointer)
{
  printf_s("Podaj temperature w Kelvinach: ");
  char str[280];
  scanf_s("%[^\n]", str, 280);
  double stopnie = convertToDouble(str, sizeof(str));
  if (conversionFailed)
  {
    printf_s("Podanej wartosci nie udalo sie przekonwertowac na liczbe zmiennoprzecinkowa. Uzywam domyslnej wartosci 293.15.");
    stopnie = 293.15;
  }
  *globalTemperaturePointer = stopnie;
}

int check(double temperatureValue, char scale)
{
  switch (scale)
  {
  case 'K':
    if (temperatureValue < 0)
      return 0;
    else
      return 1;
    break;
  case 'C':
    if (temperatureValue < -273.15)
      return 0;
    else
      return 1;
    break;
  case 'F':
    if (temperatureValue < -469.67)
      return 0;
    else
      return 1;
    break;
  default:
    return 0;
  }
}

double FtoC(double temperatureValue)
{
  return (5.0 / 9.0) * (temperatureValue - 32.0);
}
double FtoK(double temperatureValue)
{
  return (temperatureValue + 459.67) * (5.0 / 9.0);
}
double CtoF(double temperatureValue)
{
  return (9.0 / 5.0) * temperatureValue + 32;
}
double CtoK(double temperatureValue)
{
  return temperatureValue + 273.15;
}
double KtoC(double temperatureValue)
{
  return temperatureValue - 273.15;
}
double KtoF(double temperatureValue)
{
  return temperatureValue * (9.0 / 5.0) - 459.67;
}

void saveToHistory(
    int *dataCounterPointer,
    double temperatureHistory[],
    double inputTemperature,
    double computedTemperature,
    char scaleHistory[],
    char inputScale,
    char computedScale)
{
  if (*dataCounterPointer < 100)
  {
    temperatureHistory[*dataCounterPointer] = inputTemperature;
    temperatureHistory[*dataCounterPointer + 1] = computedTemperature;
    scaleHistory[*dataCounterPointer] = inputScale;
    scaleHistory[*dataCounterPointer + 1] = computedScale;
    *dataCounterPointer += 2;
  }
  else
  {
    printf_s("Brak miejsca w historii, wynik nie zostnaie zapisany");
  }
}

void printHistoryMenu()
{
  printf_s("1: Tylko F -> inne\n");
  printf_s("2: Tylko C -> inne\n");
  printf_s("3: Tylko K -> inne\n");
  printf_s("4: Cala historia\n");
}

void printHistory(
    int *dataCounterPointer,
    double temperatureHistory[],
    char scaleHistory[],
    char filter)
{
  int resultCounter = 0;
  if (filter == 'F' || filter == 'C' || filter == 'K')
  {
    for (int i = 0; i < *dataCounterPointer; i += 2)
    {
      if (scaleHistory[i] == filter)
      {
        printf_s("<%d> %f%c = %f%c\n", i / 2 + 1, temperatureHistory[i], scaleHistory[i], temperatureHistory[i + 1], scaleHistory[i + 1]);
        resultCounter++;
      }
    }
  }
  else
  {
    for (int i = 0; i < *dataCounterPointer; i += 2)
    {
      printf_s("<%d> %f%c = %f%c\n", i / 2 + 1, temperatureHistory[i], scaleHistory[i], temperatureHistory[i + 1], scaleHistory[i + 1]);
      resultCounter++;
    }
  }
  if (resultCounter == 0)
  {
    printf_s("Brak danych.\n");
  }
}

void printModifyMenu()
{
  printf_s("Wybierz typ przeliczania\n");
  printf_s("1: Fahr -> Celsius\n");
  printf_s("2: Fahr -> Kelvin\n");
  printf_s("3: Celsius -> Fahr\n");
  printf_s("4: Celsius -> Kelvin\n");
  printf_s("5: Kelvin -> Celsius\n");
  printf_s("6: Kelvin -> Fahr\n");
  printf_s("Wybierz akcje: ");
}

void modifyHistory(
    int index,
    double temperatureHistory[],
    double modifyTemperature,
    double computedTemperature,
    char scaleHistory[],
    char inputScale,
    char computedScale)
{
  temperatureHistory[index] = modifyTemperature;
  temperatureHistory[index + 1] = computedTemperature;
  scaleHistory[index] = inputScale;
  scaleHistory[index + 1] = computedScale;
}