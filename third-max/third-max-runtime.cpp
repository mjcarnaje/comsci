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

  SortingAlgorithm(int arr[], int n)
  {
    this->n = n;
    this->orig = new int[n];
    this->arr = new int[n];
  }

  void initArray()
  {
    for (int i = 0; i < this->n; ++i)
    {
      arr[i] = orig[i];
    }
  }

  virtual void sort() = 0;

  virtual void printAverageRunTime() = 0;

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
    for (int i = 0; i < this->n; ++i)
    {
      if (this->arr[i] < this->arr[i - 1])
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
  FirstMethod(int arr[], int n) : SortingAlgorithm(arr, n)
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

  void printAverageRunTime()
  {
    cout << "Average Run Time of First Method: " << this->getAverageRunTime(10) << " nanoseconds" << endl;
  };
};

class SecondMethod : public SortingAlgorithm
{
public:
  SecondMethod(int arr[], int n) : SortingAlgorithm(arr, n)
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

  void printAverageRunTime()
  {
    cout << "Average Run Time of Second Method: " << this->getAverageRunTime(10) << " nanoseconds" << endl;
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
  ThirdMethod(int arr[], int n) : SortingAlgorithm(arr, n)
  {
  }

  void sort()
  {
    int thirdMax;
    bubbleSort(this->arr, this->n);
    if (this->n < 3)
      thirdMax = this->arr[0];
    thirdMax = this->arr[this->n - 3];
  };

  void printAverageRunTime()
  {
    cout << "Average Run Time of Third Method: " << this->getAverageRunTime(10) << " nanoseconds" << endl;
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
};

int *generateRandomArray(int n)
{
  int *arr = new int[n];
  for (int i = 0; i < n; i++)
  {
    arr[i] = rand() % n;
  }
  return arr;
}

int main()
{
  int n = 100000;

  int *arr = generateRandomArray(n);

  FirstMethod firstMethod(arr, n);
  firstMethod.printAverageRunTime();

  SecondMethod secondMethod(arr, n);
  secondMethod.printAverageRunTime();

  ThirdMethod thirdMethod(arr, n);
  thirdMethod.printAverageRunTime();
}