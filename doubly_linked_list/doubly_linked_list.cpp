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

private:
  void init()
  {
    head = new DLink<E>;
    tail = new DLink<E>;

    head->prevPtr = nullptr;
    head->nextPtr = tail;

    tail->prevPtr = head;
    tail->nextPtr = nullptr;

    curr = head;
    cnt = 0;
  }

  void emptyList()
  {
    curr = head;
    while (curr != nullptr)
    {
      DLink<E> *temp = curr;
      curr = curr->nextPtr;
      delete temp;
    }
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
    init();
  }

  // The copy constructor
  DList(const DList &source)
  {
    init();

    DLink<E> *temp = source.head;

    while (temp->nextPtr != source.tail)
    {
      append(temp->nextPtr->theElement);
      temp = temp->nextPtr;
      if (temp == source.curr)
        curr = temp;
    }
  }

  // The class destructor
  ~DList()
  {
    emptyList();
  }

  // Empty the list
  void clear()
  {
    emptyList();
    init();
  }

  // Set current to first element
  void moveToStart()
  {
    curr = head;
  }

  // Set current element to end of list
  void moveToEnd()
  {
    // not sure if this is correct
    curr = tail->prevPtr;
  }

  // Advance current to the next element
  void next()
  {
    if (curr == tail)
      return;
    curr = curr->nextPtr;
  }

  // Return the current element
  E &getValue() const
  {
    return curr->nextPtr->theElement;
  }

  // Insert value at current position
  void insert(const E &it)
  {
    DLink<E> *newLink = new DLink<E>;
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
    if (curr->nextPtr == tail)
      return '\0';

    E it = curr->nextPtr->theElement;

    curr->nextPtr = curr->nextPtr->nextPtr;
    curr->nextPtr->nextPtr->prevPtr = curr;

    delete curr->nextPtr;

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

  void debug()
  {
    cout << endl;

    DLink<E> *temp = head;

    cout << "CURRENT POINTER: ";
    cout << (temp == head)  ?  "HEAD" : (temp == tail) ? "TAIL" : to_string(temp->theElement) << endl;

    int index = 0;

    while (temp != nullptr)
    {
      cout << endl;
      cout << "|---------------------------------------------|" << endl;
      cout << "| INDEX: " << index << endl;
      cout << "| PREVIOUS POINTER: " << temp->prevPtr << endl;
      cout << "| [POINTER-VALUE]: " << temp << " - ";
      cout << (temp == head)  ?  "HEAD" : (temp == tail) ? "TAIL" : to_string(temp->theElement) << endl;
      cout << "| NEXT POINTER: " << temp->nextPtr << endl;
      cout << "|---------------------------------------------|" << endl;
      cout << endl;
      temp = temp->nextPtr;
      index++;
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