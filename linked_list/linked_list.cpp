#include <iostream>
#include <assert.h>

using namespace std;

struct Node
{
  int data;
  struct Node *nextNode;
};

int main()
{
  struct Node *headNode = new Node;

  int COUNT = 3;

  assert(headNode != NULL);

  headNode->data = 1;
  headNode->nextNode = NULL;

  Node *tempNode = headNode;

  for (int i = 2; i <= COUNT; i++)
  {
    Node *newNode = new Node;

    assert(newNode != NULL);

    newNode->data = i;
    newNode->nextNode = headNode;

    tempNode->nextNode = newNode;
    tempNode = newNode;
  }

  tempNode = headNode;

  for (int i = 1; i <= COUNT * COUNT + 1; i++)
  {
    cout << tempNode->data << " ";
    tempNode = tempNode->nextNode;
  }

  cout << endl;

  tempNode = headNode;

  for (int i = 1; i <= COUNT; i++)
  {
    Node *tempNode2 = tempNode->nextNode;
    delete tempNode;
    tempNode = tempNode2;
  }

  cout << "DONE!" << endl;

  return 0;
}
