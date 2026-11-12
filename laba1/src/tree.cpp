#include "tree.h"
#include <queue>
using namespace std;

TNode::TNode(int v) : val(v), left(nullptr), right(nullptr) {}

BST::~BST() { clear(); }

void BST::clearRec(TNode* n) {
    if (!n) return;
    clearRec(n->left);
    clearRec(n->right);
    delete n;
}

void BST::clear() {
    clearRec(root);
    root = nullptr;
}

TNode* BST::insertRec(TNode* n, int val) {
    if (!n) return new TNode(val);
    if (val < n->val) n->left = insertRec(n->left, val);
    else if (val > n->val) n->right = insertRec(n->right, val);
    return n;
}

void BST::insert(int val) { root = insertRec(root, val); }

bool BST::searchRec(TNode* n, int val) const {
    if (!n) return false;
    if (val == n->val) return true;
    if (val < n->val) return searchRec(n->left, val);
    return searchRec(n->right, val);
}

bool BST::search(int val) const { return searchRec(root, val); }

bool BST::isFullRec(TNode* n) const {
    if (!n) return true;
    if ((n->left && !n->right) || (!n->left && n->right)) return false;
    return isFullRec(n->left) && isFullRec(n->right);
}

bool BST::isFull() const { return isFullRec(root); }

void BST::printLevelOrder() const {
    if (!root) { cout << "EMPTY\n"; return; }
    queue<TNode*> q;
    q.push(root);
    while (!q.empty()) {
        TNode* cur = q.front(); q.pop();
        if (cur) {
            cout << cur->val << " ";
            q.push(cur->left);
            q.push(cur->right);
        } else {
            cout << "# ";
        }
    }
    cout << "\n";
}

void BST::saveLevelOrder(ostream& os) const {
    if (!root) { os << "0"; return; }
    vector<string> tokens;
    queue<TNode*> q;
    q.push(root);
    while (!q.empty()) {
        TNode* cur = q.front(); q.pop();
        if (cur) {
            tokens.push_back(to_string(cur->val));
            q.push(cur->left);
            q.push(cur->right);
        } else {
            tokens.push_back("#");
        }
    }
    os << tokens.size();
    for (auto& s : tokens) os << " " << s;
}

void BST::load(const vector<string>& tokens) {
    clear();
    if (tokens.empty() || tokens[0] == "#") return;
    root = new TNode(stoi(tokens[0]));
    queue<TNode*> q;
    q.push(root);
    size_t i = 1;
    while (!q.empty() && i < tokens.size()) {
        TNode* cur = q.front(); q.pop();
        if (i < tokens.size()) {
            if (tokens[i] != "#") { 
                cur->left = new TNode(stoi(tokens[i]));
                q.push(cur->left); 
            }
            i++;
        }
        if (i < tokens.size()) {
            if (tokens[i] != "#") { 
                cur->right = new TNode(stoi(tokens[i]));
                q.push(cur->right); 
            }
            i++;
        }
    }
}