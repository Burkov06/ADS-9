// Copyright 2022 NNTU-CS
#include "tree.h"
#include <chrono>
#include <random>
#include <iostream>

int main() {
    std::vector<char> base = {'1','2','3'};
    PMTree tree(base);

    auto perms = getAllPerms(tree);
    for (const auto& p : perms) {
        for (char c : p) std::cout << c;
        std::cout << '\n';
    }

    std::mt19937 gen(std::random_device{}());
    for (int n = 3; n <= 7; ++n) {
        std::vector<char> symbols;
        for (int i = 0; i < n; ++i) symbols.push_back('a' + i);
        PMTree t(symbols);
        std::uniform_int_distribution<> dist(1, t.factorial(n));

        auto t0 = std::chrono::high_resolution_clock::now();
        getAllPerms(t);
        auto t1 = std::chrono::high_resolution_clock::now();
        getPerm1(t, dist(gen));
        auto t2 = std::chrono::high_resolution_clock::now();
        getPerm2(t, dist(gen));
        auto t3 = std::chrono::high_resolution_clock::now();

        auto d1 = std::chrono::duration<double>(t1 - t0).count();
        auto d2 = std::chrono::duration<double>(t2 - t1).count();
        auto d3 = std::chrono::duration<double>(t3 - t2).count();

        std::cout << "n=" << n << " all=" << d1 << "s p1=" << d2 << "s p2=" << d3 << "s\n";
    }

    return 0;
}
