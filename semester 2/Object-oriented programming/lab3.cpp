#include <iostream>
using namespace std;

class Vector
{
public:
  Vector(int x = 0, int y = 0)
  {
    this->x = x;
    this->y = y;
  }

  friend Vector operator+(Vector V1, Vector V2);

  void operator++()
  {
    ++x;
    ++y;
  }

  void print() { printf_s("X: %d, Y: %d\n", x, y); }
  int getValueX() { return this->x; }
  int getValueY() { return this->y; }

protected:
  int x, y;
};

Vector operator+(Vector V1, Vector V2)
{
  Vector res(V1.getValueX() + V2.getValueX(), V1.getValueY() + V2.getValueY());

  return res;
};

int main()
{
  Vector V1(3, 5), V2(2, 1);
  V1.print();
  V2.print();

  Vector V3 = V1 + V2;
  V3.print();

  Vector V4(7, 8);
  V4.print();
  ++V4;
  V4.print();
}