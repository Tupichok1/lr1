#include <iostream>
#include <string>
#include <fstream>
#include "singleLinkedList.h"
struct stack{
    singleList list;
    bool isEmpty();
    void pushBack(std::string value);
    void popElement();
    void printStack();
    void parseListStack(std::string line);
    void loadFromFileStack(std::string file);
    void saveToFileStack(std::string file);
};

void Stack(char* argv[]);