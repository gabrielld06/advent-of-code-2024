#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

bool isOrdered(const vector<int> &updates, const set<int> &has,
               const map<int, vector<int>> &rules) {
  set<int> seen;
  for (auto &e : updates) {
    auto it = rules.find(e);
    if (it != rules.end()) {
      bool all_seen = true;

      for (auto &rule : it->second) {
        if (has.find(rule) != has.end() && seen.find(rule) == seen.end()) {
          all_seen = false;
          break;
        }
      }

      if (!all_seen) {
        return false;
      }
    }

    seen.insert(e);
  }

  return true;
}

int solve(const vector<int> &updates, const set<int> &has,
          const map<int, vector<int>> &rules) {
  if (isOrdered(updates, has, rules)) {
    return 0;
  }

  set<int> seen = set<int>();
  vector<int> ordered = vector<int>();
  while (ordered.size() < updates.size()) {
    for (auto &e : updates) {
      if (seen.find(e) != seen.end()) {
        continue;
      }

      bool should_insert = true;

      // check rules
      auto it = rules.find(e);
      if (it != rules.end()) {
        for (auto &rule : it->second) {
          if (has.find(rule) != has.end() && seen.find(rule) == seen.end()) {
            should_insert = false;
            break;
          }
        }
      }

      if (should_insert) {
        seen.insert(e);
        ordered.push_back(e);
        continue;
      }
    }
  }

  int middle = ordered.size() / 2;

  return ordered[middle];
}

int main(int argc, char **argv) {
  assert(argc == 2);

  string filename = argv[1];

  ifstream input(filename);

  int x, y, ans = 0;
  string line;
  map<int, vector<int>> rules;
  while (getline(input, line)) {
    if (line == "") {
      break;
    }
    sscanf(line.c_str(), "%d|%d", &x, &y);

    rules[y].push_back(x);
  }

  set<int> has;
  vector<int> updates;
  while (input.good()) {
    input >> x;
    updates.push_back(x);
    has.insert(x);

    char c = input.get();
    if (c == '\n') {
      ans += solve(updates, has, rules);

      has = set<int>();
      updates = vector<int>();
    }
  }

  cout << ans << endl;

  return 0;
}
