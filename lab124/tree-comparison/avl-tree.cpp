#include <iostream>
#include <fstream>
#include <chrono>
#include <time.h>

using namespace std;

struct Node
{
  int value;
  int height;
  Node *left;
  Node *right;
};

class AVLTree
{
public:
  Node *root = nullptr;
  void insert(Node *&node, int value);
  bool search(Node *node, int value);
  void remove(Node *&node, int value);
  void print(Node *node);

private:
  int getHeight(Node *node);
  int getBalance(Node *node);
  Node *rotateLeft(Node *node);
  Node *rotateRight(Node *node);
  Node *insertHelper(Node *node, int value);
  Node *findMin(Node *node);
  Node *removeHelper(Node *node, int value);
};

int AVLTree::getHeight(Node *node)
{
  if (node == nullptr)
    return 0;
  return node->height;
}

int AVLTree::getBalance(Node *node)
{
  if (node == nullptr)
    return 0;
  return getHeight(node->left) - getHeight(node->right);
}

Node *AVLTree::rotateLeft(Node *node)
{
  Node *newRoot = node->right;
  Node *subTree = newRoot->left;

  newRoot->left = node;
  node->right = subTree;

  node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
  newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

  return newRoot;
}

Node *AVLTree::rotateRight(Node *node)
{
  Node *newRoot = node->left;
  Node *subTree = newRoot->right;

  newRoot->right = node;
  node->left = subTree;

  node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
  newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

  return newRoot;
}

Node *AVLTree::insertHelper(Node *node, int value)
{
  if (node == nullptr)
  {
    node = new Node;
    node->value = value;
    node->height = 1;
    node->left = nullptr;
    node->right = nullptr;
    return node;
  }

  if (value < node->value)
  {
    node->left = insertHelper(node->left, value);
  }
  else if (value > node->value)
  {
    node->right = insertHelper(node->right, value);
  }
  else
  {
    // Duplicate values not allowed in AVL tree
    return node;
  }

  node->height = 1 + max(getHeight(node->left), getHeight(node->right));

  int balance = getBalance(node);

  // Left-Left case
  if (balance > 1 && value < node->left->value)
  {
    return rotateRight(node);
  }

  // Right-Right case
  if (balance < -1 && value > node->right->value)
  {
    return rotateLeft(node);
  }

  // Left-Right case
  if (balance > 1 && value > node->left->value)
  {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }

  // Right-Left case
  if (balance < -1 && value < node->right->value)
  {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  return node;
}

Node *AVLTree::findMin(Node *node)
{
  while (node->left != nullptr)
  {
    node = node->left;
  }
  return node;
}

Node *AVLTree::removeHelper(Node *node, int value)
{
  if (node == nullptr)
  {
    return nullptr;
  }

  if (value < node->value)
  {
    node->left = removeHelper(node->left, value);
  }
  else if (value > node->value)
  {
    node->right = removeHelper(node->right, value);
  }
  else
  {
    if (node->left == nullptr && node->right == nullptr)
    {
      delete node;
      return nullptr;
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
      Node *temp = findMin(node->right);
      node->value = temp->value;
      node->right = removeHelper(node->right, temp->value);
    }
  }

  if (node == nullptr)
  {
    return nullptr;
  }

  node->height = 1 + max(getHeight(node->left), getHeight(node->right));

  int balance = getBalance(node);

  // Left-Left case
  if (balance > 1 && getBalance(node->left) >= 0)
  {
    return rotateRight(node);
  }

  // Left-Right case
  if (balance > 1 && getBalance(node->left) < 0)
  {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }

  // Right-Right case
  if (balance < -1 && getBalance(node->right) <= 0)
  {
    return rotateLeft(node);
  }

  // Right-Left case
  if (balance < -1 && getBalance(node->right) > 0)
  {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  return node;
}

void AVLTree::insert(Node *&node, int value)
{
  root = insertHelper(node, value);
}

bool AVLTree::search(Node *node, int value)
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

void AVLTree::remove(Node *&node, int value)
{
  root = removeHelper(node, value);
}

void AVLTree::print(Node *node)
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
  AVLTree avl;
  ifstream fin("data.txt");
  ofstream fout("avl-tree-stats.txt");

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
      avl.insert(avl.root, arr[i]);
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    fout << "Inserting " << N[k] << " items into the AVL tree took " << duration.count() << " milliseconds" << endl;

    int randomIndexToSearch = rand() % N[k];

    start = chrono::high_resolution_clock::now();

    for (int i = 0; i < N[k]; i++)
    {
      avl.search(avl.root, arr[randomIndexToSearch]);
    }

    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    fout << "Searching " << N[k] << " items in the AVL tree took " << duration.count() << " milliseconds" << endl;

    int randomIndexToRemove = rand() % N[k];

    start = chrono::high_resolution_clock::now();

    for (int i = 0; i < N[k]; i++)
    {
      avl.remove(avl.root, arr[randomIndexToRemove]);
    }

    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    fout << "Removing " << N[k] << " items from the AVL tree took " << duration.count() << " milliseconds" << endl;
    fout << endl;

    delete[] arr;
  }

  fin.close();
  fout.close();

  return 0;
}
