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
void dfs(PMTree::Node* node, std::vector<char>& path,
         std::vector<std::vector<char>>& out) {
  if (node->val != '\0') path.push_back(node->val);
  if (node->children.empty()) {
    out.push_back(path);
  } else {
    for (auto child : node->children) {
      dfs(child, path, out);
    }
  }
  if (node->val != '\0') path.pop_back();
}
}  // namespace

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

std::vector<char> getPerm2(PMTree& tree, int num) {
  std::vector<char> elems;
  for (auto child : tree.getRoot()->children) {
    elems.push_back(child->val);
  }
  int n = elems.size();
  int64_t total = 1;
  for (int i = 2; i <= n; ++i) total *= i;
  if (num < 1 || num > total) return {};
  num -= 1;
  std::vector<char> result;
  std::vector<char> available = elems;
  for (int i = n; i >= 1; --i) {
    int64_t fact = 1;
    for (int j = 2; j < i; ++j) fact *= j;
    int idx = num / fact;
    result.push_back(available[idx]);
    available.erase(available.begin() + idx);
    num %= fact;
  }
  return result;
}
