#include <iostream>
#include <assert.h>
#include "stack.h"
#define defaultSize 10

using namespace std;

void Assert(int value, const char *str)
{
  assert(value);
}

template <typename E>
class AStack : public Stack<E>
{
private:
  int maxSize;
  int top;
  E *listArray;

public:
  AStack(int size = defaultSize)
  {
    maxSize = size;
    top = 0;
    listArray = new E[size];
  }

  ~AStack()
  {
    delete[] listArray;
  }

  void clear()
  {
    top = 0;
  }

  void push(const E &it)
  {
    Assert(top != maxSize, "Stack is full");
    listArray[top++] = it;
  }

  E pop()
  {
    Assert(top != 0, "Stack is empty");
    return listArray[--top];
  }

  const E &topValue() const
  {
    Assert(top != 0, "Stack is empty");
    return listArray[top - 1];
  }

  int length() const
  {
    return top;
  }

  void display()
  {
    for (int i = 0; i < top; i++)
    {
      cout << listArray[i] << endl;
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
  AStack<int> stack;
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