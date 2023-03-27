#include <iostream>

using namespace std;

void selectionSort(int arr[], int n) {
    int lastIdx = n - 1;

    for (int i = 0; i < lastIdx; ++i) {
        int minValue = arr[i];
        int minIndex = i;

        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < minValue) {
                minValue = arr[j];
                minIndex = j;
            }
        }

        arr[minIndex] = arr[i];
        arr[i] = minValue;
    }
}

int main() {
  int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2};
   int len  =  sizeof(arr1) / sizeof(int);
   selectionSort(arr1, len);   
   for (int i = 0; i < len; ++i) {
       cout << arr1[i] << endl;
   }   
   return 0;
}