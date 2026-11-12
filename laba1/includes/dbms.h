#pragma once
#include <string>
#include <map>
#include <memory>
#include "array.h"
#include "singlyList.h"
#include "doublyList.h"
#include "stack.h"
#include "queue.h"
#include "tree.h"

class DBMS {
    std::string filename;
    std::map<std::string, std::unique_ptr<Array>> arrays;
    std::map<std::string, std::unique_ptr<SinglyList>> flists;
    std::map<std::string, std::unique_ptr<DoublyList>> llists;
    std::map<std::string, std::unique_ptr<Stack>> stacks;
    std::map<std::string, std::unique_ptr<Queue>> queues;
    std::map<std::string, std::unique_ptr<BST>> trees;

    void printAny(const std::string& name);

public:
    explicit DBMS(const std::string& fname);

    void load();
    void save();
    void execute(const std::string& line);
};