#include <iostream>

using namespace std;

struct Node
{
  int data;
  Node *nextNode;
};

int main()
{
  int newCalled = 0, deleteCalled = 0, nodeCount = 3;

  Node *headNode = NULL;
  Node *tempNode = NULL;

  for (int i = 0; i < nodeCount; i++)
  {
    Node *newNode = new Node;
    newCalled++;

    newNode->data = i;
    newNode->nextNode = headNode;

    if (headNode == NULL)
      headNode = newNode;

    if (tempNode != NULL)
      tempNode->nextNode = newNode;

    tempNode = newNode;
  }

  cout << "\nNEW CALLED: " << newCalled << " times." << endl;

  tempNode = headNode;

  for (int i = 1; i <= nodeCount * nodeCount + 1; i++)
  {
    cout << tempNode->data << "(" << tempNode << ")";

    if (i != nodeCount * nodeCount + 1)
      cout << " => ";

    tempNode = tempNode->nextNode;
  }

  cout << "\n\nDELETING.." << endl;

  tempNode = headNode;

  for (int i = 0; i < nodeCount; i++)
  {
    Node *tempNextNode = tempNode->nextNode;
    cout << "Deleting: " << tempNode->data << "(" << tempNode << ") ";
    delete tempNode;
    deleteCalled++;
    tempNode = tempNextNode;
  };

  cout << "\nDELETE CALLED: " << deleteCalled << " times." << endl;

  return 0;
}