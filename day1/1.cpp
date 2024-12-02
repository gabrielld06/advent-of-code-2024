#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  assert(argc == 2);

  string filename = argv[1];

  ifstream input(filename);

  int x, y;

  vector<int> l1;
  vector<int> l2;

  input >> x >> y;
  while (input.good()) {
    l1.push_back(x);
    l2.push_back(y);

    input >> x >> y;
  }

  sort(l1.begin(), l1.end());
  sort(l2.begin(), l2.end());

  int sum = 0;
  for (int i = 0; i < l1.size(); i++) {
    sum += abs(l1[i] - l2[i]);
  }

  cout << sum << endl;

  return 0;
}
