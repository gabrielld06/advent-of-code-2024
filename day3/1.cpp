#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

int solve(ifstream &input) {
  int i = 1, mult = 1;
  string n = "";
  const string chain = "mul(*,*)";
  while (i < chain.size() && input.good()) {
    char c = input.get();

    if (chain[i] == '*') {
      if (c == chain[i + 1]) {
        i += 2;
        mult *= atoi(n.c_str());
        n = "";
        continue;
      }

      int digit = c - '0';

      if (digit < 0 or digit > 9) {
        return 0;
      }

      n += c;
    } else if (chain[i] != c) {
      return 0;
    } else {
      i++;
    }
  }

  return mult;
}

int main(int argc, char **argv) {
  assert(argc == 2);

  string filename = argv[1];

  ifstream input(filename);

  int sum = 0;
  while (input.good()) {
    char c = input.get();
    if (c == 'm') {
      sum += solve(input);
    }
  }

  cout << sum << endl;

  return 0;
}
