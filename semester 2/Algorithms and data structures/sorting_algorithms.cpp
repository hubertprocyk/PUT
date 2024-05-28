#include <iostream>
#include <time.h>
#include <chrono>
using namespace std;

void fillRandom(int arr[], int n)
{
  for (int i = 0; i < n; i++)
  {
    // cout << rand() % 10000 << " ";
    arr[i] = rand() % 1000000;
  }
  // cout << "\n";
}
void fillNotLesser(int arr[], int n)
{
  int a = rand() % 100 + 1;
  for (int i = 0; i < n; i++)
  {
    a += rand() % 100;
    // cout << a << " ";
    arr[i] = a;
  }
  // cout << "\n";
}
void fillNotGreater(int arr[], int n)
{
  int a = rand() % 100 + 1;
  for (int i = 0; i < n; i++)
  {
    a -= rand() % 100;
    // cout << a << " ";
    arr[i] = a;
  }
  // cout << "\n";
}
void fillVShaped(int arr[], int n)
{
  int i = 0, j = n - 1, k = 0;
  while (i < j)
  {
    arr[i] = k;
    arr[j] = k - 1;
    i += 1;
    j -= 1;
    k -= 2;
  }
  if (i == j)
  {
    arr[i] = k;
  }
}

void swapTEST(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}
void selectionSort(int arr[], int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    int jMin = i;

    for (int j = i + 1; j < n; j++)
    {
      if (arr[j] < arr[jMin])
      {
        jMin = j;
      }
    }

    swapTEST(&arr[jMin], &arr[i]);
  }
}
void insertionSort(int arr[], int n)
{
  for (int i = 1; i < n; i++)
  {
    int key = arr[i], j = i - 1;

    while (key < arr[j] && j >= 0)
    {
      arr[j + 1] = arr[j];
      j -= 1;
    }

    arr[j + 1] = key;
  }
}
int partition(int arr[], int low, int high)
{
  int pivot = arr[high], i = (low - 1);

  for (int j = low; j < high; j++)
  {
    if (arr[j] <= pivot)
    {
      i += 1;
      swapTEST(&arr[i], &arr[j]);
    }
  }

  swapTEST(&arr[i + 1], &arr[high]);

  return (i + 1);
}
void quickSort(int arr[], int low, int high)
{
  if (low < high)
  {
    int p = partition(arr, low, high);

    quickSort(arr, low, p - 1);
    quickSort(arr, p + 1, high);
  }
}
int randomizedPartition(int arr[], int low, int high)
{
  int i = rand() % (high - low + 1) + low;
  swapTEST(&arr[i], &arr[high]);

  return partition(arr, low, high);
}
void randomizedQuickSort(int arr[], int low, int high)
{
  if (low < high)
  {
    int q = randomizedPartition(arr, low, high);
    randomizedQuickSort(arr, low, q - 1);
    randomizedQuickSort(arr, q + 1, high);
  }
}
void heapify(int arr[], int n, int i)
{
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && arr[left] > arr[largest])
    largest = left;

  if (right < n && arr[right] > arr[largest])
    largest = right;

  if (largest != i)
  {
    swapTEST(&arr[i], &arr[largest]);
    heapify(arr, n, largest);
  }
}
void heapSort(int arr[], int n)
{
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);

  for (int i = n - 1; i >= 0; i--)
  {
    swapTEST(&arr[0], &arr[i]);
    heapify(arr, i, 0);
  }
}
int compare(const void *a, const void *b)
{
  return (*(int *)a - *(int *)b);
}

int main()
{
  using std::chrono::duration;
  using std::chrono::duration_cast;
  using std::chrono::high_resolution_clock;
  using std::chrono::milliseconds;
  srand(time(0));

  int values[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};

  for (int i = 1; i <= 4; i++)
  {
    for (int j = 1; j <= 5; j++)
    {
      for (int k = 0; k < 10; k++)
      {
        int n = values[k];

        int *arr = new int[n];
        switch (i)
        {
        case 1:
          cout << "Losowe ";
          fillRandom(arr, n);
          break;
        case 2:
          cout << "Niemalejace ";
          fillNotLesser(arr, n);
          break;
        case 3:
          cout << "Nierosnace ";
          fillNotGreater(arr, n);
          break;
        case 4:
          cout << "V-ksztaltne ";
          fillVShaped(arr, n);
          break;
        default:
          return 0;
        }

        auto t1 = high_resolution_clock::now();
        switch (j)
        {
        case 1:
          cout << "Selection sort ";
          selectionSort(arr, n);
          break;
        case 2:
          cout << "Insertion sort ";
          insertionSort(arr, n);
          break;
        case 3:
          cout << "Quick sort ";
          // quickSort(arr, 0, n - 1);
          qsort(arr, n, sizeof(int), compare);
          break;
        case 4:
          cout << "Randomized quick sort ";
          randomizedQuickSort(arr, 0, n - 1);
          break;
        case 5:
          cout << "Heap sort ";
          heapSort(arr, n);
          break;
        default:
          return 0;
        }
        auto t2 = high_resolution_clock::now();
        auto ms_int = duration_cast<milliseconds>(t2 - t1);
        duration<double, std::milli> ms_double = t2 - t1;

        cout << n << " Czas: " << ms_double.count() << "\n";
      }

      cout << endl;
    }
  }

  return 0;
}