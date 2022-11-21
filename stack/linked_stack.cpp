#include <iostream>
#include <assert.h>
#include "stack.h"
#define defaultSize 10

using namespace std;

template <class E>
struct Link
{
  E element;
  Link<E> *next;
};

void Assert(int value, const char *str)
{
  assert(value);
}

// Linked stack implementation
template <typename E>
class LStack : public Stack<E>
{
private:
  Link<E> *top; // Pointer to first element
  int size;     // Number of elements
public:
  LStack(int sz = defaultSize) // Constructor
  {
    top = NULL;
    size = 0;
  }

  ~LStack()
  {
    clear();
  }

  void clear()
  {
    while (top != NULL)
    {
      Link<E> *temp = top;
      top = top->next;
      delete temp;
    }
    size = 0;
  }

  void push(const E &it)
  {
    Link<E> *newLink = new Link<E>;
    newLink->element = it;
    newLink->next = top;
    top = newLink;
    size++;
  }

  E pop()
  {
    Assert(top != NULL, "Stack is empty");
    E it = top->element;
    Link<E> *ltemp = top->next;
    delete top;
    top = ltemp;
    size--;
    return it;
  }

  const E &topValue() const
  {
    Assert(top != 0, "Stack is empty");
    return top->element;
  }

  int length() const
  {
    return size;
  }

  void display()
  {
    cout << "the contents are: " << endl;
    Link<E> *temp = top;
    while (temp != NULL)
    {
      cout << temp->element << endl;
      temp = temp->next;
    }
  }

  void getLength()
  {
    cout << "the size of the stack is: " << length() << endl;
  }

  void getTopValue()
  {
    cout << "the value at the top of the stack is: " << topValue() << endl;
  }
};

int main()
{
  LStack<int> stack;
  stack.push(1);
  stack.push(2);
  stack.push(3);
  stack.getLength();
  stack.display();
  stack.clear();
  stack.getLength();
  cout << "pushing 4...\n";
  stack.push(4);
  cout << "pushing 5...\n";
  stack.push(5);
  cout << "pushing 6...\n";
  stack.push(6);
  cout << "pushing 7...\n";
  stack.push(7);
  cout << "pushing 8...\n";
  stack.push(8);
  stack.getLength();
  stack.getTopValue();
  cout << "popping 8...\n";
  stack.pop();
  cout << "popping 7...\n";
  stack.pop();
  cout << "popping 6...\n";
  stack.pop();
  stack.getLength();
  cout << "clearing.." << endl;
  stack.clear();
  stack.getLength();
  return 0;
}