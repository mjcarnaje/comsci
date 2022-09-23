#include <iostream>
#include <assert.h>

using namespace std;

struct Node
{
  int value;
  Node *nextNode;
};

void printNodes(Node *head)
{
  while (head != NULL)
  {
    cout << head->value << " ";
    head = head->nextNode;
  }
}

int main()
{
  int count;

  cout << "Enter array count: ";
  cin >> count;

  Node *head = new Node;
  assert(head != NULL);
  head->value = 1;
  head->nextNode = NULL;

  Node *tempNode = head;

  for (int i = 1; i < count; i++)
  {
    tempNode->nextNode = new Node;
    assert(tempNode->nextNode != NULL);
    tempNode->nextNode->value = i + 1;
    tempNode->nextNode->nextNode = NULL;
    tempNode = tempNode->nextNode;
  }

  tempNode->nextNode = head;
  tempNode = head;

  for (int i = 1; i <= count * count; i++)
  {
    cout << tempNode->value << " ";
    if (i % count == 0)
    {
      cout << endl;
    }
    tempNode = tempNode->nextNode;
  }

  cout << "DONE!!";

  return 0;
}
