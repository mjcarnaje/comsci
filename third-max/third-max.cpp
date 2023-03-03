#include <iostream>
#include <limits>

using namespace std;

const int NEGATIVE_INFINITY = -numeric_limits<int>::infinity();

// ====== UTIL ====== //
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

// ==================== //

int getThirdMax1(int arr[], int size)
{
  int max = NEGATIVE_INFINITY;
  int secondMax = NEGATIVE_INFINITY;
  int thirdMax = NEGATIVE_INFINITY;

  for (int i = 0; i < size; i++)
  {
    if (arr[i] > max)
    {
      thirdMax = secondMax;
      secondMax = max;
      max = arr[i];
    }
    else if (arr[i] > secondMax && arr[i] < max)
    {
      thirdMax = secondMax;
      secondMax = arr[i];
    }
    else if (arr[i] > thirdMax && arr[i] < secondMax)
    {
      thirdMax = arr[i];
    }
  }

  return thirdMax;
}

int getThirdMax2(int arr[], int size)
{
  int maxIdx = getMaxNumIndex(arr, size);
  removeMaxNum(arr, size, maxIdx);
  int secondMaxIdx = getMaxNumIndex(arr, size);
  removeMaxNum(arr, size, secondMaxIdx);
  int thirdMaxIdx = getMaxNumIndex(arr, size);
  return arr[thirdMaxIdx];
}

int getThirdMax3(int arr[], int size)
{
  bubbleSort(arr, size);
  if (size < 3)
    return arr[0];
  return arr[size - 3];
}

int main()
{
  int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2};
  int len1 = sizeof(arr1) / sizeof(int);
  int first = getThirdMax1(arr1, len1);

  int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2};
  int len2 = sizeof(arr2) / sizeof(int);
  int second = getThirdMax2(arr2, len2);

  int arr3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2};
  int len3 = sizeof(arr3) / sizeof(int);
  int third = getThirdMax3(arr3, len3);

  cout << "[FIRST]:" << first << endl;
  cout << "[SECOND]:" << second << endl;
  cout << "[THIRD]:" << third << endl;
}