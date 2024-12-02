#include "dualLinkedList.h"
using namespace std;

void dualLinkedList::addFirstElementDL(string value) {
    NodeDL* newNode = new NodeDL{value, NULL, NULL};
    if ( head == NULL ) {
        head = newNode;
        tail = newNode;
        return;
    }
    newNode -> next = head;
    head -> prev = newNode;
    head = newNode;
}
void dualLinkedList::addLastElementDL(string value) {
    NodeDL* newNode = new NodeDL{value, NULL, NULL};
    if ( tail == NULL ) {
        head = newNode;
        tail = newNode;
        return;
    }
    newNode -> prev = tail;
    tail -> next = newNode;
    tail = newNode;
    //list -> next = list -> tail;
}
void dualLinkedList::deleteLastElementDL() {
    if ( head == NULL ) {
        cout << "list is empty";
        return;
    }
    if ( head == tail ) {
        delete head;
        return;
    }
    tail -> prev -> next = NULL;
    delete tail;
}
void dualLinkedList::deleteFirstElementDL() {
    if ( head == NULL ) {
        cout << "list is empty";
        return;
    }
    NodeDL* deleteNode = head;
    head = head -> next;
    head -> prev = NULL;
    delete deleteNode;
}
void dualLinkedList::deleteElementByValueDL(string value) {
    if ( head == NULL ) {
        cout << "list is empty";
        return;
    }
    NodeDL* find = head;
    while ( find -> key != value ) {
        find = find -> next;
    }
    find -> prev -> next = find -> next;
    find -> next -> prev = find -> prev;
    find = NULL;
    delete find;
}
string dualLinkedList::findElementByValueDL(string value) {
    if ( head == NULL ) {
        return "list is empty";
    }
    NodeDL* find = head;
    while ( find -> key != value ) {
        find = find -> next;
        if ( find == NULL ) {
            return "netu";
        }
    }
    return find -> key;
}
void dualLinkedList::printElementsDL() {
    if ( head == NULL ) {
        cout << "list is empty";
        return;
    }
    NodeDL* newNode = head;
    while ( newNode != NULL ) {
        cout << newNode -> key << " ";
        newNode = newNode -> next;
    }
}
string dualLinkedList::findElementByIndex(int index) {
    if ( head == NULL ) {
        return "list is empty";
    }
    NodeDL* newNode = head;
    for ( int i = 0; i < index; i ++ ) {
        newNode = newNode -> next;
    }
    return newNode -> key;
}
void dualLinkedList::parseListDL(string line) {
    string newLine;
    for ( auto i : line ) {
        if ( i == ',' ) {
            continue;
        }
        if ( i == ' '  ) {
            addLastElementDL(newLine);
            newLine = "";
        }
        else { 
            newLine += i;
        }
    }
    addLastElementDL(newLine);
}
void dualLinkedList::loadFromFileListDL(string file) {
    string line;
    ifstream fileInput(file);
    getline(fileInput,  line);
    if ( line == "" ) {
        return;
    }
    parseListDL(line);
}
void dualLinkedList::saveToFileListDL(string file) {
    NodeDL* newNode = head;
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


void DoubleLinkedList(char* argv[]) {
    dualLinkedList list;
    singleList commandLine;
    string fileName = argv[2];
    list.loadFromFileListDL(fileName);
    commandLine.parseList(argv[4]);
    string command = commandLine.findElementByIndex(0);
    if ( command == "DLPUSHT" ) {
        string value = commandLine.findElementByIndex(2);
        list.addLastElementDL(value);
    }
    else if ( command == "DLPUSHH" ) {
        string value = commandLine.findElementByIndex(2);
        list.addFirstElementDL(value);
    }
    else if ( command == "DLDELH" ) {
        list.deleteFirstElementDL();
    }
    else if ( command == "DLDELT" ) {
        list.deleteLastElementDL();
    }
    else if ( command == "DLDELV" ) {
        string value = commandLine.findElementByIndex(2);
        list.deleteElementByValueDL(value);
    }
    else if ( command == "LFIND" ) {
        string value = commandLine.findElementByIndex(2);
        list.findElementByValueDL(value);
    }
    list.saveToFileListDL(fileName);
    list.printElementsDL();
}