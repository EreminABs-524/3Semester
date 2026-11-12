#pragma once
#include <string>
#include <iostream>

struct QNode {
    std::string val;
    QNode* next;
    QNode(const std::string& v);
};

class Queue {
private:
    QNode* head;
    QNode* tail;
    int size;

public:
    Queue();
    ~Queue();
    
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
    
    Queue(Queue&& other) noexcept;
    Queue& operator=(Queue&& other) noexcept;

    void push(const std::string& val);
    std::string pop();
    std::string front() const;
    void print() const;
    void save(std::ostream& os) const;
    void load(std::istream& is, int n);
};