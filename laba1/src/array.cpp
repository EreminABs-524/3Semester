#include "array.h"
using namespace std;

Array::Array() : data(nullptr), size(0), capacity(0) {}

Array::~Array() {
    delete[] data;
}

Array::Array(Array&& other) noexcept 
    : data(other.data), size(other.size), capacity(other.capacity) {
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}
Array& Array::operator=(Array&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        size = other.size;
        capacity = other.capacity;
        
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

void Array::resize(int new_capacity) {
    string* new_data = new string[new_capacity];
    for (int i = 0; i < size; ++i) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

void Array::push(const string& val, int idx) {
    if (size >= capacity) {
        int new_cap = (capacity == 0) ? 1 : capacity * 2;
        resize(new_cap);
    }
    if (idx < 0 || idx >= size) {
        data[size] = val;
        size++;
    } 
    else {
        for (int i = size; i > idx; --i) {
            data[i] = data[i - 1];
        }
        data[idx] = val;
        size++;
    }
}

bool Array::del(int idx) {
    if (idx < 0 || idx >= size) return false;
    
    for (int i = idx; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    size--;
    return true;
}

string Array::get(int idx) const {
    if (idx < 0 || idx >= size) return "ERROR";
    return data[idx];
}

int Array::len() const {
    return size;
}

bool Array::replace(int idx, const string& val) {
    if (idx < 0 || idx >= size) return false;
    data[idx] = val;
    return true;
}

void Array::print() const {
    for (int i = 0; i < size; ++i) {
        cout << data[i] << " ";
    }
    cout << "\n";
}

void Array::save(ostream& os) const {
    os << size;
    for (int i = 0; i < size; ++i) {
        os << " " << data[i];
    }
}

void Array::load(istream& is, int n) {
    delete[] data;
    
    data = new string[n];
    size = n;
    capacity = n;
    
    for (int i = 0; i < n; ++i) {
        is >> data[i];
    }
}