#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  ofstream fout("data.txt");
  for (int i = 0; i < 100000; i++)
  {
    fout << rand() % 1000 << endl;
  }
  fout.close();
  return 0;
}
