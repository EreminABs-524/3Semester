#include "doublyList.h"
using namespace std;

DNode::DNode(const string& v) : val(v), prev(nullptr), next(nullptr) {}

DoublyList::~DoublyList() { clear(); }

void DoublyList::clear() {
    while (head) { DNode* t = head; head = head->next; delete t; }
    tail = nullptr; sz = 0;
}

void DoublyList::push(const string& val, const string& mode, const string& ref) {
    DNode* node = new DNode(val);
    if (mode == "head") {
        node->next = head;
        if (head) head->prev = node;
        head = node;
        if (!tail) tail = node;
    } else if (mode == "tail") {
        if (!head) head = tail = node;
        else { tail->next = node; node->prev = tail; tail = node; }
    } else if (mode == "before") {
        if (!head) { head = tail = node; }
        else if (head->val == ref) { node->next = head; head->prev = node; head = node; }
        else {
            DNode* cur = head;
            while (cur && cur->val != ref) cur = cur->next;
            if (cur) {
                node->prev = cur->prev;
                node->next = cur;
                if (cur->prev) cur->prev->next = node;
                else head = node;
                cur->prev = node;
            } else { delete node; cout << "NOT_FOUND\n"; return; }
        }
    } else if (mode == "after") {
        DNode* cur = head;
        while (cur && cur->val != ref) cur = cur->next;
        if (cur) {
            node->prev = cur;
            node->next = cur->next;
            if (cur->next) cur->next->prev = node;
            else tail = node;
            cur->next = node;
        } else { delete node; cout << "NOT_FOUND\n"; return; }
    } else { delete node; cout << "BAD_MODE\n"; return; }
    sz++;
}

bool DoublyList::del(const string& mode, const string& ref) {
    if (!head) return false;
    if (mode == "head") {
        DNode* t = head; head = head->next; if (head) head->prev = nullptr; else tail = nullptr; delete t; sz--; return true;
    } else if (mode == "tail") {
        DNode* t = tail; tail = tail->prev; if (tail) tail->next = nullptr; else head = nullptr; delete t; sz--; return true;
    } else if (mode == "value") {
        DNode* cur = head;
        while (cur && cur->val != ref) cur = cur->next;
        if (cur) {
            if (cur->prev) cur->prev->next = cur->next; else head = cur->next;
            if (cur->next) cur->next->prev = cur->prev; else tail = cur->prev;
            delete cur; sz--; return true;
        }
        return false;
    } else if (mode == "before") {
        DNode* cur = head;
        while (cur && cur->val != ref) cur = cur->next;
        if (cur && cur->prev) {
            DNode* t = cur->prev;
            if (t->prev) t->prev->next = cur; else head = cur;
            cur->prev = t->prev;
            delete t; sz--; return true;
        }
        return false;
    } else if (mode == "after") {
        DNode* cur = head;
        while (cur && cur->val != ref) cur = cur->next;
        if (cur && cur->next) {
            DNode* t = cur->next;
            cur->next = t->next;
            if (t->next) t->next->prev = cur; else tail = cur;
            delete t; sz--; return true;
        }
        return false;
    }
    return false;
}

string DoublyList::getHead() const { return head ? head->val : "EMPTY"; }
string DoublyList::getTail() const { return tail ? tail->val : "EMPTY"; }

string DoublyList::getIndex(int idx) const {
    DNode* cur = head; int i = 0;
    while (cur) { if (i == idx) return cur->val; cur = cur->next; i++; }
    return "ERROR";
}

int DoublyList::search(const string& val) const {
    DNode* cur = head; int i = 0;
    while (cur) { if (cur->val == val) return i; cur = cur->next; i++; }
    return -1;
}

void DoublyList::print() const {
    for (DNode* cur = head; cur; cur = cur->next) cout << cur->val << " ";
    cout << "\n";
}

void DoublyList::printReverse() const {
    for (DNode* cur = tail; cur; cur = cur->prev) cout << cur->val << " ";
    cout << "\n";
}

void DoublyList::save(ostream& os) const {
    os << sz;
    for (DNode* cur = head; cur; cur = cur->next) os << " " << cur->val;
}