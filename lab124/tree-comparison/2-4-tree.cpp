#include <iostream>
#include <fstream>
#include <chrono>
#include <time.h>

using namespace std;

const int MIN_KEYS = 1;
const int MAX_KEYS = 3;

struct Node
{
  int keys[MAX_KEYS];
  Node *child[MAX_KEYS + 1];
  int keyCount;
  bool isLeaf;

  Node()
  {
    for (int i = 0; i <= MAX_KEYS; i++)
    {
      child[i] = nullptr;
    }
    keyCount = 0;
    isLeaf = true;
  }
};

class TwoFourTree
{
public:
  Node *root;

  TwoFourTree()
  {
    root = nullptr;
  }

  void insert(int value);
  bool search(int value);
  void remove(int value);
  void print();

private:
  void insertNonFull(Node *node, int value);
  void splitChild(Node *parent, int index);
  bool searchRecursive(Node *node, int value);
  void removeInternal(Node *node, int value);
  void removeFromLeaf(Node *node, int index);
  void removeFromNonLeaf(Node *node, int index);
  int getPredecessor(Node *node, int index);
  int getSuccessor(Node *node, int index);
  void fillChild(Node *node, int index);
  void borrowFromPrev(Node *node, int index);
  void borrowFromNext(Node *node, int index);
  void merge(Node *node, int index);
  void printRecursive(Node *node);
};

void TwoFourTree::insert(int value)
{
  if (root == nullptr)
  {
    root = new Node;
    root->keys[0] = value;
    root->keyCount = 1;
  }
  else
  {
    if (root->keyCount == MAX_KEYS)
    {
      Node *newRoot = new Node;
      newRoot->child[0] = root;
      splitChild(newRoot, 0);
      root = newRoot;
    }
    insertNonFull(root, value);
  }
}

void TwoFourTree::insertNonFull(Node *node, int value)
{
  int i = node->keyCount - 1;

  if (node->isLeaf)
  {
    while (i >= 0 && value < node->keys[i])
    {
      node->keys[i + 1] = node->keys[i];
      i--;
    }
    node->keys[i + 1] = value;
    node->keyCount++;
  }
  else
  {
    while (i >= 0 && value < node->keys[i])
    {
      i--;
    }
    i++;

    if (node->child[i]->keyCount == MAX_KEYS)
    {
      splitChild(node, i);
      if (value > node->keys[i])
      {
        i++;
      }
    }
    insertNonFull(node->child[i], value);
  }
}

void TwoFourTree::splitChild(Node *parent, int index)
{
  Node *nodeToSplit = parent->child[index];
  Node *newNode = new Node;
  newNode->isLeaf = nodeToSplit->isLeaf;
  newNode->keyCount = MIN_KEYS;

  for (int i = 0; i < MIN_KEYS; i++)
  {
    newNode->keys[i] = nodeToSplit->keys[i + MIN_KEYS];
  }

  if (!nodeToSplit->isLeaf)
  {
    for (int i = 0; i <= MIN_KEYS; i++)
    {
      newNode->child[i] = nodeToSplit->child[i + MIN_KEYS];
    }
  }

  nodeToSplit->keyCount = MIN_KEYS;

  for (int i = parent->keyCount; i > index; i--)
  {
    parent->child[i + 1] = parent->child[i];
  }

  parent->child[index + 1] = newNode;

  for (int i = parent->keyCount - 1; i >= index; i--)
  {
    parent->keys[i + 1] = parent->keys[i];
  }

  parent->keys[index] = nodeToSplit->keys[MIN_KEYS];
  parent->keyCount++;
}

bool TwoFourTree::search(int value)
{
  return searchRecursive(root, value);
}

bool TwoFourTree::searchRecursive(Node *node, int value)
{
  int i = 0;
  while (i < node->keyCount && value > node->keys[i])
  {
    i++;
  }

  if (i < node->keyCount && value == node->keys[i])
  {
    return true;
  }
  else if (node->isLeaf)
  {
    return false;
  }
  else
  {
    return searchRecursive(node->child[i], value);
  }
}

void TwoFourTree::remove(int value)
{
  if (root == nullptr)
  {
    return;
  }

  removeInternal(root, value);

  if (root->keyCount == 0)
  {
    Node *oldRoot = root;
    if (root->isLeaf)
    {
      root = nullptr;
    }
    else
    {
      root = root->child[0];
    }
    delete oldRoot;
  }
}

void TwoFourTree::removeInternal(Node *node, int value)
{
  int index = 0;
  while (index < node->keyCount && value > node->keys[index])
  {
    index++;
  }

  if (index < node->keyCount && value == node->keys[index])
  {
    if (node->isLeaf)
    {
      removeFromLeaf(node, index);
    }
    else
    {
      removeFromNonLeaf(node, index);
    }
  }
  else
  {
    if (node->isLeaf)
    {
      return;
    }
    bool flag = (index == node->keyCount);

    if (node->child[index]->keyCount < MIN_KEYS)
    {
      fillChild(node, index);
    }

    if (flag && index > node->keyCount)
    {
      removeInternal(node->child[index - 1], value);
    }
    else
    {
      removeInternal(node->child[index], value);
    }
  }
}

void TwoFourTree::removeFromLeaf(Node *node, int index)
{
  for (int i = index + 1; i < node->keyCount; i++)
  {
    node->keys[i - 1] = node->keys[i];
  }
  node->keyCount--;
}

void TwoFourTree::removeFromNonLeaf(Node *node, int index)
{
  int value = node->keys[index];

  if (node->child[index]->keyCount >= MIN_KEYS)
  {
    int predecessor = getPredecessor(node, index);
    node->keys[index] = predecessor;
    removeInternal(node->child[index], predecessor);
  }
  else if (node->child[index + 1]->keyCount >= MIN_KEYS)
  {
    int successor = getSuccessor(node, index);
    node->keys[index] = successor;
    removeInternal(node->child[index + 1], successor);
  }
  else
  {
    merge(node, index);
    removeInternal(node->child[index], value);
  }
}

int TwoFourTree::getPredecessor(Node *node, int index)
{
  Node *current = node->child[index];
  while (!current->isLeaf)
  {
    current = current->child[current->keyCount];
  }
  return current->keys[current->keyCount - 1];
}

int TwoFourTree::getSuccessor(Node *node, int index)
{
  Node *current = node->child[index + 1];
  while (!current->isLeaf)
  {
    current = current->child[0];
  }
  return current->keys[0];
}

void TwoFourTree::fillChild(Node *node, int index)
{
  if (index != 0 && node->child[index - 1]->keyCount >= MIN_KEYS)
  {
    borrowFromPrev(node, index);
  }
  else if (index != node->keyCount && node->child[index + 1]->keyCount >= MIN_KEYS)
  {
    borrowFromNext(node, index);
  }
  else
  {
    if (index != node->keyCount)
    {
      merge(node, index);
    }
    else
    {
      merge(node, index - 1);
    }
  }
}

void TwoFourTree::borrowFromPrev(Node *node, int index)
{
  Node *child = node->child[index];
  Node *sibling = node->child[index - 1];

  for (int i = child->keyCount - 1; i >= 0; i--)
  {
    child->keys[i + 1] = child->keys[i];
  }

  if (!child->isLeaf)
  {
    for (int i = child->keyCount; i >= 0; i--)
    {
      child->child[i + 1] = child->child[i];
    }
  }

  child->keys[0] = node->keys[index - 1];

  if (!child->isLeaf)
  {
    child->child[0] = sibling->child[sibling->keyCount];
  }

  node->keys[index - 1] = sibling->keys[sibling->keyCount - 1];

  child->keyCount++;
  sibling->keyCount--;
}

void TwoFourTree::borrowFromNext(Node *node, int index)
{
  Node *child = node->child[index];
  Node *sibling = node->child[index + 1];

  child->keys[child->keyCount] = node->keys[index];

  if (!child->isLeaf)
  {
    child->child[child->keyCount + 1] = sibling->child[0];
  }

  node->keys[index] = sibling->keys[0];

  for (int i = 1; i < sibling->keyCount; i++)
  {
    sibling->keys[i - 1] = sibling->keys[i];
  }

  if (!sibling->isLeaf)
  {
    for (int i = 1; i <= sibling->keyCount; i++)
    {
      sibling->child[i - 1] = sibling->child[i];
    }
  }

  child->keyCount++;
  sibling->keyCount--;
}

void TwoFourTree::merge(Node *node, int index)
{
  Node *child = node->child[index];
  Node *sibling = node->child[index + 1];

  child->keys[MIN_KEYS] = node->keys[index];

  for (int i = 0; i < sibling->keyCount; i++)
  {
    child->keys[i + MIN_KEYS + 1] = sibling->keys[i];
  }

  if (!child->isLeaf)
  {
    for (int i = 0; i <= sibling->keyCount; i++)
    {
      child->child[i + MIN_KEYS + 1] = sibling->child[i];
    }
  }

  for (int i = index + 1; i < node->keyCount; i++)
  {
    node->keys[i - 1] = node->keys[i];
  }

  for (int i = index + 2; i <= node->keyCount; i++)
  {
    node->child[i - 1] = node->child[i];
  }

  child->keyCount += sibling->keyCount + 1;
  node->keyCount--;

  delete sibling;
}

void TwoFourTree::print()
{
  printRecursive(root);
  cout << endl;
}

void TwoFourTree::printRecursive(Node *node)
{
  if (node != nullptr)
  {
    for (int i = 0; i < node->keyCount; i++)
    {
      cout << node->keys[i] << " ";
    }

    if (!node->isLeaf)
    {
      for (int i = 0; i <= node->keyCount; i++)
      {
        printRecursive(node->child[i]);
      }
    }
  }
}

int main()
{
  TwoFourTree twoFour;
  ifstream fin("data.txt");
  ofstream fout("twoFour-tree-stats.txt");

  ifstream finIterations("num-of-iterations.txt");

  int *N = new int[100];
  int numIterations = 0;

  while (!finIterations.eof())
  {
    finIterations >> N[numIterations];
    numIterations++;
  }

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
      twoFour.insert(arr[i]);
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    fout << "Inserting " << N[k] << " items into the 2-4 tree took " << duration << " milliseconds" << endl;

    int randomIndexToSearch = rand() % N[k];

    start = chrono::high_resolution_clock::now();

    for (int i = 0; i < N[k]; i++)
    {
      twoFour.search(arr[randomIndexToSearch]);
    }

    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    fout << "Searching for " << N[k] << " items in the 2-4 tree took " << duration << " milliseconds" << endl;

    int randomIndexToRemove = rand() % N[k];

    start = chrono::high_resolution_clock::now();

    for (int i = 0; i < N[k]; i++)
    {
      twoFour.remove(arr[randomIndexToRemove]);
    }

    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    fout << "Removing " << N[k] << " items from the 2-4 tree took " << duration << " milliseconds" << endl;
    fout << endl;

    delete[] arr;
  }

  fin.close();
  fout.close();

  return 0;
}
