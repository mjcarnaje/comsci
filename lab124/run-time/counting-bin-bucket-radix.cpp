#include <iostream>
#include <chrono>
#include <algorithm>
#include <cstring>
#include <cmath>

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

class CountingSort : public SortingAlgorithm
{
public:
  CountingSort(int arr[], int n, string name) : SortingAlgorithm(arr, n, name)
  {
  }

  void sort()
  {
    int max_element = arr[0];
    for (int i = 1; i < n; i++)
    {
      if (arr[i] > max_element)
      {
        max_element = arr[i];
      }
    }

    int count[max_element + 1];
    memset(count, 0, sizeof(count));

    for (int i = 0; i < n; i++)
    {
      count[arr[i]]++;
    }

    for (int i = 1; i <= max_element; i++)
    {
      count[i] += count[i - 1];
    }

    int output[n];
    for (int i = n - 1; i >= 0; i--)
    {
      output[count[arr[i]] - 1] = arr[i];
      count[arr[i]]--;
    }

    for (int i = 0; i < n; i++)
    {
      arr[i] = output[i];
    }
  }
};

class BinSort : public SortingAlgorithm
{
public:
  BinSort(int arr[], int n, string name) : SortingAlgorithm(arr, n, name)
  {
  }

  void sort()
  {
    int i, j;
    int min_val = arr[0], max_val = arr[0];

    // find the minimum and maximum values in the array
    for (i = 1; i < n; i++)
    {
      if (arr[i] < min_val)
      {
        min_val = arr[i];
      }
      else if (arr[i] > max_val)
      {
        max_val = arr[i];
      }
    }

    // create a temporary array of size max_val - min_val + 1
    int *temp = new int[max_val - min_val + 1];
    for (i = 0; i < max_val - min_val + 1; i++)
    {
      temp[i] = 0;
    }

    // count the occurrences of each element in the array
    for (i = 0; i < n; i++)
    {
      temp[arr[i] - min_val]++;
    }

    // overwrite the input array with the sorted values
    for (i = min_val, j = 0; i <= max_val; i++)
    {
      while (temp[i - min_val] > 0)
      {
        arr[j++] = i;
        temp[i - min_val]--;
      }
    }

    // free the temporary array
    delete[] temp;
  }
};

class BucketSort : public SortingAlgorithm
{
public:
  BucketSort(int arr[], int n, string name) : SortingAlgorithm(arr, n, name)
  {
  }

  void sort()
  {
    // Determine the range of values in the array
    int max_element = arr[0];
    int min_element = arr[0];
    for (int i = 1; i < n; i++)
    {
      if (arr[i] > max_element)
      {
        max_element = arr[i];
      }
      if (arr[i] < min_element)
      {
        min_element = arr[i];
      }
    }

    // Determine the size of each bucket
    int bucket_size = (max_element - min_element) / n + 1;

    // Create the buckets
    int num_buckets = (max_element - min_element) / bucket_size + 1;
    std::vector<std::vector<int>> buckets(num_buckets);

    // Distribute the elements into the buckets
    for (int i = 0; i < n; i++)
    {
      int bucket_index = (arr[i] - min_element) / bucket_size;
      buckets[bucket_index].push_back(arr[i]);
    }

    // Sort each bucket
    for (int i = 0; i < num_buckets; i++)
    {
      std::sort(buckets[i].begin(), buckets[i].end());
    }

    // Merge the buckets back into the original array
    int k = 0;
    for (int i = 0; i < num_buckets; i++)
    {
      for (int j = 0; j < buckets[i].size(); j++)
      {
        arr[k] = buckets[i][j];
        k++;
      }
    }
  }
};

class RadixSort : public SortingAlgorithm
{
public:
  RadixSort(int arr[], int n, string name) : SortingAlgorithm(arr, n, name)
  {
  }

  void sort()
  {
    // Find the maximum element in the array
    int max_element = arr[0];
    for (int i = 1; i < n; i++)
    {
      if (arr[i] > max_element)
      {
        max_element = arr[i];
      }
    }

    // Perform radix sort on each digit
    for (int exp = 1; max_element / exp > 0; exp *= 10)
    {
      counting_sort(exp);
    }
  }

private:
  void counting_sort(int exp)
  {
    // Initialize the count array and output array
    int count[10] = {0};
    int output[n];

    // Count the occurrences of each digit
    for (int i = 0; i < n; i++)
    {
      int digit = (arr[i] / exp) % 10;
      count[digit]++;
    }

    // Calculate the cumulative count
    for (int i = 1; i < 10; i++)
    {
      count[i] += count[i - 1];
    }

    // Sort the elements based on the current digit
    for (int i = n - 1; i >= 0; i--)
    {
      int digit = (arr[i] / exp) % 10;
      output[count[digit] - 1] = arr[i];
      count[digit]--;
    }

    // Copy the sorted output array back to the input array
    for (int i = 0; i < n; i++)
    {
      arr[i] = output[i];
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

int main()
{
  int arraySize = 1000;
  int numIterations = 10;

  int arr[arraySize];
  genIntArr(arr, arraySize);

  // CountingSort countingSort(arr, arraySize, "CountingSort");
  // countingSort.printAverageRunTime(numIterations);

  BinSort binSort(arr, arraySize, "BinSort");
  binSort.printAverageRunTime(numIterations);

  // BucketSort bucketSort(arr, arraySize, "BucketSort");
  // bucketSort.printAverageRunTime(numIterations);

  // RadixSort radixSort(arr, arraySize, "RadixSort");
  // radixSort.printAverageRunTime(numIterations);

  return 0;
}
