#include "hashMap.h"
using namespace std;

int hashTable::hashFunc(string key) {
    int sum = 0;
    for ( auto i : key ) {
        sum += int(i);
    }
    return sum % SIZEHM;
}
void hashTable::initTable() {
    table = new hashNode*[SIZEHM];
    for ( int i = 0; i < SIZEHM; i ++ ) {
        table[i] = NULL;
    }
}
void hashTable::addLastValue(singleList &forSave, string value, string key) {
    string saveElement;
    if ( key != "" and value != "" ) {
        saveElement = key + "-" + value;
    }
    else {
        return;
    }
    forSave.addLastElement(saveElement);
    int hashed = hashFunc(key);
    hashNode* newNode = new hashNode{key, value, NULL};
    if ( table[hashed] == NULL ) {
        table[hashed] = newNode;
        return;
    }
    else {
        hashNode* last = table[hashed];
        if ( last -> key == key ) {
            last -> value = value;
            return;
        }
        while ( last -> next != NULL ) {
            if ( last -> key == key ) {
                last -> value = value;
                return;
            }
            last = last -> next;
        }
        last -> next = newNode;
    }
}
void hashTable::deleteElement(singleList &forSave, string value, string key) {
    string saveElement = key + "-" + value;
    int hashed = hashFunc(key);
    hashNode* deleteNode = table[hashed];
    if ( deleteNode -> value == value ) {
        table[hashed] = deleteNode -> next;
        delete deleteNode;
        forSave.deleteByValue(saveElement);
        return;
    }
    deleteNode = table[hashed] -> next;
    hashNode* prev = table[hashed];
    while ( deleteNode -> value != value ) {
        prev = prev -> next;
        deleteNode = deleteNode -> next;
    }
    prev -> next = deleteNode -> next;
    forSave.deleteByValue(saveElement);
    delete deleteNode;
}
void hashTable::printElement(string key) {
    int hashed = hashFunc(key);
    hashNode* entry = table[hashed];
    while ( entry != NULL ) {
        cout << entry -> value << " ";
        entry = entry -> next;
    }
}
void hashTable::parseHashMap(singleList &forSave, string line) {
    string newLine;
    string key, value;
    for ( size_t i = 0; i < line.size(); i ++ ) {
        if ( line[i] == '-' ) {
            key = newLine;
            newLine = "";
            continue;
        }
        if ( line[i] == ',' ) {
            continue;
        }
        if ( line[i] == ' ' ) {
            addLastValue(forSave, newLine, key);
            newLine = "";
            continue;
        }
        newLine += line[i];
    }
    addLastValue(forSave, newLine, key);
}
void hashTable::loadFromFileHash(singleList &forSave, string file) {
    string line;
    ifstream fileInput(file);
    while ( getline(fileInput,  line) ) {
        parseHashMap(forSave, line);
    }
}
void hashTable::saveToFileHash(singleList &forSave, string file) {
    ofstream out;
    out.open(file);
    Node* newNode = forSave.node;
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


void HashMap(char* argv[]) {
    singleList forSave;
    hashTable table;
    table.initTable();
    singleList commandLine;
    string fileName = argv[2];
    table.loadFromFileHash(forSave, fileName);
    commandLine.parseList(argv[4]);
    string command = commandLine.findElementByIndex(0);
    if ( command == "HSET" ) {
        string key = commandLine.findElementByIndex(2);
        string value = commandLine.findElementByIndex(3);
        table.addLastValue(forSave, value, key);
        table.printElement(key);
    }
    else if ( command == "HDEL" ) {
        string key = commandLine.findElementByIndex(2);
        string value = commandLine.findElementByIndex(3);
        table.deleteElement(forSave, value, key);
    }
    else if ( command == "HGET" ) {
        string key = commandLine.findElementByIndex(2);
        table.printElement(key);
    }
    table.saveToFileHash(forSave, fileName);
} 