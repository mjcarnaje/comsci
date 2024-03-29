/*
    CCC121 Laboratory Exercise No .1 Due : November 20, 2022(Sunday)at 11 : 55PM
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
    head = new DLink<E>;
    assert(head != nullptr);
    tail = new DLink<E>;
    assert(tail != nullptr);

    head->prevPtr = nullptr;
    head->nextPtr = tail;

    tail->prevPtr = head;
    tail->nextPtr = nullptr;

    curr = head;
    cnt = 0;
  }

  // The copy constructor
  DList(const DList &source)
  {
    head = new DLink<E>;
    assert(head != nullptr);
    tail = new DLink<E>;
    assert(tail != nullptr);

    head->prevPtr = nullptr;
    head->nextPtr = tail;

    tail->prevPtr = head;
    tail->nextPtr = nullptr;

    curr = head;
    cnt = 0;

    DLink<E> *temp = source.head;

    while (temp->nextPtr != source.tail)
    {
      append(temp->nextPtr->theElement);
      if (temp == source.curr)
        curr = tail->prevPtr->prevPtr;
      temp = temp->nextPtr;
    }
  }

  // The class destructor
  ~DList()
  {
    clear();
    delete head;
    delete tail;
  }

  // Empty the list
  void clear()
  {
    moveToStart();
    while (curr->nextPtr != tail)
    {
      remove();
    }
  }

  // Set current to first element
  void moveToStart()
  {
    curr = head;
  }

  // Set current element to end of list
  void moveToEnd()
  {
    curr = tail->prevPtr;
  }

  // Advance current to the next element
  void next()
  {
    if (curr->nextPtr == tail)
      return;
    curr = curr->nextPtr;
  }

  // Return the current element
  E &getValue() const
  {
    assert(curr != tail && curr->nextPtr != tail);
    return curr->nextPtr->theElement;
  }

  // Insert value at current position
  void insert(const E &it)
  {
    DLink<E> *newLink = new DLink<E>;
    assert(newLink != nullptr);
    newLink->theElement = it;
    newLink->prevPtr = curr;
    newLink->nextPtr = curr->nextPtr;
    curr->nextPtr->prevPtr = newLink;
    curr->nextPtr = newLink;
    cnt++;
  }

  // Append value at the end of the list
  void append(const E &it)
  {
    DLink<E> *newLink = new DLink<E>;
    assert(newLink != nullptr);
    newLink->theElement = it;
    newLink->prevPtr = tail->prevPtr;
    newLink->nextPtr = tail;
    tail->prevPtr->nextPtr = newLink;
    tail->prevPtr = newLink;
    cnt++;
  }

  // Remove and return the current element
  E remove()
  {
    assert(curr != tail && curr->nextPtr != tail);
    DLink<E> *temp = curr->nextPtr;
    E it = temp->theElement;
    curr->nextPtr = temp->nextPtr;
    temp->nextPtr->prevPtr = curr;
    delete temp;
    cnt--;
    return it;
  }

  // Advance current to the previous element
  void prev()
  {
    if (curr == head)
      return;
    curr = curr->prevPtr;
  }

  // Return position of the current element
  int currPos() const
  {
    DLink<E> *temp = head;
    int i;
    for (i = 0; curr != temp; i++)
      temp = temp->nextPtr;
    return i;
  }

  // Set current to the element at the given position
  void moveToPos(int pos)
  {
    assert(("Postion out of range.", pos >= 0 && pos <= cnt));
    curr = head;
    for (int i = 0; i < pos; i++)
      curr = curr->nextPtr;
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

  theList.moveToStart();
  for (i = 0; i < theList.length(); ++i)
  {
    cout << theList.getValue() << " ";

    theList.next();
  }
  cout << "\n";

  return 0;
}