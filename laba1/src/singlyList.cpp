#include "singlyList.h"
using namespace std;

SNode::SNode(const string& v) : val(v), next(nullptr) {}

SinglyList::~SinglyList() { clear(); }

void SinglyList::clear() {
    while (head) { SNode* t = head; head = head->next; delete t; }
    tail = nullptr; sz = 0;
}

void SinglyList::push(const string& val, const string& mode, const string& ref) {
    SNode* node = new SNode(val);
    if (mode == "head") {
        node->next = head; head = node; if (!tail) tail = node;
    } else if (mode == "tail") {
        if (!head) head = tail = node;
        else { tail->next = node; tail = node; }
    } else if (mode == "before") {
        if (!head) { head = tail = node; }
        else if (head->val == ref) { node->next = head; head = node; }
        else {
            SNode* cur = head;
            while (cur->next && cur->next->val != ref) cur = cur->next;
            if (cur->next) { node->next = cur->next; cur->next = node; }
            else { delete node; cout << "NOT_FOUND\n"; return; }
        }
    } else if (mode == "after") {
        SNode* cur = head;
        while (cur && cur->val != ref) cur = cur->next;
        if (cur) { node->next = cur->next; cur->next = node; if (tail == cur) tail = node; }
        else { delete node; cout << "NOT_FOUND\n"; return; }
    } else { delete node; cout << "BAD_MODE\n"; return; }
    sz++;
}

bool SinglyList::del(const string& mode, const string& ref) {
    if (!head) return false;
    if (mode == "head") {
        SNode* t = head; head = head->next; if (!head) tail = nullptr; delete t; sz--; return true;
    } else if (mode == "tail") {
        if (head == tail) { delete head; head = tail = nullptr; sz--; return true; }
        SNode* cur = head; while (cur->next != tail) cur = cur->next;
        delete tail; tail = cur; tail->next = nullptr; sz--; return true;
    } else if (mode == "value") {
        if (head->val == ref) { SNode* t = head; head = head->next; if (!head) tail = nullptr; delete t; sz--; return true; }
        SNode* cur = head;
        while (cur->next && cur->next->val != ref) cur = cur->next;
        if (cur->next) { SNode* t = cur->next; cur->next = t->next; if (t == tail) tail = cur; delete t; sz--; return true; }
        return false;
    } else if (mode == "before") {
        if (head->val == ref) return false;
        SNode* cur = head;
        while (cur->next && cur->next->val != ref) cur = cur->next;
        if (cur->next) { SNode* t = cur->next; cur->next = t->next; if (t == tail) tail = cur; delete t; sz--; return true; }
        return false;
    } else if (mode == "after") {
        SNode* cur = head;
        while (cur && cur->val != ref) cur = cur->next;
        if (cur && cur->next) { SNode* t = cur->next; cur->next = t->next; if (t == tail) tail = cur; delete t; sz--; return true; }
        return false;
    }
    return false;
}

string SinglyList::getHead() const { return head ? head->val : "EMPTY"; }
string SinglyList::getTail() const { return tail ? tail->val : "EMPTY"; }

string SinglyList::getIndex(int idx) const {
    SNode* cur = head; int i = 0;
    while (cur) { if (i == idx) return cur->val; cur = cur->next; i++; }
    return "ERROR";
}

int SinglyList::search(const string& val) const {
    SNode* cur = head; int i = 0;
    while (cur) { if (cur->val == val) return i; cur = cur->next; i++; }
    return -1;
}

void SinglyList::print() const {
    for (SNode* cur = head; cur; cur = cur->next) cout << cur->val << " ";
    cout << "\n";
}

void SinglyList::save(ostream& os) const {
    os << sz;
    for (SNode* cur = head; cur; cur = cur->next) os << " " << cur->val;
}