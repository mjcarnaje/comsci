/* MEMBERS:
  Carnaje, Michael James
  Lavesores, Fulgent Kvasir
  Requina, John Lenard
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge
{
  int src, dest, weight;
};

class Graph
{
private:
  vector<Edge> edges;
  int vertexCount;

public:
  Graph(int vertexCount)
  {
    this->vertexCount = vertexCount;
  }

  void addEdge(int src, int dest, int weight)
  {
    Edge edge;
    edge.src = src;
    edge.dest = dest;
    edge.weight = weight;
    edges.push_back(edge);
  }

  int find(vector<int> &parent, int i)
  {
    if (parent[i] == -1)
      return i;
    return find(parent, parent[i]);
  }

  void Union(vector<int> &parent, int x, int y)
  {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
  }

  static bool compareEdges(const Edge &a, const Edge &b)
  {
    return a.weight < b.weight;
  }

  void minimumSpanningTree()
  {
    vector<Edge> result;
    int e = 0;
    int i = 0;

    sort(edges.begin(), edges.end(), compareEdges);

    vector<int> parent(vertexCount, -1);

    while (e < vertexCount - 1 && i < edges.size())
    {
      Edge nextEdge = edges[i++];

      int x = find(parent, nextEdge.src);
      int y = find(parent, nextEdge.dest);

      if (x != y)
      {
        result.push_back(nextEdge);
        Union(parent, x, y);
        e++;
      }
    }

    cout << "Minimum Spanning Tree(Prim's Algorithm):" << endl;
    for (int i = 0; i < result.size(); i++)
    {
      cout << result[i].src << " - " << result[i].dest << " : " << result[i].weight << endl;
    }
  }

  void draw()
  {
    vector<vector<int>> matrix = getMatrix();
    cout << "  ";
    for (int i = 0; i < vertexCount; i++)
    {
      cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < vertexCount; i++)
    {
      cout << i << " ";
      for (int j = 0; j < vertexCount; j++)
      {
        cout << matrix[i][j] << " ";
      }
      cout << endl;
    }
  }

  void bfs(int start)
  {
    vector<bool> visited(vertexCount, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
      int current = q.front();
      q.pop();
      cout << current << " ";

      for (int i = 0; i < vertexCount; i++)
      {
        if (edges[current].weight != 0 && !visited[i])
        {
          q.push(i);
          visited[i] = true;
        }
      }
    }
  }

  void dfs(int start)
  {
    vector<bool> visited(vertexCount, false);
    stack<int> s;
    s.push(start);
    visited[start] = true;

    while (!s.empty())
    {
      int current = s.top();
      s.pop();
      cout << current << " ";

      for (int i = 0; i < vertexCount; i++)
      {
        if (edges[current].weight != 0 && !visited[i])
        {
          s.push(i);
          visited[i] = true;
        }
      }
    }
  }

  vector<vector<int>> getMatrix()
  {
    vector<vector<int>> matrix(vertexCount, vector<int>(vertexCount, 0));
    for (int i = 0; i < edges.size(); i++)
    {
      int src = edges[i].src;
      int dest = edges[i].dest;
      int weight = edges[i].weight;
      matrix[src][dest] = weight;
      matrix[dest][src] = weight; // Assuming the graph is undirected
    }
    return matrix;
  }
};

int main()
{
  Graph uG(9);
  uG.addEdge(1, 2, 2);
  uG.addEdge(1, 5, 22);
  uG.addEdge(1, 6, 8);
  uG.addEdge(2, 3, 10);
  uG.addEdge(2, 6, 6);
  uG.addEdge(3, 4, 3);
  uG.addEdge(3, 6, 12);
  uG.addEdge(3, 7, 1);
  uG.addEdge(4, 7, 5);
  uG.addEdge(4, 8, 20);
  uG.addEdge(5, 6, 25);
  uG.addEdge(6, 7, 11);
  uG.addEdge(7, 8, 15);

  cout << "A." << endl;
  uG.draw();

  cout << endl;

  cout << "B. BFS" << endl;
  uG.bfs(1);

  cout << endl;
  cout << endl;

  cout << "C. DFS" << endl;
  uG.dfs(1);

  cout << endl;
  cout << endl;

  cout << "Bonus." << endl;
  uG.minimumSpanningTree();

  return 0;
}
