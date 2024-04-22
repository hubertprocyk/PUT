#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
class MaxFinder
{
public:
  virtual T findMax(const vector<T> &array) const = 0;
};

class IntMaxFinder : public MaxFinder<int>
{
public:
  int findMax(const vector<int> &array) const override
  {
    return *max_element(array.begin(), array.end());
  }
};

class FloatMaxFinder : public MaxFinder<float>
{
public:
  float findMax(const vector<float> &array) const override
  {
    return *max_element(array.begin(), array.end());
  }
};

class CharMaxFinder : public MaxFinder<char>
{
public:
  char findMax(const vector<char> &array) const override
  {
    return *max_element(array.begin(), array.end());
  }
};

int main()
{
  vector<int> intArray = {3, 7, 2, 9, 5};
  IntMaxFinder intMaxFinder;
  cout << "Max int: " << intMaxFinder.findMax(intArray) << endl;

  vector<float> floatArray = {3.5, 7.2, 2.9, 9.1, 5.6};
  FloatMaxFinder floatMaxFinder;
  cout << "Max float: " << floatMaxFinder.findMax(floatArray) << endl;

  vector<char> charArray = {'a', 'c', 'e', 'b'};
  CharMaxFinder charMaxFinder;
  cout << "Max char: " << charMaxFinder.findMax(charArray) << endl;

  return 0;
}