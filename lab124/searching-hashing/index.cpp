#include <iostream>

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
    hash_table = new int[table_length];
    reset();
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

  void display()
  {
    cout << "===== Linear Probing =====" << endl;

    for (int i = 0; i < table_length; i++)
    {
      if (hash_table[i] != -1)
        cout << hash_table[i] << " ";
      cout << "_ ";
    }
    cout << endl;
    cout << "Probe Count: " << probe_count << endl;
    cout << endl;
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
    hash_table = new int[table_length];
    reset();
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

  void display()
  {
    cout << "===== Quadratic Probing =====" << endl;

    for (int i = 0; i < table_length; i++)
    {
      if (hash_table[i] != -1)
        cout << hash_table[i] << " ";
      cout << "_ ";
    }
    cout << endl;
    cout << "Probe Count: " << probe_count << endl;
    cout << endl;
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
    return 7 - (value % 7);
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
    hash_table = new int[table_length];
    reset();
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

  void display()
  {
    cout << "===== Double Hashing =====" << endl;

    for (int i = 0; i < table_length; i++)
    {
      if (hash_table[i] != -1)
        cout << hash_table[i] << " ";
      cout << "_ ";
    }
    cout << endl;
    cout << "Probe Count: " << probe_count << endl;
    cout << endl;
  }
};

int main()
{
  int arr[] = {25, 88, 3, 38, 20, 71, 55, 56, 50, 105};
  int arrSize = sizeof(arr) / sizeof(arr[0]);

  int table_length = 17;

  LinearProbing lp(table_length);
  QuadraticProbing qp(table_length);
  DoubleHashing dh(table_length);

  for (int i = 0; i < arrSize; i++)
  {
    lp.insert(arr[i]);
    qp.insert(arr[i]);
    dh.insert(arr[i]);
  }

  lp.display();
  qp.display();
  dh.display();

  return 0;
}