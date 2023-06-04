#include <iostream>
#include <fstream>
#include <chrono>
#include <time.h>

using namespace std;

struct Node
{
  int value;
  Node *left;
  Node *right;
};

class BinarySearchTree
{
public:
  Node *root = nullptr;
  void insert(Node *&node, int value);
  bool search(Node *node, int value);
  void remove(Node *&node, int value);
  void print(Node *node);
};

void BinarySearchTree::insert(Node *&node, int value)
{
  if (node == nullptr)
  {
    node = new Node;
    node->value = value;
    node->left = nullptr;
    node->right = nullptr;
  }
  else if (value < node->value)
  {
    insert(node->left, value);
  }
  else if (value > node->value)
  {
    insert(node->right, value);
  }
}

bool BinarySearchTree::search(Node *node, int value)
{
  if (node == nullptr)
  {
    return false;
  }
  else if (value == node->value)
  {
    return true;
  }
  else if (value < node->value)
  {
    return search(node->left, value);
  }
  else if (value > node->value)
  {
    return search(node->right, value);
  }
  return false;
}

void BinarySearchTree::remove(Node *&node, int value)
{
  if (node == nullptr)
  {
    return;
  }
  else if (value < node->value)
  {
    remove(node->left, value);
  }
  else if (value > node->value)
  {
    remove(node->right, value);
  }
  else if (value == node->value)
  {
    if (node->left == nullptr && node->right == nullptr)
    {
      delete node;
      node = nullptr;
    }
    else if (node->left == nullptr)
    {
      Node *temp = node;
      node = node->right;
      delete temp;
    }
    else if (node->right == nullptr)
    {
      Node *temp = node;
      node = node->left;
      delete temp;
    }
    else
    {
      Node *temp = node->right;
      while (temp->left != nullptr)
      {
        temp = temp->left;
      }
      node->value = temp->value;
      remove(node->right, temp->value);
    }
  }
}

void BinarySearchTree::print(Node *node)
{
  if (node == nullptr)
  {
    return;
  }
  print(node->left);
  cout << node->value << endl;
  print(node->right);
}

int main()
{
  BinarySearchTree bst;
  ifstream fin("data.txt");
  ofstream fout("bst-stats.txt");

  ifstream finIterations("num-of-iterations.txt");

  int *N = new int[100];
  int numIterations = 0;

  while (!finIterations.eof())
  {
    finIterations >> N[numIterations];
    numIterations++;
  }

  srand(time(0));

  for (int k = 0; k < numIterations; k++)
  {
    int *arr = new int[N[k]];

    for (int i = 0; i < N[k]; i++)
    {
      fin >> arr[i];
    }

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < N[k]; i++)
    {
      bst.insert(bst.root, arr[i]);
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    fout << "Inserting " << N[k] << " items into the BST took " << duration.count() << " milliseconds" << endl;

    int randomIndexToSearch = rand() % N[k];

    start = chrono::high_resolution_clock::now();

    for (int i = 0; i < N[k]; i++)
    {
      bst.search(bst.root, arr[randomIndexToSearch]);
    }

    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    fout << "Searching " << N[k] << " items in the BST took " << duration.count() << " milliseconds" << endl;

    int randomIndexToRemove = rand() % N[k];

    start = chrono::high_resolution_clock::now();

    for (int i = 0; i < N[k]; i++)
    {
      bst.remove(bst.root, arr[randomIndexToRemove]);
    }

    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    fout << "Removing " << N[k] << " items from the BST took " << duration.count() << " milliseconds" << endl;
    fout << endl;

    delete[] arr;
  }

  fin.close();
  fout.close();
  return 0;
}
