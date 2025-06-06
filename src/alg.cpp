// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include "tree.h"
#include <algorithm>
#include <memory>
#include <vector>

PMTree::PMTree(const std::vector<char>& input) : elements(input) {
    root = std::make_unique<Node>('\0'); 
    buildTree(root, elements);
}

int PMTree::factorial(int n) const {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

void PMTree::buildTree(std::unique_ptr<Node>& parent, const std::vector<char>& remaining) {
    std::vector<char> sorted = remaining;
    std::sort(sorted.begin(), sorted.end());

    for (char c : sorted) {
        auto child = std::make_unique<Node>(c);
        std::vector<char> newRemaining;
        for (char r : remaining) {
            if (r != c) newRemaining.push_back(r);
        }
        buildTree(child, newRemaining);
        parent->children.push_back(std::move(child));
    }
}

std::vector<std::vector<char>> PMTree::generateAll() const {
    std::vector<std::vector<char>> result;
    std::vector<char> path;
    traverseTree(root.get(), path, result);
    return result;
}

void PMTree::traverseTree(Node* node, std::vector<char>& path, std::vector<std::vector<char>>& result) const {
    if (node->value != '\0') path.push_back(node->value);
    if (node->children.empty()) result.push_back(path);
    else for (const auto& child : node->children) traverseTree(child.get(), path, result);
    if (node->value != '\0') path.pop_back();
}

bool PMTree::findPermByCounting(Node* node, std::vector<char>& path, int& count, int target, std::vector<char>& result) const {
    if (!result.empty()) return true;
    if (node->value != '\0') path.push_back(node->value);
    if (node->children.empty()) {
        if (++count == target) result = path;
    } else {
        for (const auto& child : node->children) {
            if (findPermByCounting(child.get(), path, count, target, result)) return true;
        }
    }
    if (node->value != '\0') path.pop_back();
    return false;
}

bool PMTree::findPermByNavigating(Node* node, std::vector<char>& path, int& remaining, std::vector<char>& result) const {
    if (node->value != '\0') path.push_back(node->value);
    if (node->children.empty()) {
        if (remaining == 0) result = path;
        remaining--;
        return !result.empty();
    }
    for (const auto& child : node->children) {
        int subtree_size = factorial(child->children.size());
        if (remaining >= subtree_size) remaining -= subtree_size;
        else if (findPermByNavigating(child.get(), path, remaining, result)) return true;
    }
    if (node->value != '\0') path.pop_back();
    return false;
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    return tree.generateAll();
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    std::vector<char> result;
    std::vector<char> path;
    int count = 0;
    const_cast<PMTree&>(tree).findPermByCounting(tree.root.get(), path, count, num, result);
    return (count >= num) ? result : std::vector<char>();
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    if (num < 1 || num > tree.factorial(tree.elements.size())) return {};
    std::vector<char> result;
    std::vector<char> path;
    int remaining = num - 1;
    const_cast<PMTree&>(tree).findPermByNavigating(tree.root.get(), path, remaining, result);
    return result;
}
