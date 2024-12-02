#include <iostream>
#include <string>
#include <fstream>
#include "singleLinkedList.h"

struct NodeBT {
    std::string key;
    NodeBT* left = NULL;
    NodeBT* right = NULL;
};

struct NodeCT {
    NodeBT* key;
    NodeCT* next;
    void addLastElementCT(NodeCT* &node, NodeBT* newElement);
};
int countOfSymbols(std::string value);
NodeBT* insertElement(NodeBT* &tree, std::string value);
void searchElementBT(NodeBT* tree, std::string value, bool& flag);
NodeBT* lift(NodeBT* tree);
NodeBT* deleteNodeBT(NodeBT* tree, std::string value);
bool isCompleteTree(NodeBT* tree);
void printTree(NodeBT* tree, bool& head);
void parseListBT(NodeBT* &tree, Node* &node, std::string line);
void loadFromFileListBT(NodeBT* &tree, Node* &node, std::string file);
void saveToFileListBT(Node* node, std::string file);
void CompleteBinaryTree(char* argv[]);