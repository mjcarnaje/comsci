
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
  void initialize()
  {
    head = new DLink<E>;
    tail = new DLink<E>;
    cnt = 0;
    head->prevPtr = nullptr;
    head->nextPtr = tail;
    tail->prevPtr = head;
    tail->nextPtr = nullptr;
    curr = tail;
  }

  void deleteLinks()
  {
    curr = head;
    while (curr != nullptr)
    {
      DLink<E> *nextLink = curr->nextPtr;
      delete curr;
      curr = nextLink;
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
    initialize();
  }

  // The copy constructor
  DList(const DList &source)
  {
    head = source->head;
    tail = source->tail;
    curr = source->curr;
    cnt = source->cnt;
  }

  // The class destructor
  ~DList()
  {
    deleteLinks();
  }

  // Empty the list
  void clear()
  {
    deleteLinks();
    initialize();
  }

  // Set current to first element
  void moveToStart()
  {
    curr = head->nextPtr;
  }

  // Set current element to end of list
  void moveToEnd()
  {
    curr = tail;
  }

  // Advance current to the next element
  void next()
  {
    if (curr != tail)
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
    DLink<E> *newLink = new DLink<E>;
    newLink->theElement = it;
    newLink->prevPtr = curr->prevPtr;
    newLink->nextPtr = curr;
    curr->prevPtr->nextPtr = newLink;
    if (curr->nextPtr)
      curr->nextPtr->prevPtr = newLink;
    curr = newLink;
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
    if (curr == tail)
      curr = tail->prevPtr;
    cnt++;
  }

  // Remove and return the current element
  E remove()
  {
    assert(("You can't delete unknown link.", curr != nullptr));

    E currElement = curr->theElement;

    DLink<E> *prevLink = curr->prevPtr;
    DLink<E> *nextLink = curr->nextPtr;

    prevLink->nextPtr = nextLink;
    nextLink->prevPtr = prevLink;

    delete curr;

    curr = nextLink;

    cnt--;

    return currElement;
  }

  // Advance current to the previous element
  void prev()
  {
    if (curr == head)
      return;

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

    DLink<E> *tempLink = head->nextPtr;

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
    assert(("Postion out of range.", pos >= 0 && pos <= cnt));
    curr = head->nextPtr;
    for (int i = 0; i < pos; i++)
      curr = curr->nextPtr;
  }

  void display(bool isBackward = false)
  {
    cout << endl;

    if (!isBackward)
    {
      cout << "------------- PRINTING (FORWARD) -------------" << endl;
      moveToStart();
    }
    else
    {
      cout << "------------- PRINTING (BACKWARD) -------------" << endl;
      moveToEnd();
    }

    for (int i = 0; i < length(); ++i)
    {
      cout << getValue() << " ";

      if (!isBackward)
      {
        next();
      }
      else
      {
        prev();
      }
    }

    cout << endl;
  }

  void debug()
  {
    curr = head;

    while (curr != nullptr)
    {
      cout << endl;
      cout << "|---------------------------------------------|" << endl;
      cout << "| PrevPtr: " << curr->prevPtr << endl;
      cout << "| [Ptr-Value]: " << curr << " - ";
      if (curr == head)
        cout << "HEAD" << endl;
      else if (curr == tail)
        cout << "TAIL" << endl;
      else
        cout << curr->theElement << endl;
      cout << "| NextPtr: " << curr->nextPtr << endl;
      cout << "|---------------------------------------------|" << endl;
      cout << endl;
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

  cout << "\nAdding [0-19] to the list with the append & insert function\n";

  // for (i = 0; i < 10; ++i)
  // {
  //   theList.append(i);
  // }

  theList.append(23);
  theList.append(8);
  theList.append(35);
  theList.append(10);
  theList.moveToPos(1);
  theList.insert(15);
  theList.append(15);

  // while (i < 20)
  // {
  //   theList.insert(i);
  //   ++i;
  // }

  theList.debug();
  // theList.display();
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
  // cout << "\nRemove the header link: " << theList.remove() << "\n";

  // theList.display();

  // theList.moveToEnd();
  // cout << "\nRemove the tailer link: " << theList.remove() << "\n";

  // theList.display();

  // cout << "\nThank you sir Haroun!";
  return 0;
}