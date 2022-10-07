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
  // create the head node, we separate this from the loop because we need to keep track of the head node to print and delete it later
  Node *headNode = new Node;

  // set the data of the head node
  headNode->data = 1;
  headNode->nextNode = NULL;

  // create a temporary node, we use this to keep track of the previous node we created and set it's nextNode to the new node we create in the loop
  Node *tempNode = headNode;

  // start the loop at 2 because we already created the head node
  for (int i = 2; i <= N_TIMES; i++)
  {
    Node *newNode = new Node;

    newNode->data = i;
    // we set the nextNode of the new node to the head node because we want to create a circular linked list
    // NOTE: only the last node will have it's nextNode set to the head node, the rest will have it's nextNode set to the next node in the list
    newNode->nextNode = headNode;

    // set the nextNode of the previous node(tempNode) to the new node
    tempNode->nextNode = newNode;

    // set the tempNode to the new node so we can use it in the next iteration
    tempNode = newNode;
  }

  // set the tempNode to the head node so we can start printing from the head node
  tempNode = headNode;

  for (int i = 1; i <= N_TIMES; i++)
  {
    cout << tempNode->data;

    // if we are not at the last node, print the arrow (for visual purposes)
    if (i != N_TIMES)
    {
      cout << " => ";
    }

    tempNode = tempNode->nextNode;
  }

  // set the tempNode to the head node so we can start deleting from the head node
  tempNode = headNode;

  for (int i = 0; i < N_TIMES; i++)
  {
    // create a temporary node to store the nextNode of the current node
    // NOTE: we need to do this because we are going to delete the current node and we need to store the nextNode before we delete it
    Node *tempNextNode = tempNode->nextNode;
    // delete the current node
    delete tempNode;
    // set the tempNode to the nextNode of the current node (the one we stored in tempNextNode)
    tempNode = tempNextNode;
  };

  return 0;
}