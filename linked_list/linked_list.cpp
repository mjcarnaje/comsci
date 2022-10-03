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

  assert(headNode != NULL);

  headNode->data = 1;
  headNode->nextNode = NULL;

  Node *tempNode = headNode;

  for (int i = 2; i <= 20; i++)
  {
    Node *newNode = new Node;

    assert(newNode != NULL);

    newNode->data = i;
    newNode->nextNode = NULL;

    tempNode->nextNode = newNode;
    tempNode = newNode;
  }

  // tempNode->nextNode = headNode;
  tempNode = headNode;

  while (tempNode != NULL)
  {
    cout << tempNode->data << " ";

    tempNode = tempNode->nextNode;
  }

  tempNode = headNode;

  while (tempNode != NULL)
  {
    Node *deleteNode = tempNode;

    tempNode = tempNode->nextNode;

    delete deleteNode;
  }

  return 0;
}
