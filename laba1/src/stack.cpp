#include "stack.h"
using namespace std;

StNode::StNode(const string& v) : val(v), next(nullptr) {}

Stack::Stack() : head(nullptr), size(0) {}

Stack::~Stack() {
    while (head) {
        StNode* temp = head;
        head = head->next;
        delete temp;
    }
}

Stack::Stack(Stack&& other) noexcept 
    : head(other.head), size(other.size) {
    other.head = nullptr;
    other.size = 0;
}

Stack& Stack::operator=(Stack&& other) noexcept {
    if (this != &other) {
        while (head) {
            StNode* temp = head;
            head = head->next;
            delete temp;
        }
        head = other.head;
        size = other.size;
        other.head = nullptr;
        other.size = 0;
    }
    return *this;
}

void Stack::push(const string& val) {
    StNode* node = new StNode(val);
    node->next = head;
    head = node;
    size++;
}

string Stack::pop() {
    if (!head) return "EMPTY";
    StNode* temp = head;
    string val = head->val;
    head = head->next;
    delete temp;
    size--;
    return val;
}

string Stack::top() const {
    if (!head) return "EMPTY";
    return head->val;
}

void Stack::print() const {
    StNode* cur = head;
    while (cur) {
        cout << cur->val << " ";
        cur = cur->next;
    }
    cout << "\n";
}

void Stack::save(ostream& os) const {
    os << size;
    if (size == 0) return;
    string* tempArr = new string[size];
    StNode* cur = head;
    int i = size - 1;
    while (cur) {
        tempArr[i--] = cur->val;
        cur = cur->next;
    }
    for (int j = 0; j < size; j++) {
        os << " " << tempArr[j];
    }
    delete[] tempArr;
}

void Stack::load(istream& is, int n) {
    while (head) {
        StNode* temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
    size = 0;
    
    string* tempArr = new string[n];
    for (int i = 0; i < n; i++) {
        is >> tempArr[i];
    }
    for (int i = n - 1; i >= 0; i--) {
        push(tempArr[i]);
    }
    delete[] tempArr;
}