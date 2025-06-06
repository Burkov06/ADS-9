// Copyright 2022 NNTU-CS
#include <vector>
#include <algorithm>
#include "tree.h"

PMTree::Node::Node(char v) : val(v) {}

PMTree::Node::~Node() {
  for (auto c : children) delete c;
}

PMTree::PMTree(const std::vector<char>& elems) {
  root_ = new Node('\0');
  std::vector<char> sorted = elems;
  std::sort(sorted.begin(), sorted.end());
  buildTree(root_, sorted);
}

PMTree::~PMTree() {
  delete root_;
}

PMTree::Node* PMTree::getRoot() const {
  return root_;
}

void PMTree::buildTree(Node* node, const std::vector<char>& remaining) {
  for (size_t i = 0; i < remaining.size(); ++i) {
    std::vector<char> next = remaining;
    Node* child = new Node(next[i]);
    node->children.push_back(child);
    next.erase(next.begin() + i);
    buildTree(child, next);
  }
}

static void dfs(PMTree::Node* node, std::vector<char>& path, std::vector<std::vector<char>>& result) {
  if (node->val != '\0') path.push_back(node->val);
  if (node->children.empty()) result.push_back(path);
  for (auto* child : node->children)
    dfs(child, path, result);
  if (node->val != '\0') path.pop_back();
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> path;
  dfs(tree.getRoot(), path, result);
  return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  auto perms = getAllPerms(tree);
  return (num >= 1 && num <= static_cast<int>(perms.size())) ? perms[num - 1] : std::vector<char>{};
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  std::vector<char> elems;
  for (auto* child : tree.getRoot()->children)
    elems.push_back(child->val);

  std::sort(elems.begin(), elems.end());
  int n = elems.size();

  std::vector<int64_t> factorial(n + 1, 1);
  for (int i = 2; i <= n; ++i) factorial[i] = factorial[i - 1] * i;

  if (num < 1 || num > factorial[n]) return {};

  num--;
  std::vector<char> result;
  std::vector<char> available = elems;

  for (int i = n; i > 0; --i) {
    int idx = num / factorial[i - 1];
    result.push_back(available[idx]);
    available.erase(available.begin() + idx);
    num %= factorial[i - 1];
  }

  return result;
}
