#include <iostream>
#include <limits>
#include <chrono>

using namespace std;

const int NEGATIVE_INFINITY = -numeric_limits<int>::infinity();

class SortingAlgorithm
{

public:
  int n;
  int *orig;
  int *arr;
  string name;

  SortingAlgorithm(int arr[], int n, string name)
  {
    this->n = n;
    this->orig = new int[n];
    this->arr = new int[n];
    this->name = name;
  }

  virtual void sort() = 0;

  void initArray()
  {
    for (int i = 0; i < this->n; ++i)
    {
      arr[i] = orig[i];
    }
  }

  void printAverageRunTime(int numIterations)
  {
    cout << "Average Run Time of " << this->name << ": " << this->getAverageRunTime(numIterations) << " nanoseconds" << endl;
  };

  double getAverageRunTime(int numIterations)
  {
    double sum = 0.0;

    for (int i = 0; i < numIterations; i++)
    {
      sum += this->getRunTime();
    }

    return (sum / numIterations);
  }

protected:
  bool isSorted()
  {
    for (int i = 0; i < this->n - 1; i++)
    {
      if (this->arr[i] > this->arr[i + 1])
      {
        return false;
      }
    }

    return true;
  }

  double getRunTime()
  {
    this->initArray();

    auto start = chrono::high_resolution_clock::now();
    this->sort();
    auto finish = chrono::high_resolution_clock::now();

    if (!this->isSorted())
    {
      cout << "Something went wrong!";
    }

    return chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
  }
};

class FirstMethod : public SortingAlgorithm
{
public:
  FirstMethod(int arr[], int n, string name) : SortingAlgorithm(arr, n, name)
  {
  }

  void sort()
  {
    int max = NEGATIVE_INFINITY;
    int secondMax = NEGATIVE_INFINITY;
    int thirdMax = NEGATIVE_INFINITY;

    for (int i = 0; i < this->n; i++)
    {
      if (this->arr[i] > max)
      {
        thirdMax = secondMax;
        secondMax = max;
        max = this->arr[i];
      }
      else if (this->arr[i] > secondMax && this->arr[i] < max)
      {
        thirdMax = secondMax;
        secondMax = this->arr[i];
      }
      else if (this->arr[i] > thirdMax && this->arr[i] < secondMax)
      {
        thirdMax = this->arr[i];
      }
    }
  };
};

class SecondMethod : public SortingAlgorithm
{
public:
  SecondMethod(int arr[], int n, string name) : SortingAlgorithm(arr, n, name)
  {
  }

  void sort()
  {
    int maxIdx = this->getMaxNumIndex(this->arr, this->n);
    this->removeMaxNum(this->arr, this->n, maxIdx);
    int secondMaxIdx = this->getMaxNumIndex(this->arr, this->n);
    this->removeMaxNum(this->arr, this->n, secondMaxIdx);
    int thirdMaxIdx = this->getMaxNumIndex(this->arr, this->n);
  };

private:
  int getMaxNumIndex(int arr[], int size)
  {
    int max = NEGATIVE_INFINITY;
    int index = 0;

    for (int i = 0; i < size; i++)
    {
      if (arr[i] > max)
      {
        max = arr[i];
        index = i;
      }
    }

    return index;
  }

  void removeMaxNum(int arr[], int size, int index)
  {
    for (int i = index; i < size - 1; i++)
    {
      arr[i] = arr[i + 1];
    }
  }
};

class ThirdMethod : public SortingAlgorithm
{
public:
  ThirdMethod(int arr[], int n, string name) : SortingAlgorithm(arr, n, name)
  {
  }

  void sort()
  {
    int thirdMax;
    insertionSort(this->arr, this->n);
    if (this->n < 3)
      thirdMax = this->arr[0];
    thirdMax = this->arr[this->n - 3];
  };

private:
  void bubbleSort(int arr[], int size)
  {
    for (int i = 0; i < size; i++)
    {
      for (int j = i + 1; j < size; j++)
      {
        if (arr[i] > arr[j])
        {
          int temp = arr[i];
          arr[i] = arr[j];
          arr[j] = temp;
        }
      }
    }
  }

  void insertionSort(int arr[], int size)
  {
    for (int i = 1; i < size; i++)
    {
      int key = arr[i];
      int j = i - 1;

      while (j >= 0 && arr[j] > key)
      {
        arr[j + 1] = arr[j];
        j--;
      }

      arr[j + 1] = key;
    }
  }
};

void genIntArr(int arr[], int size)
{
  for (int i = 0; i < size; i++)
  {
    arr[i] = rand() % 1000;
  }
}

void copyArr(int arr1[], int arr2[], int size)
{
  for (int i = 0; i < size; i++)
  {
    arr2[i] = arr1[i];
  }
}

int main()
{
  cout << "Enter the size of the array: ";
  cin >> arraySize;

  cout << "Enter the number of iterations: ";
  cin >> numIterations;

  cout << "== Running " << numIterations << " iterations for each method ==" << endl;

  int originalArr[arraySize];
  genIntArr(originalArr, arraySize);

  int arr1[arraySize];
  copyArr(originalArr, arr1, arraySize);

  FirstMethod firstMethod(arr1, arraySize, "First Method");
  firstMethod.printAverageRunTime(numIterations);

  int arr2[arraySize];
  copyArr(originalArr, arr2, arraySize);

  SecondMethod secondMethod(arr2, arraySize, "Second Method");
  secondMethod.printAverageRunTime(numIterations);

  int arr3[arraySize];
  copyArr(originalArr, arr3, arraySize);

  ThirdMethod thirdMethod(arr3, arraySize, "Third Method");
  thirdMethod.printAverageRunTime(numIterations);

  return 0;
}