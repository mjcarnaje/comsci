
/*
CCC121 Laboratory Exercise No.1 Due : November 20,
2022(Sunday)at 11 : 55PM
*/

#include <iostream>
#include <assert.h>

using namespace std;

/*
The structure to be used for representing a doubly-linked link. This struct
declaration should not be modified in any way.
*/
template <class E>
struct DLink
{
  E theElement;
  DLink<E> *nextPtr;
  DLink<E> *prevPtr;
};

/*
Complete this implementation variant of the doubly-linked list. Use the same
convention as described in the slides. The DLink declaration to be used here is
just a struct and should not be modified in any way. All of the operations of
the original DLink class must be done in the methods of this class. Use
assertions to ensure the correct operation of this ADT. All memory allocations
should be checked with assertions and all discarded memory must be properly
deallocated.
*/
template <class E>
class DList
{
  DLink<E> *head;
  DLink<E> *tail;
  DLink<E> *curr;
  int cnt;


private: 
  void initialize() {
    curr = head = tail = new DLink<E>;
    cnt = 0;
  }

public:
  // Return the size of the list
  int length() const
  {
    return cnt;
  }

  // The constructor with initial list size
  DList(int size)
  {
    this();
  }

  // The default constructor
  DList()
  {
    initialize();
  }

  // The copy constructor
  DList(const DList &source)
  {
    this->head = source->head;
    this->tail = source->tail;
    this->curr = source->curr;
    this->cnt = source->cnt;
  }

  // The class destructor
  ~DList()
  {
    this->clear();
  }

  // Empty the list
  void clear()
  {
    DLink<E> *tempLink = curr->nextPtr;
    curr->nextPtr->nextPtr->prevPtr = curr;
    curr->nextPtr = curr->nextPtr->nextPtr;
    delete tempLink;
    initialize();
  }

  // Set current to first element
  void moveToStart()
  {
    curr = head;
  }

  // Set current element to end of list
  void moveToEnd()
  {
    curr = tail;
  }

  // Advance current to the next element
  void next()
  {
    if (curr != tail) {
      curr = curr->nextPtr;
    }
  }

  // Return the current element
  E &getValue() const
  {
    assert(("No value.", curr->nextPtr != nullptr));
    return curr->nextPtr->theElement;
  }

  // Insert value at current position
  void insert(const E &it)
  {
    DLink<E> *newLink = new DLink<E>;
    newLink->theElement = it;
    newLink->nextPtr = curr->nextPtr;
    newLink->prevPtr = curr->prevPtr;
    curr = newLink;
    if (tail == curr) {
      tail = curr->nextPtr;
    }   
    cnt++;
  }

  // Append value at the end of the list
  void append(const E &it)
  {
    DLink<E> *newLink = new DLink<E>;
    newLink->theElement = it;
    newLink->prevPtr = tail->prevPtr;
    newLink->nextPtr = tail;
    cnt++;
  }

  // Remove and return the current element
  E remove()
  {
    DLink<E> *tempLink = curr->nextPtr;
    curr->nextPtr->nextPtr->prevPtr = curr;
    curr->nextPtr = curr->nextPtr->nextPtr;
    int it = tempLink->theElement;
    delete tempLink;
    return it;
  }

  // Advance current to the previous element
  void prev()
  {
    if (curr == head) return;

    DLink<E> *tempLink = head;

    while (tempLink->nextPtr != curr)
    {
      tempLink = tempLink->nextPtr; 
    }
    
    curr = tempLink; 
  }

  // Return position of the current element
  int currPos() const
  {
    int pos = 0;

    DLink<E> *tempLink = head;

    while (tempLink != curr)
    {
      tempLink = tempLink->nextPtr;
      pos++;
    }

    return pos;
  }

  // Set current to the element at the given position
  void moveToPos(int pos)
  {
    assert(("Postion out of range.", (pos >= 0 && pos <= cnt)));
    curr = head;
    while (pos > 0) {
      curr = curr->nextPtr;
      pos--;
    }
  }

  void debug()
  {
    // for (int i = 0; i < this->length(); i++) {
    //   cout << this->getValue() << endl;
    //   this->next();
    // }

    DLink<E> *tempLink = this->curr->nextPtr;

  
    for (int i = 0; i < this->length(); i++) {
      cout << endl;
      cout << "PREV PTR: " << tempLink->prevPtr << endl;
      cout << "CUR [PTR-VALUE]: " << tempLink << " - " << tempLink->theElement << endl;
      cout << "NEXT PTR: " << tempLink->nextPtr << endl;
      cout << endl;
      tempLink = tempLink->nextPtr;
    }
  }
};

/*
This is the main function for testing the implementation of the DList class.
This function can be freely modified.
*/
int main(void)
{
  int i;
  DList<int> theList;

  cout << "\nAdding [0-19] to the list with the append & insert function\n";
  for (i = 0; i < 10; ++i)
  {
    theList.insert(i);
  }

  theList.debug();
  
  // while (i < 20)
  // {
  //   theList.append(i);
  //   ++i;
  // }

  // theList.debug();

  // theList.display(true);

  // cout << "\n\n-------------Clearing the list-------------\n";
  // theList.clear();
  // cout << "Checking if the list is empty: " << theList.length() << " length" << endl;
  // cout << "-------------------------------------------\n";

  // cout << "\nAdding new elements to the list from [100-109]\n";
  // for (i = 0; i < 10; ++i)
  // {
  //   theList.append(i + 100);
  // }

  // theList.display();

  // cout << "\nMoving to the 5th element...\n";
  // theList.moveToPos(5);
  // cout << "Current Position: " << theList.currPos() << "\n";

  // cout << "Removing current element: " << theList.remove() << "\n";
  // cout << "Removing current element: " << theList.remove() << "\n";

  // theList.display();

  // theList.moveToStart();
  // cout << "\nRemove the head element: " << theList.remove() << "\n";

  // theList.display();

  // theList.moveToEnd();
  // cout << "\nRemove the tail element: " << theList.remove() << "\n";

  // theList.display();

  return 0;
}