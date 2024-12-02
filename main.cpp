#include "hashMap.h"
#include "dualLinkedList.h"
#include "queue.h"
#include "stack.h"
#include "completeBinaryTree.h"
#include "array.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    if ( argv[4][0] == 'M' ) {
        Array(argv);
    } 
    else if ( argv[4][0] == 'L' ) {
        SingleList(argv);
    }
    else if ( argv[4][0] == 'D' ) {
        DoubleLinkedList(argv);
    }
    else if ( argv[4][0] == 'Q' ) {
        Queue(argv);
    }
    else if ( argv[4][0] == 'S' ) {
        Stack(argv);
    }
    else if ( argv[4][0] == 'H' ) {
        HashMap(argv);
    }
    else if ( argv[4][0] == 'T' ) {
        CompleteBinaryTree(argv);
    }
    return 0; 
}

