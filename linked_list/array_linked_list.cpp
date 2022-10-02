#include <iostream>

using namespace std;

struct Node
{
  int data;
  struct Node *next;
};

int main()
{
  int size = 20;

  Node **headNode;

  headNode = new Node *[size];

  // initialize nodes to NULL
  for (int i = 0; i < size; ++i)
  {
    *(headNode + 1) = NULL;
  }

  for (int i = 0; i < size; ++i)
  {
    // track the previous node
    Node *prevNode = NULL;

    int nodeSize = size;
    int data = 0;

    while (nodeSize--)
    {
      data++;
      // initialize current node
      Node *currentNode = new Node;
      // set data of current node
      currentNode->data = data;
      // set next node to NULL
      currentNode->next = NULL;

      // if current head node is equal to NULL (OR FIRST NODE)
      if (*(headNode + 1) == NULL)
      {
        // set current head node to current node
        *(headNode + 1) = currentNode;
      }
      else
      {
        // if current head node is not equal to NULL (OR AFTER FIRST NODE)
        // then set next node of previous node to the current node
        prevNode->next = currentNode;
      }
      // set previous node to current node for tracking
      prevNode = currentNode;
    }

    for (int i = 0; i < size; ++i)
    {
      Node *tempNode = *(headNode + 1);
      cout << i + 1 << ": ";
      while (tempNode != NULL)
      {
        cout << tempNode->data << " ";
        tempNode = tempNode->next;
      }
      cout << endl;
    }
  }
}