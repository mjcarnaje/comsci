  #include <iostream>

  using namespace std;

  struct Node
  { 
    int data;
    Node *nextNode;
  };

  void printNodes(Node *headNode)
  {
    cout << endl;
    while (headNode != NULL)
    {
      cout << headNode->data;
      if (headNode->nextNode != NULL)
      {
        cout << " => ";
      }
      headNode = headNode->nextNode;
    }
  }

  void insertAtIndex(Node *&headNode, int index, int newData) 
  {
    Node *newNode = newNode;
    newNode->data = newData;
    newNode->nextNode = NULL;

    if(index == headNode->data)
    {
      newNode->nextNode = headNode->nextNode;
      headNode->nextNode = newNode;
      return;
    }
    
    Node *tempNode = headNode;

    while (tempNode->data != index)
    {
      tempNode = tempNode->nextNode;
      if (tempNode == NULL) return;
    }

    newNode->nextNode = tempNode->nextNode;
    tempNode->nextNode = newNode;
  }

  void appendNode(Node *&headNode, int value)
  {
    Node *newNode = new Node;
    newNode->data = value;
    newNode->nextNode = NULL;

    if(headNode == NULL)
    { 
      headNode = newNode;
      return;
    }

    Node *tempNode = headNode;

    while(tempNode->nextNode != NULL)
    {
      tempNode = tempNode->nextNode;
    }
    tempNode->nextNode = newNode;
  }

  void setUpNodes(Node *&headNode, int count) {
    int index = 1;
    while (index <= count) {
      appendNode(headNode, index);
      index++;  
    }
  }

  int main()
  {

    Node *headNode = NULL;
    
    setUpNodes(headNode, 10);  

    printNodes(headNode);
    
    // printNodes(headNode);

    // insertAtIndex(headNode, 1, 20);
    
    // printNodes(headNode);
    
    return 0;
    
  }
    