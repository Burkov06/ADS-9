// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <cstdint>
#include "tree.h"

int main() {
  std::vector<char> input = {'1', '2', '3'};
  PMTree tree(input);

  std::cout << "All permutations:\n";
  auto allPerms = getAllPerms(tree);
  for (const auto& perm : allPerms) {
    for (char c : perm) std::cout << c;
    std::cout << '\n';
  }

  auto p1 = getPerm1(tree, 1);
  std::cout << "getPerm1(tree, 1): ";
  for (char c : p1) std::cout << c;
  std::cout << '\n';

  auto p2 = getPerm2(tree, 2);
  std::cout << "getPerm2(tree, 2): ";
  for (char c : p2) std::cout << c;
  std::cout << '\n';

  return 0;
}
