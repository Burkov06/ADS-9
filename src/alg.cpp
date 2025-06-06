// Copyright 2022 NNTU-CS

#include <cstdlib>
#include <locale>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "tree.h"

PMTree::Node::Node(char symbol) {
    val = symbol;
}

PMTree::Node::~Node() {
    std::for_each(children.begin(), children.end(), [](Node* child) {
        delete child;
    });
}

PMTree::PMTree(const std::vector<char>& elements) : root_(nullptr) {
    root_ = new Node(0);
    auto sorted_elements = elements;
    std::sort(sorted_elements.begin(), sorted_elements.end());
    constructTree(root_, sorted_elements);
}

PMTree::~PMTree() {
  delete root_;
}

PMTree::Node* PMTree::getRoot() const {
  return root_;
}

void PMTree::constructTree(Node* current, const std::vector<char>& elements) {
    if (elements.size() == 0) return;
    
    for (size_t pos = 0; pos < elements.size(); ++pos) {
        Node* new_child = new Node(elements[pos]);
        current->children.emplace_back(new_child);
        
        std::vector<char> new_elements(elements);
        new_elements.erase(new_elements.begin() + pos);
        constructTree(new_child, new_elements);
    }
}

namespace {
void traverseTree(PMTree::Node* current_node, 
                std::vector<char>& current_path,
                std::vector<std::vector<char>>& results) {
    bool is_root = (current_node->val == '\0');
    
    if (!is_root) {
        current_path.emplace_back(current_node->val);
    }
    
    if (current_node->children.empty()) {
        results.emplace_back(current_path);
    } else {
        std::for_each(current_node->children.begin(), current_node->children.end(),
            [&](PMTree::Node* child) {
                traverseTree(child, current_path, results);
            });
    }
    
    if (!is_root) {
        current_path.pop_back();
    }
}
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> path;
  dfs(tree.getRoot(), path, result);
  return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  auto all = getAllPerms(tree);
  if (num < 1 || num > static_cast<int>(all.size())) return {};
  return all[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int position) {
    const auto& root_children = tree.getRoot()->children;
    std::vector<char> symbols;
    std::transform(root_children.begin(), root_children.end(), 
                  std::back_inserter(symbols),
                  [](const PMTree::Node* node) { return node->val; });
    
    int count = symbols.size();
    int factorial = std::accumulate(symbols.begin(), symbols.end(), 1,
        [](int a, char) { return a * (a + 1); }); // Альтернативный расчёт факториала
    
    if (position < 1 || position > factorial) return {};
    
    std::vector<char> permutation;
    std::vector<char> remaining_symbols = symbols;
    int current_pos = position - 1;
    
    while (count > 0) {
        factorial /= count;
        int index = current_pos / factorial;
        permutation.emplace_back(remaining_symbols[index]);
        remaining_symbols.erase(remaining_symbols.begin() + index);
        current_pos %= factorial;
        count--;
    }
    
    return permutation;
}
