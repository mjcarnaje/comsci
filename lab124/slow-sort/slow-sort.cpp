#include <iostream>
#include <time.h>
#include <chrono>

using namespace std;

void slowSort(int a[], int i, int j) {
  if (i < j && a[i] > a[j]) {
      int min = a[i];
      int max = a[j];
      a[j] = min;
      a[i] = max;
   }
}

void printArr(int a[], int len) {
  for (int i = 0; i < len; i++) {
    cout << a[i] << " ";
  }
}

bool isSorted(int a[], int len) {
  for (int i = 0; i < len - 1; i++) {
    if (a[i] > a[i + 1]) {
      return false;
    }
  }
    return true;

}

int main()
{
   int size = 5000;
   int arr[size];

  srand(time(0));

  cout << "Generating array of integers" << endl;

  for (int i = 0; i < size; i++) {
    arr[i] = rand() % size;
  }

  cout << "Done generating.." << endl;


  cout << "Sorting.." << endl;

  auto start = chrono::high_resolution_clock::now();

  while (!isSorted(arr, size)) {
    cout << ".";
    int i = rand() % size;
    int j = rand() % size;
    slowSort(arr, i, j);
  }

  cout << "Done sorting.." << endl;

  auto finish = chrono::high_resolution_clock::now();

  double duration =  chrono::duration_cast<chrono::nanoseconds>(finish - start).count();

  cout << "Duration: " << duration << " ms" << endl;

  return 0;
}
