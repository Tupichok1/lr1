#include "dualLinkedList.h"
#include "singleLinkedList.h"

struct queue {
    dualLinkedList node;
    int sizeOfQueue();
    void pushQueue(std::string value);
    void popQueue();
    void printQueue();
    void loadFromFileQueue(std::string fileName);
    void saveToFileQueue(std::string fileName) ;
};

void Queue(char* argv[]);