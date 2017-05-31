//-------------------------------------
//-------------------------------------
//||                                 ||
//||        Joao Rebelo Pires        ||
//||                                 ||
//||              2017               ||
//||                                 ||
//-------------------------------------
//-------------------------------------

#include <iostream>
#include "avl.h"
#include "avl.cpp" // clang++ will not compile without this
#include <ctime> // Library for time tests
#include <vector>

using namespace std;

AVL<int> avl = AVL<int>();
vector<int> v;

int main() {
  clock_t fst, snd;
  int n; cin >> n;
  double tm;

  fst = clock();
  for(int i = 0; i < n; i++) {
    int k; cin >> k;
    v.push_back(k);
    avl.insert(k);
  }
  snd = clock();

  tm = 1000.0 * (snd - fst) / CLOCKS_PER_SEC;

  cout << "Insertion: " << tm << " milliseconds." << endl;

  fst = clock();
  cout << "Minimum value: " << avl.minValue() << endl;
  snd = clock();

  tm = 1000.0 * (snd - fst) / CLOCKS_PER_SEC;

  cout << "Minimum: " << tm << " milliseconds." << endl;

  fst = clock();
  cout << "Maximum value: " << avl.maxValue() << endl;
  snd = clock();

  tm = 1000.0 * (snd - fst) / CLOCKS_PER_SEC;

  cout << "Maximum: " << tm << " milliseconds." << endl;

  return 0;
}
