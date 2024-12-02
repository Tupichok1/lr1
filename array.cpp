#include "array.h"

using namespace std;

void arr::initArray(int initCapacity) {
    ar = new string[initCapacity];
    size = 0;
    capacity = initCapacity;
}
void arr::resize(int newCapacity) {
    string* newAr = new string[newCapacity];
    for ( int i = 0; i < size + 1; i ++ ) {
        newAr[i] = ar[i];
    }
    delete[] ar;
    ar = newAr;
    capacity = newCapacity;
}
void arr::pushBack(string value) {
    if ( size == capacity ) {
        resize(2 * capacity);
    }
    ar[size++] = value;
}
void arr::addByIndex(int index, string value) {
    if ( index > size or index < 0 ) {
        cout << "out of size";
        return;
    }
    if ( size == capacity ) {
        resize(2 * capacity);
    }
    string* destination = new string[capacity + 1];
    for ( int i = 0; i < index; i ++ ) {
        destination[i] = ar[i];
    }
    destination[index] = value;
    for ( int i = index + 1; i < size; i ++ ) {
        destination[i] = ar[i - 1];
    }
    delete[] ar;
    ar = destination;
    size += 1;
}
string arr::findElementByIndex(int index) {
    return ar[index];
}
void arr::changeElementByIndex(int index, string value) {
    ar[index] = value;
}
int arr::sizeOfArray() {
    return size;
}
void arr::printElements() {
    for ( int i = 0; i < size; i ++ ) {
        if ( ar[i] != "" ) {
            cout << ar[i] << " ";
        }
    } 
}
void arr::deleteElementByIndex(int index) {
    if ( index > size or index < 0 ) {
        cout << "out of size";
        return;
    }
    for ( int i = index; i < size; i ++ ) {
        ar[i] = ar[i + 1];
    }
    size -= 1;
}
void arr::parse(string line) {
    string newLine;
    for ( auto i : line ) {
        if ( i == ',' ) {
            continue;
        }
        if ( i == ' ' ) {
            pushBack(newLine);
            newLine = "";
        }
        else {
            newLine += i;
        }
    }
    pushBack(newLine);
}
void arr::loadFromFile(string file) {
    string line;
    ifstream fileInput(file);
    if ( fileInput.eof() ) {
        return;
    }
    getline(fileInput, line);
    parse(line);
}
void arr::saveToFile(string file) {
    ofstream out;
    out.open(file);
    for ( int i = 0; i < size; i ++ ) {
        if ( i == ( size - 1 ) ) {
            out << ar[i];
        }
        else {
            out << ar[i] << " ";
        }
    }
    out.close();
}

void Array(char* argv[]) {
    arr ar;
    ar.initArray(15);
    arr commandLine;
    commandLine.initArray(15);
    string fileName = argv[2];
    ar.loadFromFile(fileName);
    commandLine.parse(argv[4]);
    string command = commandLine.findElementByIndex(0);
    if ( command == "MPUSHT" ) {
        ar.pushBack(commandLine.findElementByIndex(2));
        ar.printElements();
    }
    else if ( command == "MPUSHI" ) {
        int index = stoi(commandLine.findElementByIndex(2));
        string value = commandLine.findElementByIndex(3);
        ar.addByIndex(index, value);
    }
    else if ( command == "MFINDI" ) {
        int index = stoi(commandLine.findElementByIndex(2));
        cout << ar.findElementByIndex(index);
        return;
    }
    else if ( command == "MDELI" ) {
        int index = stoi(commandLine.findElementByIndex(2));
        ar.deleteElementByIndex(index);
        ar.printElements();
    }
    else if ( command == "MCHANGEI") {
        int index = stoi(commandLine.findElementByIndex(2));
        string value = commandLine.findElementByIndex(3);
        ar.changeElementByIndex(index, value);
    }
    else if ( command == "MSIZE" ) {
        cout << ar.sizeOfArray();
        return;
    }
    else if ( command == "MPRINT" ) {
        ar.printElements();
    }
    ar.saveToFile(fileName);
}