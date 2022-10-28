
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
    this->cnt = 0;
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
    this->moveToStart();

    while (this->curr != nullptr)
    {
      DLink<E> *nextLink = this->curr->nextPtr;
      delete this->curr;
      this->curr = nextLink;
    }

    this->head = nullptr;
    this->tail = nullptr;
    this->cnt = 0;
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
    DLink<E> *newLink = new DLink<E>;
    assert(newLink != nullptr);
    newLink->theElement = it;
    newLink->nextPtr = nullptr;
    this->cnt++;

    if (this->head == nullptr)
    {
      this->head = newLink;
      this->tail = newLink;
      this->curr = newLink;
      return;
    }

    DLink<E> *currLink = this->curr;
    DLink<E> *nextLink = currLink->nextPtr;

    if (nextLink != nullptr)
    {
      nextLink->prevPtr = newLink;
    }

    newLink->prevPtr = currLink;
    newLink->nextPtr = nextLink;
    currLink->nextPtr = newLink;

    this->curr = newLink;

    if (newLink->nextPtr == nullptr)
    {
      this->tail = newLink;
    }
  }

  // Append value at the end of the list
  void append(const E &it)
  {
    DLink<E> *newLink = new DLink<E>;
    assert(newLink != nullptr);
    newLink->theElement = it;
    newLink->prevPtr = this->tail;
    newLink->nextPtr = nullptr;
    this->cnt++;

    if (this->head == nullptr)
    {
      this->head = newLink;
      this->tail = newLink;
      this->curr = newLink;
      return;
    }

    this->tail->nextPtr = newLink;
    this->tail = newLink;
    this->curr = newLink;
  }

  // Remove and return the current element
  E remove()
  {
    DLink<E> *currLink = this->curr;

    if (this->curr == nullptr)
    {
      cout << "Error: You can't delete unknown link." << endl;
      return 0;
    }

    E currElement = currLink->theElement;

    DLink<E> *prevLink = currLink->prevPtr;
    DLink<E> *nextLink = currLink->nextPtr;

    if (prevLink != nullptr)
    {
      prevLink->nextPtr = nextLink;
    }

    if (nextLink != nullptr)
    {
      nextLink->prevPtr = prevLink;
    }

    if (this->head == this->curr)
    {
      this->head = nextLink;
    }

    if (this->tail == this->curr)
    {
      this->tail = nextLink;
    }

    this->curr = nextLink;

    delete currLink;

    this->cnt--;

    return currElement;
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

    DLink<E> *tempLink = this->head;

    while (tempLink != this->curr)
    {
      tempLink = tempLink->nextPtr;
      pos++;
    }

    return pos;
  }

  // Set current to the element at the given position
  void moveToPos(int pos)
  {
    this->moveToStart();

    while (pos > 0)
    {
      this->next();
      pos--;
    }
  }

  void debug()
  {
    DLink<E> *tempLink = this->head;

    while (tempLink != nullptr)
    {
      cout << endl;
      cout << "PREV PTR: " << tempLink->prevPtr << endl;
      cout << "CUR PTR: " << tempLink << endl;
      cout << "CUR VALUE: " << tempLink->theElement << endl;
      cout << "NEXT PTR: " << tempLink->nextPtr << endl;
      cout << endl;
      tempLink = tempLink->nextPtr;
    }
  }

  void display(bool isBackward = false)
  {
    cout << endl;

    if (!isBackward)
    {
      cout << "------------- PRINTING (FORWARD) -------------" << endl;
      this->moveToStart();
    }
    else
    {
      cout << "------------- PRINTING (BACKWARD) -------------" << endl;
      this->moveToEnd();
    }

    for (int i = 0; i < this->length(); ++i)
    {
      cout << this->getValue() << " ";

      if (!isBackward)
      {
        this->next();
      }
      else
      {
        this->prev();
      }
    }

    cout << endl;
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
    theList.append(i);
  }
  while (i < 20)
  {
    theList.insert(i);
    ++i;
  }

  theList.display();

  theList.display(true);

  cout << "\n\n-------------Clearing the list-------------\n";
  theList.clear();
  cout << "Checking if the list is empty: " << theList.length() << " length" << endl;
  cout << "-------------------------------------------\n";

  cout << "\nAdding new elements to the list from [100-109]\n";
  for (i = 0; i < 10; ++i)
  {
    theList.append(i + 100);
  }

  theList.display();

  cout << "\nMoving to the 5th element...\n";
  theList.moveToPos(5);
  cout << "Current Position: " << theList.currPos() << "\n";

  cout << "Removing current element: " << theList.remove() << "\n";
  cout << "Removing current element: " << theList.remove() << "\n";

  theList.display();

  theList.moveToStart();
  cout << "\nRemove the head element: " << theList.remove() << "\n";

  theList.display();

  theList.moveToEnd();
  cout << "\nRemove the tail element: " << theList.remove() << "\n";

  theList.display();

  return 0;
}