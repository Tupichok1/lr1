#include "stack.h"

using namespace std;
bool stack::isEmpty() {
    return list.node == NULL;
}
void stack::pushBack(string value) {
    list.addFirstElement(value);
}
void stack::popElement() {
    if ( isEmpty() ) {
        return;
    }
    else {
        list.deleteFirstNode();
    }
}
void stack::printStack() {
    list.printList();
}
void stack::parseListStack(string line) {
    string newLine;
    for ( auto i : line ) {
        if ( i == ',' ) {
            continue;
        }
        if ( i == ' '  ) {
            list.addFirstElement(newLine);
            newLine = "";
        }
        else { 
            newLine += i;
        }
    }
    list.addFirstElement(newLine);
}
void stack::loadFromFileStack(string file) {
    string line;
    ifstream fileInput(file);
    getline(fileInput,  line);
    parseListStack(line);
}
void stack::saveToFileStack(string file) {
    ofstream out;
    out.open(file);
    Node* newNode = list.node;
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


void Stack(char* argv[]) {
    stack st;
    singleList commandLine;
    string fileName = argv[2];
    st.loadFromFileStack(fileName);
    commandLine.parseList(argv[4]);
    string command = commandLine.findElementByIndex(0);
    if ( command == "SPUSH" ) {
        string value = commandLine.findElementByIndex(2);
        st.pushBack(value);
        st.printStack();
    }
    else if ( command == "SPOP" ) {
        st.popElement();
        st.printStack();
    }
    else if ( command == "SGET" ) {
        st.printStack();
    }
    st.saveToFileStack(fileName);
}