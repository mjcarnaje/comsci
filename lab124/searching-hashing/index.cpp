#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

class LinearProbing
{
private:
  int table_length;
  int *hash_table;
  int probe_count = 0;

  int hashFunction(int value)
  {
    return value % table_length;
  }

  void reset()
  {
    for (int i = 0; i < table_length; i++)
      hash_table[i] = -1;
  }

public:
  LinearProbing(int table_length)
  {
    this->table_length = table_length;
    hash_table = new int[table_length]();
    reset();
  }

  ~LinearProbing()
  {
    delete[] hash_table;
  }

  void insert(int value)
  {
    int index = hashFunction(value);

    while (hash_table[index] != -1)
    {
      index = (index + 1) % table_length;
      probe_count++;
    }

    hash_table[index] = value;
  }
};

class QuadraticProbing
{
private:
  int table_length;
  int *hash_table;
  int probe_count = 0;

  int hashFunction(int value)
  {
    return value % table_length;
  }

  void reset()
  {
    for (int i = 0; i < table_length; i++)
      hash_table[i] = -1;
  }

public:
  QuadraticProbing(int table_length)
  {
    this->table_length = table_length;
    hash_table = new int[table_length]();
    reset();
  }

  ~QuadraticProbing()
  {
    delete[] hash_table;
  }

  void insert(int value)
  {
    int index = hashFunction(value);
    int i = 1;

    while (hash_table[index] != -1)
    {
      index = (index + i * i) % table_length;
      probe_count++;
      i++;
    }

    hash_table[index] = value;
  }
};

class DoubleHashing
{
private:
  int table_length;
  int *hash_table;
  int probe_count = 0;

  int hashFunction(int value)
  {
    return value % table_length;
  }

  int hashFunction2(int value)
  {
    return 13 - (value % 13);
  }

  void reset()
  {
    for (int i = 0; i < table_length; i++)
      hash_table[i] = -1;
  }

public:
  DoubleHashing(int table_length)
  {
    this->table_length = table_length;
    this->hash_table = new int[table_length]();
    reset();
  }

  ~DoubleHashing()
  {
    delete[] hash_table;
  }

  void insert(int value)
  {
    int index = hashFunction(value);
    int index2 = hashFunction2(value);

    while (hash_table[index] != -1)
    {
      index = (index + index2) % table_length;
      probe_count++;
    }

    hash_table[index] = value;
  }
};

void getDiff(clock_t start, clock_t end)
{
  cout << "Time: " << (end - start) * 1000 / CLOCKS_PER_SEC << " ms" << endl;
}

int main()
{
  int arr_len = 100000;
  vector<int> arr(arr_len);

  srand(time(0));
  for (int i = 0; i < arr_len; i++)
  {
    arr[i] = rand() % 1000;
  }

  clock_t start, end;

  LinearProbing lp(arr_len);
  start = clock();
  for (int i = 0; i < arr_len; i++)
  {
    lp.insert(arr[i]);
  }
  end = clock();
  getDiff(start, end);

  QuadraticProbing qp(arr_len);
  start = clock();
  for (int i = 0; i < arr_len; i++)
  {
    qp.insert(arr[i]);
  }
  end = clock();
  getDiff(start, end);

  DoubleHashing dh(arr_len);
  start = clock();
  for (int i = 0; i < arr_len; i++)
  {
    dh.insert(arr[i]);
  }
  end = clock();
  getDiff(start, end);

  return 0;
}
