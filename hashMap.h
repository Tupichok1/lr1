#include <string>
#include <iostream>
#include <fstream>
#include "singleLinkedList.h"
#define SIZEHM 80

struct hashNode {
    std::string key = 0;
    std::string value = 0;
    hashNode* next;
};
struct hashTable {
    hashNode** table;
    int hashFunc(std::string key);
    void initTable();
    void addLastValue(singleList &forSave, std::string value, std::string key);
    void deleteElement(singleList &forSave, std::string value, std::string key);
    void printElement(std::string key);
    void parseHashMap(singleList &forSave, std::string line);
    void loadFromFileHash(singleList &forSave, std::string file);
    void saveToFileHash(singleList &forSave, std::string file);
};

void HashMap(char* argv[]);