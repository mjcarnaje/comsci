/* MEMBERS:
  Carnaje, Michael James
  Lavesores, Fulgent Kvasir
  Requina, John Lenard
*/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <string>
#include <stack>
using namespace std;

void dijkstra(const vector<vector<int>> &graph, int src)
{
  int V = graph.size();
  vector<int> dist(V, numeric_limits<int>::max());
  dist[src] = 0;
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  pq.push({0, src});

  while (!pq.empty())
  {
    int u = pq.top().second;
    pq.pop();

    for (int v = 0; v < V; v++)
    {
      if (graph[u][v] != 0 && dist[u] != numeric_limits<int>::max() && dist[u] + graph[u][v] < dist[v])
      {
        dist[v] = dist[u] + graph[u][v];
        pq.push({dist[v], v});
      }
    }
  }

  for (int i = 0; i < V; i++)
  {
    cout << "Vertex 0 -> Vertex " << i << " = " << dist[i] << endl;
  }
}

bool isDirectedGraphConnected(const vector<vector<bool>> &graph)
{
  int V = graph.size();
  vector<bool> visited(V, false);
  queue<int> q;
  q.push(0);
  visited[0] = true;

  while (!q.empty())
  {
    int u = q.front();
    q.pop();

    for (int v = 0; v < V; v++)
    {
      if (graph[u][v] && !visited[v])
      {
        visited[v] = true;
        q.push(v);
      }
    }
  }

  for (int i = 0; i < V; i++)
  {
    if (!visited[i])
    {
      return false;
    }
  }

  return true;
}

string bfs(const vector<vector<int>> &graph, int src)
{
  int V = graph.size();
  vector<bool> visited(V, false);
  queue<int> q;
  q.push(src);
  visited[src] = true;
  string result = "";

  while (!q.empty())
  {
    int u = q.front();
    q.pop();
    result += to_string(u) + " ";

    for (int v = 0; v < V; v++)
    {
      if (graph[u][v] != 0 && !visited[v])
      {
        visited[v] = true;
        q.push(v);
      }
    }
  }

  return result;
}

string dfs(const vector<vector<int>> &graph, int src)
{
  int V = graph.size();
  vector<bool> visited(V, false);
  stack<int> s;
  s.push(src);
  visited[src] = true;
  string result = "";

  while (!s.empty())
  {
    int u = s.top();
    s.pop();
    result += to_string(u) + " ";

    for (int v = 0; v < V; v++)
    {
      if (graph[u][v] != 0 && !visited[v])
      {
        visited[v] = true;
        s.push(v);
      }
    }
  }

  return result;
}

int getNumberOfEdges(const vector<vector<int>> &graph)
{
  int V = graph.size();
  int edges = 0;

  for (int i = 0; i < V; i++)
  {
    for (int j = 0; j < V; j++)
    {
      if (graph[i][j] != 0)
      {
        edges++;
      }
    }
  }

  return edges;
}

int main()
{

  vector<vector<int>> graph = {
      {0, 2, 0, 20, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
      {3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 8, 0, 0, 6, 4, 0, 0, 0},
      {0, 0, 7, 0, 0, 0, 0, 3, 0, 0},
      {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
      {0, 0, 0, 0, 0, 0, 2, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}};

  int V = graph.size();

  vector<vector<bool>> boolGraph(V, vector<bool>(V, false));

  for (int i = 0; i < graph.size(); i++)
  {
    for (int j = 0; j < graph[i].size(); j++)
    {
      if (graph[i][j] > 0)
      {
        boolGraph[i][j] = true;
      }
    }
  }

  cout << "A. ";
  cout << "The list of the shortest path from vertex 0 to each vertex is: " << endl;
  dijkstra(graph, 0);

  cout << "============================================" << endl;

  cout << "B. ";
  cout << "The directed graph is: ";
  if (isDirectedGraphConnected(boolGraph))
    cout << "connected";
  else
    cout << "not connected";
  cout << endl;

  cout << "============================================" << endl;

  cout << "C. ";
  cout << "The breadth-first spanning tree starting from vertex 0 is: " << endl;
  cout << bfs(graph, 0) << endl;

  cout << "============================================" << endl;

  cout << "D. ";
  cout << "The breadth-first spanning tree starting from vertex 0 is: " << endl;
  cout << dfs(graph, 0) << endl;

  cout << "============================================" << endl;

  cout << "Bonus. ";
  cout << "The number of edges in the graph is: ";
  cout << getNumberOfEdges(graph) << endl;

  return 0;
}
