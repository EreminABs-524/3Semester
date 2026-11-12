#pragma once
#include <string>
#include <iostream>

struct DNode {
    std::string val;
    DNode* prev;
    DNode* next;
    explicit DNode(const std::string& v);
};

class DoublyList {
public:
    DNode* head = nullptr;
    DNode* tail = nullptr;
    int sz = 0;

    DoublyList() = default;
    ~DoublyList();
    DoublyList(const DoublyList&) = delete;
    DoublyList& operator=(const DoublyList&) = delete;

    void clear();
    void push(const std::string& val, const std::string& mode, const std::string& ref = "");
    bool del(const std::string& mode, const std::string& ref = "");
    std::string getHead() const;
    std::string getTail() const;
    std::string getIndex(int idx) const;
    int search(const std::string& val) const;
    void print() const;
    void printReverse() const;
    void save(std::ostream& os) const;
};