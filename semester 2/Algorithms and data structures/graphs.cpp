#include <vector>
#include <queue>
#include <random>
#include <chrono>
using namespace std;

struct GraphMatrix
{
  int V;
  vector<vector<bool>> matrix;

  GraphMatrix(int n)
  {
    V = n;
    matrix.resize(V, vector<bool>(V, false));
  }

  void addEdge(int u, int v)
  {
    matrix[u][v] = true;
  }
};
struct GraphList
{
  int V;
  vector<vector<int>> list;

  GraphList(int n)
  {
    V = n;
    list.resize(V);
  }

  void addEdge(int u, int v)
  {
    list[u].push_back(v);
  }
};

GraphList MatrixToList(GraphMatrix &graph)
{
  GraphList listGraph(graph.V);

  for (int u = 0; u < graph.V; u++)
  {
    for (int v = 0; v < graph.V; v++)
    {
      if (graph.matrix[u][v])
        listGraph.addEdge(u, v);
    }
  }

  return listGraph;
}
GraphMatrix RandomDirectedGraph(int n, double b)
{
  GraphMatrix graph(n);
  int m = (int)b * n * n;

  random_device rand;
  mt19937 gen(rand());
  uniform_int_distribution<> dis(0, n - 1);

  for (int i = 0; i < m; i++)
  {
    int u, v;

    do
    {
      u = dis(gen);
      v = dis(gen);
    } while (u == v || graph.matrix[u][v]);

    graph.addEdge(u, v);
  }

  return graph;
}
GraphMatrix RandomDirectedAcyclicGraphMatrix(int n, double b)
{
  GraphMatrix graph(n);
  int m = static_cast<int>(b * n * (n - 1));

  random_device rand;
  mt19937 gen(rand());
  uniform_int_distribution<> dis(0, n - 1);

  vector<int> indegrees(n, 0);
  vector<int> availableNodes;
  vector<bool> visited(n, false);

  for (int i = 0; i < n; i++)
  {
    availableNodes.push_back(i);
  }

  for (int i = 0; i < m; i++)
  {
    if (availableNodes.empty())
      break;

    int u = availableNodes.back();
    availableNodes.pop_back();

    int v;
    do
    {
      v = dis(gen);
    } while (indegrees[v] == 0 && v != u && !visited[v]);

    if (v != u && !visited[v])
    {
      graph.addEdge(u, v);
      indegrees[v]++;
      visited[u] = true;
      availableNodes.push_back(u);
    }
  }

  return graph;
}

void MatrixDFSVisit(GraphMatrix &graph, int u, vector<int> &colors)
{
  colors[u] = 1;

  for (int v = 0; v < graph.V; v++)
  {
    if (graph.matrix[u][v] && colors[v] == 0)
      MatrixDFSVisit(graph, v, colors);
  }

  colors[u] = 2;
}
void ListDFSVisit(GraphList &graph, int u, vector<int> &colors)
{
  colors[u] = 1;

  for (int i = 0; i < graph.list[u].size(); i++)
  {
    int v = graph.list[u][i];
    if (colors[v] == 0)
      ListDFSVisit(graph, v, colors);
  }

  colors[u] = 2;
}
void ListDFSTopologicalSortVisit(GraphList &graph, int u, vector<int> &colors, vector<int> &topologicalOrder)
{
  colors[u] = 1;

  for (int v : graph.list[u])
  {
    if (colors[v] == 0)
      ListDFSTopologicalSortVisit(graph, v, colors, topologicalOrder);
  }

  colors[u] = 2;
  topologicalOrder.push_back(u);
}
void ListDFSTopologicalSort(GraphList &graph)
{
  vector<int> colors(graph.V, 0);
  vector<int> topologicalOrder;

  for (int u = 0; u < graph.V; u++)
  {
    if (colors[u] == 0)
      ListDFSTopologicalSortVisit(graph, u, colors, topologicalOrder);
  }

  reverse(topologicalOrder.begin(), topologicalOrder.end());
}
void MatrixDFSTopologicalSortVisit(GraphMatrix &graph, int u, vector<int> &colors, vector<int> &topologicalOrder)
{
  colors[u] = 1;

  for (int v = 0; v < graph.V; v++)
  {
    if (graph.matrix[u][v] && colors[v] == 0)
      MatrixDFSTopologicalSortVisit(graph, v, colors, topologicalOrder);
  }

  colors[u] = 2;
  topologicalOrder.push_back(u);
}
void MatrixDFSTopologicalSort(GraphMatrix &graph)
{
  vector<int> colors(graph.V, 0);
  vector<int> topologicalOrder;

  for (int u = 0; u < graph.V; u++)
  {
    if (colors[u] == 0)
      MatrixDFSTopologicalSortVisit(graph, u, colors, topologicalOrder);
  }

  reverse(topologicalOrder.begin(), topologicalOrder.end());
}
void MatrixDFS(GraphMatrix &graph)
{
  vector<int> colors(graph.V, 0);

  for (int u = 0; u < graph.V; u++)
  {
    if (colors[u] == 0)
      MatrixDFSVisit(graph, u, colors);
  }
}
void ListDFS(GraphList &graph)
{
  vector<int> colors(graph.V, 0);

  for (int u = 0; u < graph.V; u++)
  {
    if (colors[u] == 0)
      ListDFSVisit(graph, u, colors);
  }
}
void MatrixBFS(GraphMatrix &graph)
{
  vector<int> colors(graph.V, 0);
  queue<int> Q;

  colors[0] = 1;
  Q.push(0);

  while (!Q.empty())
  {
    int u = Q.front();
    Q.pop();

    for (int v = 0; v < graph.V; v++)
    {
      if (graph.matrix[u][v] && colors[v] == 0)
      {
        colors[v] = 1;
        Q.push(v);
      }
    }

    colors[u] = 2;
  }
}
void ListBFS(GraphList &graph)
{
  vector<int> colors(graph.V, 0);
  queue<int> Q;

  colors[0] = 1;
  Q.push(0);

  while (!Q.empty())
  {
    int u = Q.front();
    Q.pop();

    for (int i = 0; i < graph.list[u].size(); i++)
    {
      int v = graph.list[u][i];
      if (colors[v] == 0)
      {
        colors[v] = 1;
        Q.push(v);
      }
    }

    colors[u] = 2;
  }
}
void MatrixKahnSort(GraphMatrix &graph)
{
  vector<int> inDegree(graph.V, 0);
  queue<int> Q;

  for (int u = 0; u < graph.V; u++)
  {
    for (int v = 0; v < graph.V; v++)
    {
      if (graph.matrix[u][v])
        inDegree[v]++;
    }
  }

  for (int u = 0; u < graph.V; u++)
  {
    if (inDegree[u] == 0)
      Q.push(u);
  }

  vector<int> topologicalOrder;

  while (!Q.empty())
  {
    int u = Q.front();
    Q.pop();

    topologicalOrder.push_back(u);

    for (int v = 0; v < graph.V; v++)
    {
      if (graph.matrix[u][v])
      {
        inDegree[v]--;
        if (inDegree[v] == 0)
          Q.push(v);
      }
    }
  }
}
void ListKahnSort(GraphList &graph)
{
  vector<int> inDegree(graph.V, 0);
  queue<int> Q;

  for (int u = 0; u < graph.V; u++)
  {
    for (int v : graph.list[u])
    {
      inDegree[v]++;
    }
  }

  for (int u = 0; u < graph.V; u++)
  {
    if (inDegree[u] == 0)
      Q.push(u);
  }

  vector<int> topologicalOrder;

  while (!Q.empty())
  {
    int u = Q.front();
    Q.pop();

    topologicalOrder.push_back(u);

    for (int v : graph.list[u])
    {
      inDegree[v]--;
      if (inDegree[v] == 0)
        Q.push(v);
    }
  }
}

template <typename T>
double Measure(void f(T &graph), T &graph)
{
  auto start = chrono::high_resolution_clock::now();
  f(graph);
  auto end = chrono::high_resolution_clock::now();

  chrono::duration<double> duration = end - start;
  return duration.count();
}

int main()
{
  int numVertices[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
  double densities[] = {0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875};

  for (int n : numVertices)
  {
    for (double density : densities)
    {
      GraphMatrix matrixGraph = RandomDirectedGraph(n, density);
      GraphList listGraph = MatrixToList(matrixGraph);
      GraphMatrix acyclicGraphMatrix = RandomDirectedAcyclicGraphMatrix(n, density);
      GraphList acyclicGraphList = MatrixToList(acyclicGraphMatrix);

      printf("Vertices: %d, Density: %.3f\n", n, density);
      printf("DFS Matrix: %f\n", Measure(MatrixDFS, matrixGraph));
      printf("DFS List: %f\n", Measure(ListDFS, listGraph));
      printf("BFS Matrix: %f\n", Measure(MatrixBFS, matrixGraph));
      printf("BFS List: %f\n", Measure(ListBFS, listGraph));
      printf("Kahn Sort Matrix: %f\n", Measure(MatrixKahnSort, acyclicGraphMatrix));
      printf("Kahn Sort List: %f\n", Measure(ListKahnSort, acyclicGraphList));
      printf("DFS Sort Matrix: %f\n", Measure(MatrixDFSTopologicalSort, acyclicGraphMatrix));
      printf("DFS Sort List: %f\n\n", Measure(ListDFSTopologicalSort, acyclicGraphList));
    }
  }

  return 0;
}
