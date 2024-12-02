#include "queue.h"

using namespace std;

int queue::sizeOfQueue() {
    int size = 0;
    NodeDL* newNode = node.head;
    while ( newNode != NULL ) {
        newNode = newNode -> next;
        size += 1;
    }
    return size;
}
void queue::pushQueue(std::string value) {
    node.addLastElementDL(value);
}
void queue::popQueue() {
    node.deleteFirstElementDL();
}
void queue::printQueue() {
    node.printElementsDL();
}
void queue::loadFromFileQueue(string fileName) {
    node.loadFromFileListDL(fileName);
}
void queue::saveToFileQueue(string fileName) {
    node.saveToFileListDL(fileName);
}

void Queue(char* argv[]) {
    queue qu;
    singleList commandLine;
    string fileName = argv[2];
    qu.loadFromFileQueue(fileName);
    commandLine.parseList(argv[4]);
    string command = commandLine.findElementByIndex(0);
    if ( command == "QPUSH" ) {
        string value = commandLine.findElementByIndex(2);
        qu.pushQueue(value);
        qu.printQueue();
    }
    else if ( command == "QPOP" ) {
        qu.popQueue();
        qu.printQueue();
    }
    else if ( command == "QGET" ) {
        qu.printQueue();
    }
    qu.saveToFileQueue(fileName);
}