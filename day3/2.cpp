#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

int mul_parser(ifstream &input) {
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

string dont_parser(ifstream &input) {
  string command = "";

  // const string chain = "don't()";

  char c = input.get();
  if (c != '\'') {
    return "";
  }

  c = input.get();
  if (c != 't') {
    return "";
  }

  c = input.get();
  if (c != '(') {
    return "";
  }

  c = input.get();
  if (c != ')') {
    return "";
  }

  return "dont";
}

string do_parser(ifstream &input) {
  string command = "";

  // const string chain = "do()";

  char c = input.get();
  if (c != 'o') {
    return "";
  }

  c = input.get();
  if (c == 'n') {
    return dont_parser(input);
  } else if (c != '(') {
    return "";
  }

  c = input.get();
  if (c != ')') {
    return "";
  }

  return "do";
}

int main(int argc, char **argv) {
  assert(argc == 2);

  string filename = argv[1];

  ifstream input(filename);

  int sum = 0;
  bool enabled = true;
  while (input.good()) {
    char c = input.get();
    if (enabled && c == 'm') {
      sum += mul_parser(input);
    } else if (c == 'd') {
      string command = do_parser(input);

      if (command == "do") {
        enabled = true;
      } else if (command == "dont") {
        enabled = false;
      }
    }
  }

  cout << sum << endl;

  return 0;
}
