#include "dbms.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

DBMS::DBMS(const string& fname) : filename(fname) {}

void DBMS::load() {
    ifstream in(filename);
    if (!in) return;
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        char type; string name; int n;
        iss >> type >> name >> n;
        if (type == 'M') {
            auto arr = make_unique<Array>();
            arr->load(iss, n);
            arrays[name] = move(arr);
        } else if (type == 'F') {
            auto lst = make_unique<SinglyList>();
            for (int i = 0; i < n; i++) { string v; iss >> v; lst->push(v, "tail"); }
            flists[name] = move(lst);
        } else if (type == 'L') {
            auto lst = make_unique<DoublyList>();
            for (int i = 0; i < n; i++) { string v; iss >> v; lst->push(v, "tail"); }
            llists[name] = move(lst);
        } else if (type == 'S') {
            auto st = make_unique<Stack>();
            st->load(iss, n);
            stacks[name] = move(st);
        } else if (type == 'Q') {
            auto q = make_unique<Queue>();
            q->load(iss, n);
            queues[name] = move(q);
        } else if (type == 'T') {
            auto tree = make_unique<BST>();
            vector<string> tokens;
            for (int i = 0; i < n; i++) { string v; iss >> v; tokens.push_back(v); }
            tree->load(tokens);
            trees[name] = move(tree);
        }
    }
}

void DBMS::save() {
    ofstream out(filename);
    for (auto& p : arrays)  { out << "M " << p.first << " "; p.second->save(out); out << "\n"; }
    for (auto& p : flists)  { out << "F " << p.first << " "; p.second->save(out); out << "\n"; }
    for (auto& p : llists)  { out << "L " << p.first << " "; p.second->save(out); out << "\n"; }
    for (auto& p : stacks)  { out << "S " << p.first << " "; p.second->save(out); out << "\n"; }
    for (auto& p : queues)  { out << "Q " << p.first << " "; p.second->save(out); out << "\n"; }
    for (auto& p : trees)   { out << "T " << p.first << " "; p.second->saveLevelOrder(out); out << "\n"; }
}

void DBMS::printAny(const string& name) {
    if (arrays.count(name))  { arrays[name]->print(); return; }
    if (flists.count(name))  { flists[name]->print(); return; }
    if (llists.count(name))  { llists[name]->print(); return; }
    if (stacks.count(name))  { stacks[name]->print(); return; }
    if (queues.count(name))  { queues[name]->print(); return; }
    if (trees.count(name))   { trees[name]->printLevelOrder(); return; }
    cout << "NOT_FOUND\n";
}

void DBMS::execute(const string& line) {
    istringstream iss(line);
    string cmd; iss >> cmd;

    if (cmd == "PRINT") {
        string name; iss >> name;
        printAny(name);
        return;
    }
    if (cmd == "SAVE") { save(); cout << "OK\n"; return; }
    if (cmd == "LOAD") { load(); cout << "OK\n"; return; }
    if (cmd == "ISFULL" || cmd == "TISFULL") {
        string name; iss >> name;
        if (trees.count(name)) cout << (trees[name]->isFull() ? "TRUE" : "FALSE") << "\n";
        else cout << "FALSE\n";
        return;
    }
    if (cmd == "ISMEMBER") {
        string name; int val; iss >> name >> val; // ИЗМЕНЕНО
        if (trees.count(name)) cout << (trees[name]->search(val) ? "TRUE" : "FALSE") << "\n";
        else cout << "FALSE\n";
        return;
    }

    char type = cmd[0];
    string op = cmd.substr(1);
    string name; iss >> name;

    if (type == 'M') {
        if (op == "PUSH") {
            string val; iss >> val;
            int idx = -1;
            if (!(iss >> idx)) idx = -1;
            if (!arrays[name]) arrays[name] = make_unique<Array>();
            arrays[name]->push(val, idx);
            cout << val << "\n";
        } else if (op == "DEL") {
            int idx; iss >> idx;
            bool ok = arrays[name] && arrays[name]->del(idx);
            cout << (ok ? "OK" : "ERROR") << "\n";
        } else if (op == "GET") {
            int idx; iss >> idx;
            if (arrays[name]) cout << arrays[name]->get(idx) << "\n";
            else cout << "ERROR\n";
        } else if (op == "LEN") {
            if (arrays[name]) cout << arrays[name]->len() << "\n";
            else cout << "0\n";
        } else if (op == "REPLACE") {
            int idx; string val; iss >> idx >> val;
            bool ok = arrays[name] && arrays[name]->replace(idx, val);
            cout << (ok ? "OK" : "ERROR") << "\n";
        }
    } else if (type == 'F') {
        if (op == "PUSH") {
            string val, mode, ref;
            iss >> val >> mode;
            if (mode == "before" || mode == "after") iss >> ref;
            if (!flists[name]) flists[name] = make_unique<SinglyList>();
            flists[name]->push(val, mode, ref);
            cout << val << "\n";
        } else if (op == "DEL") {
            string mode, ref;
            iss >> mode;
            if (mode == "before" || mode == "after" || mode == "value") iss >> ref;
            bool ok = flists[name] && flists[name]->del(mode, ref);
            cout << (ok ? "OK" : "ERROR") << "\n";
        } else if (op == "GET") {
            string mode; iss >> mode;
            if (!flists[name]) { cout << "EMPTY\n"; return; }
            if (mode == "all") flists[name]->print();
            else if (mode == "head") cout << flists[name]->getHead() << "\n";
            else if (mode == "tail") cout << flists[name]->getTail() << "\n";
            else if (mode == "index") { int idx; iss >> idx; cout << flists[name]->getIndex(idx) << "\n"; }
        } else if (op == "SEARCH") {
            string val; iss >> val;
            if (flists[name]) cout << flists[name]->search(val) << "\n";
            else cout << "-1\n";
        }
    } else if (type == 'L') {
        if (op == "PUSH") {
            string val, mode, ref;
            iss >> val >> mode;
            if (mode == "before" || mode == "after") iss >> ref;
            if (!llists[name]) llists[name] = make_unique<DoublyList>();
            llists[name]->push(val, mode, ref);
            cout << val << "\n";
        } else if (op == "DEL") {
            string mode, ref;
            iss >> mode;
            if (mode == "before" || mode == "after" || mode == "value") iss >> ref;
            bool ok = llists[name] && llists[name]->del(mode, ref);
            cout << (ok ? "OK" : "ERROR") << "\n";
        } else if (op == "GET") {
            string mode; iss >> mode;
            if (!llists[name]) { cout << "EMPTY\n"; return; }
            if (mode == "all") llists[name]->print();
            else if (mode == "reverse") llists[name]->printReverse();
            else if (mode == "head") cout << llists[name]->getHead() << "\n";
            else if (mode == "tail") cout << llists[name]->getTail() << "\n";
            else if (mode == "index") { int idx; iss >> idx; cout << llists[name]->getIndex(idx) << "\n"; }
        } else if (op == "SEARCH") {
            string val; iss >> val;
            if (llists[name]) cout << llists[name]->search(val) << "\n";
            else cout << "-1\n";
        }
    }else if (type == 'S') {
        if (op == "PUSH") {
            string val; iss >> val;
            if (!stacks[name]) stacks[name] = make_unique<Stack>();
            stacks[name]->push(val);
            cout << val << "\n";
        } else if (op == "POP") {
            if (stacks[name]) cout << stacks[name]->pop() << "\n";
            else cout << "EMPTY\n";
        } else if (op == "GET") {
            if (stacks[name]) cout << stacks[name]->top() << "\n";
            else cout << "EMPTY\n";
        }
    }else if (type == 'Q') {
        if (op == "PUSH") {
            string val; iss >> val;
            if (!queues[name]) queues[name] = make_unique<Queue>();
            queues[name]->push(val);
            cout << val << "\n";
        } else if (op == "POP") {
            if (queues[name]) cout << queues[name]->pop() << "\n";
            else cout << "EMPTY\n";
        } else if (op == "GET") {
            if (queues[name]) cout << queues[name]->front() << "\n";
            else cout << "EMPTY\n";
        }
    }else if (type == 'T') {
        if (op == "INSERT") {
            int val; iss >> val;
            if (!trees[name]) trees[name] = make_unique<BST>();
            trees[name]->insert(val);
            cout << val << "\n";
        } else if (op == "GET") {
            int val; iss >> val; 
            if (trees[name]) cout << (trees[name]->search(val) ? "TRUE" : "FALSE") << "\n";
            else cout << "FALSE\n";
        }
    } else {
        cout << "UNKNOWN_COMMAND\n";
    }
}