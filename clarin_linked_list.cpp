
#include <iostream>
using namespace std;

// test git

struct Node
{
  int value;
  Node *nextNode;
};

int main()
{
  int count;

  cout << "Enter array count: ";
  cin >> count;

  Node *head = new Node;
  head->value = 1;
  head->nextNode = NULL;

  Node *tempNode = head;

  for (int i = 1; i < count; i++)
  {
    tempNode->nextNode = new Node;
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

  delete head;

  return 0;
}
