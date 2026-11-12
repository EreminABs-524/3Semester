#include <iostream>
#include <string>
#include "dbms.h"
using namespace std;

int main(int argc, char** argv) {
    string filename = "file.data";
    string query;

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) filename = argv[++i];
        else if (arg == "--query" && i + 1 < argc) query = argv[++i];
    }

    DBMS db(filename);
    db.load();

    if (!query.empty()) {
        db.execute(query);
        db.save();
    } else {
        string line;
        while (getline(cin, line)) {
            if (line.empty()) continue;
            db.execute(line);
            db.save();
        }
    }
    return 0;
}