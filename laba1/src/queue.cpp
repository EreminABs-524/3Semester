#include "queue.h"
using namespace std;

QNode::QNode(const string& v) : val(v), next(nullptr) {}

Queue::Queue() : head(nullptr), tail(nullptr), size(0) {}

Queue::~Queue() {
    while (head) {
        QNode* temp = head;
        head = head->next;
        delete temp;
    }
}

Queue::Queue(Queue&& other) noexcept 
    : head(other.head), tail(other.tail), size(other.size) {
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}

Queue& Queue::operator=(Queue&& other) noexcept {
    if (this != &other) {
        while (head) {
            QNode* temp = head;
            head = head->next;
            delete temp;
        }
        head = other.head;
        tail = other.tail;
        size = other.size;
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }
    return *this;
}

void Queue::push(const string& val) {
    QNode* node = new QNode(val);
    if (!head) {
        head = tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
    size++;
}

string Queue::pop() {
    if (!head) return "EMPTY";
    QNode* temp = head;
    string val = head->val;
    head = head->next;
    if (!head) tail = nullptr;
    delete temp;
    size--;
    return val;
}

string Queue::front() const {
    if (!head) return "EMPTY";
    return head->val;
}

void Queue::print() const {
    QNode* cur = head;
    while (cur) {
        cout << cur->val << " ";
        cur = cur->next;
    }
    cout << "\n";
}

void Queue::save(ostream& os) const {
    os << size;
    QNode* cur = head;
    while (cur) {
        os << " " << cur->val;
        cur = cur->next;
    }
}

void Queue::load(istream& is, int n) {
    while (head) {
        QNode* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
    for (int i = 0; i < n; i++) {
        string s;
        is >> s;
        push(s);
    }
}