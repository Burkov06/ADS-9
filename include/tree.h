// Copyright 2022 NNTU-CS
#ifndef TREE_H
#define TREE_H

#include <vector>
#include <memory>

struct Node {
    char value;
    std::vector<std::unique_ptr<Node>> children;
    Node(char v) : value(v) {}
};

class PMTree {
private:
    std::unique_ptr<Node> root;
    std::vector<char> elements;

    void buildTree(std::unique_ptr<Node>& parent, const std::vector<char>& remaining);
    void traverseTree(Node* node, std::vector<char>& path,
                      std::vector<std::vector<char>>& result) const;
    bool findPermByCounting(Node* node, std::vector<char>& path, int& count, int target,
                            std::vector<char>& result) const;
    bool findPermByNavigating(Node* node, std::vector<char>& path, int& remaining,
                             std::vector<char>& result, int remainingElementsCount) const;

public:
    PMTree(const std::vector<char>& input);
    int factorial(int n) const;
    std::vector<std::vector<char>> generateAll() const;
    bool findPermByCountingPublic(int target, std::vector<char>& result) const;
    bool findPermByNavigatingPublic(int index, std::vector<char>& result) const;
    int getElementsSize() const { return static_cast<int>(elements.size()); }
    int getFactorial(int n) const { return factorial(n); }
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif// INCLUDE_TREE_H_
