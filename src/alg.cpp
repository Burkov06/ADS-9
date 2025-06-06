// Copyright 2022 NNTU-CS
#include "tree.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <algorithm>

PMTree::Node::Node(char v) : val(v) {}

PMTree::Node::~Node() {
  for (auto c : children) {
    delete c;
  }
}

PMTree::PMTree(const std::vector<char>& elems) {
  root_ = new Node('\0');
  std::vector<char> rem = elems;
  std::sort(rem.begin(), rem.end());
  buildTree(root_, rem);
}

PMTree::~PMTree() {
  delete root_;
}

PMTree::Node* PMTree::getRoot() const {
  return root_;
}

void PMTree::buildTree(Node* node, const std::vector<char>& remaining) {
  if (remaining.empty()) return;
  std::vector<char> rem = remaining;
  std::sort(rem.begin(), rem.end());
  for (size_t i = 0; i < rem.size(); ++i) {
    char c = rem[i];
    Node* child = new Node(c);
    node->children.push_back(child);
    std::vector<char> next = rem;
    next.erase(next.begin() + i);
    buildTree(child, next);
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
