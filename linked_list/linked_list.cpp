#include <iostream>

using namespace std;

struct Node
{
  int data;
  Node *nextNode;
};

int main()
{
  int newCalled = 0;
  int deleteCalled = 0;

  int COUNT = 3;

  Node *headNode = new Node;
  newCalled++;

  headNode->data = 1;
  headNode->nextNode = NULL;

  Node *tempNode = headNode;

  for (int i = 2; i <= COUNT; i++)
  {
    Node *newNode = new Node;
    newCalled++;

    newNode->data = i;
    newNode->nextNode = headNode;

    tempNode->nextNode = newNode;
    tempNode = newNode;
  }

  cout << "\nNEW CALLED: " << newCalled << " times." << endl;

  tempNode = headNode;

  for (int i = 1; i <= COUNT * COUNT + 1; i++)
  {
    cout << tempNode->data << "(" << tempNode << ")";
    if (i != COUNT * COUNT + 1)
    {
      cout << " => ";
    }
    tempNode = tempNode->nextNode;
  }

  cout << "\n\nDELETING.." << endl;

  tempNode = headNode;

  for (int i = 0; i < COUNT; i++)
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