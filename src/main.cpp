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

  std::vector<int> ns = {5, 6, 7, 8};
  std::ofstream csv("times.csv");
  csv << "n,getAll,getPerm1,getPerm2\n";

  for (int n : ns) {
    std::vector<char> elems;
    for (int i = 1; i <= n; ++i) elems.push_back('0' + i);
    PMTree t(elems);

    int64_t total = 1;
    for (int i = 2; i <= n; ++i) total *= i;

    std::mt19937_64 rng(1234);
    std::uniform_int_distribution<int64_t> dist(1, total);
    int idx = static_cast<int>(dist(rng));

    using clk = std::chrono::high_resolution_clock;

    auto t0 = clk::now();
    auto allP = getAllPerms(t);
    auto t1 = clk::now();
    auto perm1 = getPerm1(t, idx);
    auto t2 = clk::now();
    auto perm2 = getPerm2(t, idx);
    auto t3 = clk::now();

    double dt_all = std::chrono::duration<double, std::milli>(t1 - t0).count();
    double dt_p1 = std::chrono::duration<double, std::milli>(t2 - t1).count();
    double dt_p2 = std::chrono::duration<double, std::milli>(t3 - t2).count();

    csv << n << "," << dt_all << "," << dt_p1 << "," << dt_p2 << "\n";
    std::cout << "n=" << n << " all=" << dt_all << "ms p1=" << dt_p1 << "ms p2=" << dt_p2 << "ms\n";
  }

  return 0;
}
