#include "completeBinaryTree.h"
using namespace std;

void NodeCT::addLastElementCT(NodeCT* &node, NodeBT* newElement) {
    NodeCT* newNode = new NodeCT{newElement, NULL};
    if ( node == NULL ) {
        node = newNode;
        return;
    }
    NodeCT* last = node;
    while ( last -> next != NULL ) {
        last = last -> next;
    }
    last -> next = newNode;
}

int countOfSymbols(string value) {
    int summa = 0;
    for ( auto i : value ) {
        summa += int(i);
    }
    return summa;
}
NodeBT* createNode(string value) {
    NodeBT* newNode = new NodeBT; 
    newNode -> key = value;
    newNode -> left = NULL;
    newNode -> right = NULL;
    return newNode;
}
NodeBT* insertElement(NodeBT* &tree, string value) {
    if ( tree == NULL ) {
        tree = createNode(value);
    }
    if ( countOfSymbols(value) < countOfSymbols(tree -> key) ) {
        tree -> left = insertElement(tree -> left, value);
    }
    if ( countOfSymbols(value) > countOfSymbols(tree -> key) ) {
        tree -> right = insertElement(tree -> right, value);
    }
    return tree;
}
void searchElementBT(NodeBT* tree, string value, bool& flag) {
    if ( tree != NULL ) {
        if ( flag == true ) {
            return;
        }
        if ( tree -> key == value ) {
            flag = true;
            return;
        }
        if ( countOfSymbols(value) < countOfSymbols(tree -> key) ) {
            searchElementBT(tree -> left, value, flag);
        }
        if ( countOfSymbols(value) > countOfSymbols(tree -> key) ) {
            searchElementBT(tree -> right, value, flag);
        }
    }
    if ( flag == false ) {
        return;
    }
}
NodeBT* lift(NodeBT* tree) {
    NodeBT* node = tree;
    while ( node != NULL or node -> left != NULL ) {
        node = node -> left;
    }
    return node;
}
NodeBT* deleteNodeBT(NodeBT* tree, string value) {
    NodeBT* newTree = tree;
    bool flag = false;
    searchElementBT(newTree, value, flag);
    if ( flag == false ) {
        cout << "element doesnt exist";
        return tree;
    } 
    if ( countOfSymbols(value) < countOfSymbols(tree -> key) ) {
        tree -> left = deleteNodeBT(tree -> left, value);
    }
    if ( countOfSymbols(value) > countOfSymbols(tree -> key) ) {
        tree -> right = deleteNodeBT(tree -> right, value);
    }
    if ( countOfSymbols(value) == countOfSymbols(tree -> key) ) {
        if ( tree -> left == NULL ) {
            NodeBT* deleteNode = tree -> right;
            delete tree;
            return deleteNode;
        }
        else {
            NodeBT* deleteNode = tree -> left;
            delete tree;
            return deleteNode;
        }
        NodeBT* deleteNode = lift(tree -> right);
        tree -> key = deleteNode -> key;
        tree -> right = deleteNodeBT(tree -> right, deleteNode -> key);
    }
    return tree;
}

bool isCompleteTree(NodeBT* tree) {
    bool flag = true;
    NodeCT* list = NULL;
    list -> addLastElementCT(list, tree);
    while ( list != NULL ) {
        NodeBT* front = list -> key;
        if ( flag == false and ( front -> left != NULL or front -> right != NULL ) ) {
            return false;
        }
        if ( front -> left == NULL and front -> right != NULL  ) {
            return false;
        }
        if ( front -> left != NULL ) {
            list -> addLastElementCT(list, front -> left);
        }
        else {
            flag = false;
        }
        if ( front -> right != NULL ) {
            list -> addLastElementCT(list, front -> right);
        }
        else {
            flag = false;
        } 
        list = list -> next;
    }
    return true;
}

void printTree(NodeBT* tree, bool& head) {
    if ( head == true ) {
        cout << tree -> key << " ";
    }
    if ( tree != NULL ) {
        head = false;
        if ( tree -> left == NULL and tree -> right != NULL ) {
            cout << tree -> right -> key << " ";
        }
        if ( tree -> left != NULL and tree -> right == NULL ) {
            cout << tree -> left -> key << " ";
        }
        if ( tree -> left != NULL and tree -> right != NULL ) {
            cout << tree -> left -> key << " " << tree -> right -> key << " ";
        }
        printTree(tree -> left, head);
        printTree(tree -> right, head);
    }
}
void parseListBT(NodeBT* &tree, singleList &node, string line) {
    string newLine;
    for ( auto i : line ) {
        if ( i == ',' ) {
            continue;
        }
        if ( i == ' '  ) {
            node.addLastElement(newLine);
            tree = insertElement(tree, newLine);
            newLine = "";
        }
        else { 
            newLine += i;
        }
    }
    node.addLastElement(newLine);
    tree = insertElement(tree, newLine);
}
void loadFromFileListBT(NodeBT* &tree, singleList &node, string file) {
    string line;
    ifstream fileInput(file);
    getline(fileInput,  line);
    parseListBT(tree, node, line);
}
void saveToFileListBT(singleList list, string file) {
    Node* newNode = list.node;
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


void CompleteBinaryTree(char* argv[]) {
    bool head = true;
    singleList forSave;
    NodeBT* tree = NULL;
    singleList commandLine;
    string fileName = argv[2];
    loadFromFileListBT(tree, forSave, fileName);
    commandLine.parseList(argv[4]);
    string command = commandLine.findElementByIndex(0);
    if ( command == "TINSERT" ) {
        string value = commandLine.findElementByIndex(2);
        tree = insertElement(tree, value);
        forSave.addLastElement(value);
    }
    else if ( command == "TDEL" ) {
        string value = commandLine.findElementByIndex(2);
        tree = deleteNodeBT(tree, value);
        forSave.deleteByValue(value);
    }
    else if ( command == "TCOMPLETE" ) {
        if ( isCompleteTree(tree) == true ) {
            cout << "tree is complete" << " ";
        }
        else {
            cout << "tree is not complete" << " ";
        }
    }
    else if ( command == "TCHECK" ) {
        bool flag = false;
        string value = commandLine.findElementByIndex(2);
        searchElementBT(tree, value, flag);
        if ( flag == false ) {
            cout << "element doesnt exist" << " ";
        }
        if ( flag == true ) {
            cout << "element exist" << " ";
        }
    }
    else if ( command == "TGET" ) {
        printTree(tree, head);
    }
    printTree(tree, head);
    saveToFileListBT(forSave, fileName);
}

