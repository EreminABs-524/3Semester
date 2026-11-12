#pragma once
#include <string>
#include <iostream>

class Array {
private:
    std::string* data;
    int size;
    int capacity;       
    void resize(int new_capacity);

public:
    Array();
    ~Array();

    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;

    Array(Array&& other) noexcept;
    Array& operator=(Array&& other) noexcept;

    void push(const std::string& val, int idx = -1);
    bool del(int idx);
    std::string get(int idx) const;
    int len() const;
    bool replace(int idx, const std::string& val);
    void print() const;
    
    void save(std::ostream& os) const;
    void load(std::istream& is, int n);
};