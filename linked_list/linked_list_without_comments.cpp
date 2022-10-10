#include <iostream>

using namespace std;

int N_TIMES = 3;

struct Node
{
  int data;
  Node *nextNode;
};

int main()
{

  Node *headNode = new Node;

  headNode->data = 1;
  headNode->nextNode = NULL;

  Node *tempNode = headNode;

  for (int i = 2; i <= N_TIMES; i++)
  {
    Node *newNode = new Node;

    newNode->data = i;

    newNode->nextNode = headNode;

    tempNode->nextNode = newNode;

    tempNode = newNode;
  }

  tempNode = headNode;

  for (int i = 1; i <= N_TIMES; i++)
  {
    cout << tempNode->data;

    if (i != N_TIMES)
    {
      cout << " => ";
    }

    tempNode = tempNode->nextNode;
  }

  tempNode = headNode;

  for (int i = 0; i < N_TIMES; i++)
  {

    Node *tempNextNode = tempNode->nextNode;

    delete tempNode;

    tempNode = tempNextNode;
  };

  return 0;
}