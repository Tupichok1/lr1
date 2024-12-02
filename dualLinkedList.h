#ifndef DUAL_H
#define DUAL_H
#include <iostream>
#include <string>
#include <fstream>
#include "singleLinkedList.h"


struct NodeDL {
    std::string key;
    NodeDL* next;
    NodeDL* prev;
};

struct dualLinkedList {
    NodeDL* tail = NULL;
    NodeDL* head = NULL;
    void addFirstElementDL(std::string value);
    void addLastElementDL(std::string value);
    void deleteLastElementDL();
    void deleteFirstElementDL();
    void deleteElementByValueDL(std::string value);
    std::string findElementByValueDL(std::string value);
    void printElementsDL();
    std::string findElementByIndex(int index);
    void parseListDL(std::string line);
    void loadFromFileListDL(std::string file);
    void saveToFileListDL(std::string file);
};

void DoubleLinkedList(char* argv[]);

#endif