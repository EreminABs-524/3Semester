#pragma once
#include <string>
#include <iostream>

struct SNode {
    std::string val;
    SNode* next;
    explicit SNode(const std::string& v);
};

class SinglyList {
public:
    SNode* head = nullptr;
    SNode* tail = nullptr;
    int sz = 0;

    SinglyList() = default;
    ~SinglyList();
    SinglyList(const SinglyList&) = delete;
    SinglyList& operator=(const SinglyList&) = delete;

    void clear();
    void push(const std::string& val, const std::string& mode, const std::string& ref = "");
    bool del(const std::string& mode, const std::string& ref = "");
    std::string getHead() const;
    std::string getTail() const;
    std::string getIndex(int idx) const;
    int search(const std::string& val) const;
    void print() const;
    void save(std::ostream& os) const;
};