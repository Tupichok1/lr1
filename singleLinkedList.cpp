#include "singleLinkedList.h"
using namespace std;

void singleList::deleteFirstNode() {
    if ( node == NULL ) {
        cout << "list is empty";
        return;
    }
    Node* deleteNode = node;
    node = deleteNode -> next;
    delete deleteNode;
}
void singleList::deleteLastNode() {
    if ( node == NULL ) {
        cout << "list is empty";
        return;
    }
    if ( node -> next == NULL ) {
        node = NULL;
        return;
    }
    Node* deleteNode = node -> next;
    Node* prev = node;
    while ( deleteNode -> next != NULL ) {
        prev = prev -> next;
        deleteNode = deleteNode -> next;
    }
    prev -> next = NULL;
    delete deleteNode;
}
void singleList::deleteByValue(string value) {
    if ( node == NULL ) {
        cout << "list is empty";
        return;
    }
    if ( node -> key == value ) {
        Node* deleteNode = node;
        node = node -> next;
        delete deleteNode;
        return;
    }
    Node* deleteNode = node -> next;
    Node* prev = node;
    while ( deleteNode -> key != value ) {
        prev = prev -> next;
        deleteNode = deleteNode -> next;
        if ( deleteNode == NULL ) {
            return;
        }
    }
    prev -> next = deleteNode -> next;
    delete deleteNode;
}
void singleList::addLastElement(string newElement) {
    Node* newNode = new Node{newElement, NULL};
    if ( node == NULL ) {
        node = newNode;
        return;
    }
    Node* last = node;
    while ( last -> next != NULL ) {
        last = last -> next;
    }
    last -> next = newNode;
}
void singleList::addFirstElement(string next) {
    Node* newNode = new Node{next, NULL};
    newNode -> next = node;
    node = newNode;
}
void singleList::printList() {
    while ( node != NULL ) {
        cout << node -> key << " ";
        node = node -> next;
    }
}
string singleList::findElementNode(string value) {
    Node* newNode = node;
    while ( newNode -> key != value ) {
        newNode = newNode -> next;
        if ( newNode == NULL ) {
            return "doesnt exist";
        }
    }
    return "exist";
}
string singleList::findElementByIndex(int index) {
    Node* newNode = node;
    for ( int i = 0; i < index; i ++ ) {
        newNode = newNode -> next;
    }
    return newNode -> key;
}
int singleList::sizeOfList() {
    int size = 0;
    Node* newNode = node;
    while ( newNode != NULL ) {
        size += 1;
        newNode = newNode -> next;
    }
    return size;
}
void singleList::parseList(string line) {
    string newLine;
    for ( auto i : line ) {
        if ( i == ',' or i == '(' or i == ')' or i == '"' ) {
            continue;
        }
        if ( i == ' ' or i == '.' ) {
            addLastElement(newLine);
            newLine = "";
        }
        else { 
            newLine += i;
        }
    }
    addLastElement(newLine);
}
void singleList::loadFromFileList(string file) {
    string line;
    ifstream fileInput(file);
    getline(fileInput,  line);
    parseList(line);
}
void singleList::saveToFileList(string file) {
    Node* newNode = node;
    ofstream out;
    out.open(file);
    while ( newNode != NULL ) {
        if ( newNode -> next == NULL ) {
            out << newNode -> key;
        }
        else {
            out << newNode -> key << " ";
        }
        newNode = newNode -> next;
    }
    out.close();
}


void SingleList(char* argv[]) {
    singleList list;
    singleList commandLine;
    string fileName = argv[2];
    list.loadFromFileList(fileName);
    commandLine.parseList(argv[4]);
    string command = commandLine.findElementByIndex(0);
    if ( command == "LPUSHT" ) {
        string value = commandLine.findElementByIndex(2);
        list.addLastElement(value);
    }
    else if ( command == "LPUSHH" ) {
        string value = commandLine.findElementByIndex(2);
        list.addFirstElement(value);
    }
    else if ( command == "LDELH" ) {
        list.deleteFirstNode();
    }
    else if ( command == "LDELT" ) {
        list.deleteLastNode();
    }
    else if ( command == "LFIND" ) {
        string value = commandLine.findElementByIndex(2);
        cout << list.findElementNode(value) << " ";
    }
    list.saveToFileList(fileName);
    list.printList();
}