#pragma once
#include <string>
#include <vector>
#include <iostream>

struct TNode {
    int val;
    TNode* left;
    TNode* right;
    explicit TNode(int v); 
};

class BST {
public:
    TNode* root = nullptr;

    BST() = default;
    ~BST();
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    TNode* insertRec(TNode* n, int val);
    void insert(int val); 
    bool searchRec(TNode* n, int val) const;
    bool search(int val) const;
    bool isFullRec(TNode* n) const;
    bool isFull() const;
    void printLevelOrder() const;
    void saveLevelOrder(std::ostream& os) const;
    void load(const std::vector<std::string>& tokens);
    void clearRec(TNode* n);
    void clear();
};