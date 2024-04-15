#include <set>
#include <random>
#include <chrono>
using namespace std;
struct TreeNode
{
  int key;
  TreeNode *parent;
  TreeNode *left;
  TreeNode *right;
};
struct Root
{
  TreeNode *parent_root;
};
TreeNode *treeSearch(Root &root, int key)
{
  TreeNode *node = root.parent_root;
  while (node != nullptr && node->key != key)
  {
    if (key < node->key)
    {
      node = node->left;
    }
    else if (key > node->key)
    {
      node = node->right;
    }
    else
      break;
  }
  return node;
}
void treeInsert(Root &root, int key)
{
  TreeNode *node = new TreeNode;
  node->parent = nullptr;
  node->left = nullptr;
  node->right = nullptr;
  node->key = key;
  TreeNode *parent = nullptr;
  TreeNode *current = root.parent_root;
  while (current != nullptr && current->key != key)
  {
    parent = current;
    if (key < current->key)
    {
      current = current->left;
    }
    else if (key > current->key)
    {
      current = current->right;
    }
  }
  node->parent = parent;
  if (parent == nullptr)
  {
    root.parent_root = node;
  }
  else if (key < parent->key)
  {
    parent->left = node;
  }
  else
  {
    parent->right = node;
  }
}
void treeInsertBiject(Root &root, int array[], int p, int r)
{
  if (p == r)
  {
    treeInsert(root, array[p]);
  }
  else if (r - p == 1)
  {
    treeInsert(root, array[p]);
    treeInsert(root, array[r]);
  }
  else
  {
    int q = p + (r - p) / 2;
    treeInsert(root, array[q]);
    treeInsertBiject(root, array, p, q - 1);
    treeInsertBiject(root, array, q + 1, r);
  }
}
void balancedTreeCreate(Root &root, int array[], int n)
{
  sort(array, array + n);
  treeInsertBiject(root, array, 0, n - 1);
}
struct ListNode
{
  ListNode *prev;
  ListNode *next;
  int key;
};
struct List
{
  ListNode *head;
};
ListNode *listSearch(List &list, int key)
{
  ListNode *x = list.head;
  while (x != nullptr && x->key != key)
  {
    x = x->next;
  }
  return x;
}
void listInsert(List &list, int key)
{
  ListNode *node = new ListNode;
  node->prev = nullptr;
  node->next = list.head;
  node->key = key;
  if (list.head != nullptr)
  {
    list.head->prev = node;
  }
  list.head = node;
}
void Shuffle(int array[], int n)
{
  random_device rnd;
  mt19937 gen(rnd());
  for (int i = n - 1; i >= 2; i--)
  {
    uniform_int_distribution<> dis(0, i - 1);
    int j = dis(gen);
    swap(array[i], array[j]);
  }
}
void fillIncreasing(int array[], int n)
{
  for (int i = 0; i < n; i++)
  {
    array[i] = i;
  }
}
void fillRandom(int array[], int n)
{
  set<int> s;
  int i = 0;
  random_device rnd;
  mt19937 gen(rnd());
  uniform_int_distribution<> dis(0, n * 4);
  while (s.size() < n)
  {
    int r = dis(gen);
    if (s.find(r) == s.end())
    {
      s.insert(r);
      array[i] = r;
      i++;
    }
  }
}
void benchmark(int array[], double &result1, double &result2, double &result3, int &n)
{
  List list{nullptr};
  Root root{nullptr};
  Root BTreeRoot{nullptr};
  for (int j = 0; j < n; j++)
  {
    listInsert(list, array[j]);
    treeInsert(root, array[j]);
  }
  balancedTreeCreate(BTreeRoot, array, n);
  Shuffle(array, n);
  for (int j = 0; j < n; j++)
  {
    using namespace chrono;
    auto begin = high_resolution_clock::now();
    listSearch(list, array[j]);
    auto end = high_resolution_clock::now();
    auto time_diff = duration_cast<duration<double>>(end - begin);
    result1 += time_diff.count();
    begin = high_resolution_clock::now();
    treeSearch(root, array[j]);
    end = high_resolution_clock::now();
    time_diff = duration_cast<duration<double>>(end - begin);
    result2 += time_diff.count();
    begin = high_resolution_clock::now();
    treeSearch(BTreeRoot, array[j]);
    end = high_resolution_clock::now();
    time_diff = duration_cast<duration<double>>(end - begin);
    result3 += time_diff.count();
  }
}
int main()
{
  int m = 10;
  for (int i = 1; i <= m; i++)
  {
    int n = i * 1000;
    double result1 = 0, result2 = 0, result3 = 0;
    int *array = new int[n];
    printf_s("\n%d\n", n);
    fillIncreasing(array, n);
    for (int j = 1; j <= m; j++)
      benchmark(array, result1, result2, result3, n);
    printf_s("Inc ListSearch:\t\t%.10f\n", result1 / m / n);
    printf_s("Inc TreeSearch:\t\t%.10f\n", result2 / m / n);
    printf_s("Inc B-TreeSearch:\t%.10f\n", result3 / m / n);
    result1 = result2 = result3 = 0;
    fillRandom(array, n);
    for (int j = 1; j <= m; j++)
      benchmark(array, result1, result2, result3, n);
    printf_s("Rand ListSearch:\t%.10f\n", result1 / m / n);
    printf_s("Rand TreeSearch:\t%.10f\n", result2 / m / n);
    printf_s("Rand B-TreeSearch:\t%.10f\n", result3 / m / n);
    result1 = result2 = result3 = 0;
    delete[] array;
  }
  return 0;
}