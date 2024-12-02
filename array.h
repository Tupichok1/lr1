#include <iostream>
#include <string>
#include <fstream>

struct arr {
    std::string* ar;
    int size;
    int capacity;
    void initArray(int initCapacity);
    void resize(int newCapacity);
    void pushBack(std::string value);
    void addByIndex(int index, std::string value);
    std::string findElementByIndex(int index);
    void changeElementByIndex(int index, std::string value);
    int sizeOfArray();
    void printElements();
    void deleteElementByIndex(int index);
    void parse(std::string line);
    void loadFromFile(std::string file);
    void saveToFile(std::string file);
};

void Array(char* argv[]);