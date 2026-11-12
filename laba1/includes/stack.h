#pragma once
#include <string>
#include <iostream>

struct StNode {
    std::string val;
    StNode* next;
    StNode(const std::string& v);
};

class Stack {
private:
    StNode* head;
    int size;

public:
    Stack();
    ~Stack();
    
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
    
    Stack(Stack&& other) noexcept;
    Stack& operator=(Stack&& other) noexcept;

    void push(const std::string& val);
    std::string pop();
    std::string top() const;
    void print() const;
    void save(std::ostream& os) const;
    void load(std::istream& is, int n);
};