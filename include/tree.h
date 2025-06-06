// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PMTree {
private:
    struct Node {
        char value;
        std::vector<std::unique_ptr<Node>> children;
        Node(char v) : value(v) {}
    };

    std::unique_ptr<Node> root;
    std::vector<char> elements;
    int factorial(int n) const;
    void buildTree(std::unique_ptr<Node>& parent, const std::vector<char>& remaining);
    void traverseTree(Node* node, std::vector<char>& path, std::vector<std::vector<char>>& result) const;
    bool findPermByCounting(Node* node, std::vector<char>& path, int& count, int target, std::vector<char>& result) const;
    bool findPermByNavigating(Node* node, std::vector<char>& path, int& remaining, std::vector<char>& result) const;

public:
    explicit PMTree(const std::vector<char>& input);
    std::vector<std::vector<char>> generateAll() const;
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif // INCLUDE_TREE_H_
