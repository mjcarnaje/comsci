
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
    this->head = nullptr;
    this->tail = nullptr;
    this->curr = nullptr;
    cnt = 0;
  }

  // The copy constructor
  DList(const DList &source)
  {
    this->head = source->head;
    this->tail = source->tail;
    this->curr = source->curr;
    cnt = source->cnt;
  }

  // The class destructor
  ~DList()
  {
    this->clear();
  }

  // Empty the list
  void clear()
  {
    DLink<E> *tempDLink = this->head;

    while (tempDLink->nextPtr != nullptr)
    {
      DLink<E> *tempNextPtrDLink = tempDLink->nextPtr;
      delete tempDLink;
      tempDLink = tempNextPtrDLink;
    }

    delete tempDLink;

    this->head = nullptr;
    this->tail = nullptr;
    this->curr = nullptr;
    cnt = 0;
  }

  // Set current to first element
  void moveToStart()
  {
    this->curr = this->head;
  }

  // Set current element to end of list
  void moveToEnd()
  {
    this->curr = this->tail;
  }

  // Advance current to the next element
  void next()
  {
    this->curr = this->curr->nextPtr;
  }

  // Return the current element
  E &getValue() const
  {
    return this->curr->theElement;
  }

  // Insert value at current position
  void insert(const E &it)
  {
    DLink<E> *newDLink = new DLink<E>;
    newDLink->theElement = it;
    newDLink->nextPtr = nullptr;

    DLink<E> *tempDLink = this->head;

    while (tempDLink != this->curr)
    {
      tempDLink = tempDLink->nextPtr;
    }

    newDLink->prevPtr = tempDLink;
    newDLink->nextPtr = tempDLink->nextPtr;
    tempDLink->nextPtr = newDLink;
    this->curr = newDLink;
    if (newDLink->nextPtr == nullptr)
    {
      this->tail = newDLink;
    }
  }

  // Append value at the end of the list
  void append(const E &it)
  {
    DLink<E> *newDLink = new DLink<E>;
    cnt++;
    newDLink->theElement = it;
    newDLink->prevPtr = this->tail;
    newDLink->nextPtr = nullptr;

    if (this->head == nullptr)
    {
      this->head = newDLink;
      this->tail = newDLink;
      return;
    }

    DLink<E> *tempDLink = this->head;

    while (tempDLink->nextPtr != nullptr)
    {
      tempDLink = tempDLink->nextPtr;
    }
    tempDLink->nextPtr = newDLink;
    this->tail = newDLink;
    this->curr = newDLink;
  }

  // Remove and return the current element
  E remove()
  {
    DLink<E> *tempDLink = this->head;
    while (tempDLink != this->curr)
    {
      tempDLink = tempDLink->nextPtr;
    }

    E currentData = tempDLink->theElement;
    DLink<E> *prevDLink = tempDLink->prevPtr;
    DLink<E> *nextDLink = tempDLink->nextPtr;

    prevDLink->nextPtr = nextDLink;
    nextDLink->prevPtr = prevDLink;
    this->curr = nextDLink;
    delete tempDLink;
    cnt--;
    return currentData;
  }

  // Advance current to the previous element
  void prev()
  {
    this->curr = this->curr->prevPtr;
  }

  // Return position of the current element
  int currPos() const
  {
    int pos = 0;

    DLink<E> *tempDLink = this->head;

    while (tempDLink != this->curr)
    {
      tempDLink = tempDLink->nextPtr;
      pos++;
    }

    return pos;
  }

  // Set current to the element at the given position
  void moveToPos(int pos)
  {
    int curPos = 0;
    DLink<E> *tempDLink = this->head;
    while (curPos != pos)
    {
      tempDLink = tempDLink->nextPtr;
      curPos++;
    }
    this->curr = tempDLink;
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

  // populate the list
  for (i = 0; i < 10; ++i)
  {
    theList.append(i);
  }
  while (i < 20)
  {
    theList.insert(i);

    ++i;
  }

  // display the contents of the list
  theList.moveToStart();
  for (i = 0; i < theList.length(); ++i)
  {
    cout << theList.getValue() << " ";

    theList.next();
  }
  cout << "\n";

  // display the contents of the list in reverse order
  theList.moveToEnd();
  for (i = 0; i < theList.length(); ++i)
  {
    theList.prev();

    cout << theList.getValue() << " ";
  }
  cout << "\n";

  // replace the contents of the list
  theList.clear();
  for (i = 0; i < 10; ++i)
  {
    theList.append(i + 100);
  }

  // display the contents of the list
  theList.moveToStart();
  for (i = 0; i < theList.length(); ++i)
  {
    cout << theList.getValue() << " ";

    theList.next();
  }
  cout << "\n";

  // remove two elements at the specified position
  theList.moveToPos(5);
  cout << theList.currPos() << "\n";

  theList.remove();
  theList.remove();

  // display the contents of the list
  theList.moveToStart();
  for (i = 0; i < theList.length(); ++i)
  {
    cout << theList.getValue() << " ";

    theList.next();
  }
  cout << "\n";

  return 0;
}