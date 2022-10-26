/*
CCC121 Laboratory Exercise No. 1
Due: November 20, 2022 (Sunday) at 11:55PM
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
    cnt = 0;
    tail = nullptr;
    head = nullptr;
    curr = nullptr;
  }

  // The copy constructor
  DList(const DList &source)
  {
    curr = source->curr;
    head = source->head;
    tail = source->tail;
    cnt = source->cnt;
  }

  // The class destructor
  ~DList()
  {
    //
    // ??? - implement this method
    //
  }

  // Empty the list
  void clear()
  {
    moveToStart();
    while (curr->nextPtr != nullptr)
    {

      DLink<E> *temp = curr;
      curr = curr->nextPtr;
      delete temp;
    }
    cnt = 0;
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
    if (curr == tail)
      return;
    curr = curr->nextPtr;
  }

  // Return the current element
  E &getValue() const
  {
    return curr->theElement;
  }

  // Insert value at current position
  void insert(const E &it)
  {
    /*DLink<E> *temp = new DLink<E>;

    temp->theElement = it;
    temp->nextPtr = nullptr;
    temp->prevPtr = nullptr;
    if(curr == head) {
            temp->nextPtr = head;
            temp->prevPtr = nullptr;
            head = temp;
            return;
    }
    else if ( curr == tail) {
            temp->nextPtr = nullptr;
            temp->prevPtr = curr;
            curr = temp;
    }
    temp->nextPtr = curr->nextPtr;
    temp->prevPtr = curr;
    curr = temp;


    cnt++;
    */

    DLink<E> *newlink = new DLink<E>;
    newlink->theElement = it;
    newlink->nextPtr = nullptr;
    newlink->prevPtr = nullptr;
    cnt++;

    DLink<E> *temp = head;
    while (temp != curr)
    {
      temp = temp->nextPtr;
    }

    newlink->prevPtr = temp;
    newlink->nextPtr = temp->nextPtr;
    temp->nextPtr = newlink;
    if (temp->nextPtr == nullptr)
    {
      tail = newlink;
    }
  }

  // Append value at the end of the list
  void append(const E &it)
  {
    DLink<E> *temp = new DLink<E>;
    assert(temp != nullptr);
    temp->theElement = it;
    temp->nextPtr = nullptr;
    temp->prevPtr = tail;

    cnt++;

    if (head == nullptr)
    {
      head = temp;
      tail = temp;
      curr = temp;
    }

    tail->nextPtr = temp;
    tail = temp;
    curr = temp;
  }

  // Remove and return the current element
  E remove()
  {
    DLink<E> *temp = curr;
    E it = temp->theElement;

    if (head == temp->prevPtr)
    {

      head = curr;
    }
    else if (tail == temp->nextPtr)
    {
      tail = curr;
    }

    temp->prevPtr->nextPtr = temp->nextPtr;
    temp->nextPtr->prevPtr = temp->prevPtr;

    curr = temp->nextPtr;
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
    int i;
    DLink<E> *temp = head;

    for (i = 0; curr != temp; i++)
    {

      temp = temp->nextPtr;
    }
    return i;
  }

  // Set current to the element at the given position
  void moveToPos(int pos)
  {
    moveToStart();
    for (int i = 0; i < pos; i++)
    {
      curr = curr->nextPtr;
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
  /*
      while (i < 20)
      {
          theList.insert(i);

          ++i;
      }
  */

  // display the contents of the list
  cout << "Display 0-19"
       << "\n\n";
  theList.moveToStart();
  for (i = 0; i < theList.length(); ++i)
  {
    cout << theList.getValue() << " ";

    theList.next();
  }
  cout << "\n";

  // display the contents of the list in reverse order
  cout << "\n\n Display reverse 1-9"
       << "\n\n";
  theList.moveToEnd();
  for (i = 0; i < theList.length(); ++i)
  {

    cout << theList.getValue() << " ";
    theList.prev();
  }
  cout << "\n";

  // replace the contents of the list
  theList.clear();

  for (i = 0; i < 10; ++i)
  {
    theList.append(i + 100);
  }

  // display the contents of the list
  cout << "Display 100-109"
       << "\n\n";

  theList.moveToStart();
  for (i = 0; i < theList.length(); ++i)
  {
    cout << theList.getValue() << " ";

    theList.next();
  }
  cout << "\n";

  // remove two elements at the specified position
  theList.moveToPos(5);
  cout << "\nMove Curreent pos to: \t" << theList.currPos() << "\n with a value of: \t" << theList.getValue() << "\n\n";

  theList.remove();
  cout << "Removing 105\n";
  theList.remove();
  cout << "removing 106\n";

  // display the contents of the list
  cout << "\nDIsplay\n\n";
  theList.moveToStart();
  for (i = 0; i < theList.length(); ++i)
  {
    cout << theList.getValue() << " ";

    theList.next();
  }
  cout << "\n";
  // display the contents of the list in reverse order
  cout << "\nREVERSE\n\n";
  theList.moveToEnd();
  for (i = 0; i < theList.length(); ++i)
  {

    cout << theList.getValue() << " ";
    theList.prev();
  }
  cout << "\n";

  cout << "Done";
  return 0;
}
