#include <iostream>
#include <string>
using namespace std;

class Figura
{
public:
  Figura(){};
  string kolor;

  void opis()
  {
    cout << "Kolor: " << this->kolor;
  }
};

class Kolo : public Figura
{
public:
  Kolo() {}
  Kolo(string kolor, int promien)
  {
    this->kolor = kolor;
    this->promien = promien;
  }
  int promien;

  void opis()
  {
    cout << "Kolor: " << this->kolor << endl;
    printf_s("Pole: %f\n", this->promien * this->promien * 3.14);
    printf_s("Obwod: %f\n", this->promien * 3.14 * 2);
  }
};

class Kwadrat : public Figura
{
public:
  Kwadrat(){};
  Kwadrat(string kolor, int bok)
  {
    this->kolor = kolor;
    this->bok = bok;
  }
  int bok;

  void opis()
  {
    cout << "Kolor: " << this->kolor << endl;
    printf_s("Pole: %d\n", this->bok * this->bok);
    printf_s("Obwod: %d\n", this->bok * 4);
  }
};

int main()
{
  Kolo C1("czerwony", 3);
  Kwadrat S1("zielony", 3);

  printf_s("Kolo:\n");
  C1.opis();
  printf_s("\nKwadrat:\n");
  S1.opis();
}