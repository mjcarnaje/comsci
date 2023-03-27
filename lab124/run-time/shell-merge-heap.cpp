#include <iostream>
#include <chrono>

using namespace std;

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
    cout << "Average Run Time of " << this->name << ": " << this->getAverageRunTime(numIterations) << " milliseconds" << endl;
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

    return chrono::duration_cast<chrono::milliseconds>(finish - start).count();
  }
};

class ShellSort : public SortingAlgorithm
{
public:
  ShellSort(int arr[], int n, string name) : SortingAlgorithm(arr, n, name)
  {
  }

  void sort()
  {
    int gap = this->n / 2;

    while (gap > 0)
    {
      for (int i = gap; i < this->n; i++)
      {
        int temp = this->arr[i];
        int j = i;

        while (j >= gap && this->arr[j - gap] > temp)
        {
          this->arr[j] = this->arr[j - gap];
          j -= gap;
        }

        this->arr[j] = temp;
      }

      gap /= 2;
    }
  }
};

class MergeSort : public SortingAlgorithm
{
public:
  MergeSort(int arr[], int n, string name) : SortingAlgorithm(arr, n, name)
  {
  }

  void sort()
  {
    mergeSort(this->arr, 0, this->n - 1);
  };

private:
  void mergeSort(int arr[], int left, int right)
  {
    if (left < right)
    {
      int mid = left + (right - left) / 2;

      mergeSort(arr, left, mid);
      mergeSort(arr, mid + 1, right);

      merge(arr, left, mid, right);
    }
  }

  void merge(int arr[], int left, int mid, int right)
  {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[n1], rightArr[n2];

    for (int i = 0; i < n1; i++)
    {
      leftArr[i] = arr[left + i];
    }

    for (int j = 0; j < n2; j++)
    {
      rightArr[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
      if (leftArr[i] <= rightArr[j])
      {
        arr[k] = leftArr[i];
        i++;
      }
      else
      {
        arr[k] = rightArr[j];
        j++;
      }
      k++;
    }

    while (i < n1)
    {
      arr[k] = leftArr[i];
      i++;
      k++;
    }

    while (j < n2)
    {
      arr[k] = rightArr[j];
      j++;
      k++;
    }
  }
};

class HeapSort : public SortingAlgorithm
{
public:
  HeapSort(int arr[], int n, string name) : SortingAlgorithm(arr, n, name)
  {
  }

  void sort()
  {
    for (int i = this->n / 2 - 1; i >= 0; i--)
    {
      heapify(this->arr, this->n, i);
    }

    for (int i = this->n - 1; i >= 0; i--)
    {
      int temp = this->arr[0];
      this->arr[0] = this->arr[i];
      this->arr[i] = temp;

      heapify(this->arr, i, 0);
    }
  };

private:
  void heapify(int arr[], int n, int i)
  {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
    {
      largest = left;
    }

    if (right < n && arr[right] > arr[largest])
    {
      largest = right;
    }

    if (largest != i)
    {
      int temp = arr[i];
      arr[i] = arr[largest];
      arr[largest] = temp;

      heapify(arr, n, largest);
    }
  }
};

void genIntArr(int arr[], int size)
{
  srand(time(0));
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
  int arraySize, numIterations;

  cout << "Enter the size of the array: ";
  cin >> arraySize;

  cout << "Enter the number of iterations: ";
  cin >> numIterations;

  cout << "== Running " << numIterations << " iterations for each method ==" << endl;

  int arr[arraySize];
  int arr2[arraySize];
  int arr3[arraySize];

  genIntArr(arr, arraySize);
  copyArr(arr, arr2, arraySize);
  copyArr(arr, arr3, arraySize);

  ShellSort shellSort(arr, arraySize, "Shell Sort");
  MergeSort mergeSort(arr2, arraySize, "Merge Sort");
  HeapSort heapSort(arr3, arraySize, "Heap Sort");

  shellSort.printAverageRunTime(numIterations);
  mergeSort.printAverageRunTime(numIterations);
  heapSort.printAverageRunTime(numIterations);

  return 0;
}
