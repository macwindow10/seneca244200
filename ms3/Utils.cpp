/***********************************************************************
// OOP244 Project, Utils Module
//
// File	Utils.h
// Version 0.5
// Date 2024-11-13
// started by Fardad
// Description
// utility function to be used in the project
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
// saiibi          2024/12/01      getInt methods implemented
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include <iostream>
using namespace std;
#include "Utils.h"
namespace seneca {
Utils ut;
bool debug = false;
const size_t AllocationBlockSize = 128;

char* Utils::alocpy(const char* src) const {
    char* des{};
    return alocpy(des, src);
}

char* Utils::alocpy(char*& des, const char* src) const {
    delete[] des;
    des = nullptr;
    if (src) {
        des = new char[strlen(src) + 1];
        strcpy(des, src);
    }
    return des;
}

char* Utils::strcpy(char* des, const char* src) const {
    int i;
    for (i = 0; src[i]; i++) des[i] = src[i];
    des[i] = char(0);
    return des;
}
char* Utils::strcpy(char* des, const char* src, int len) const {
    int i;
    for (i = 0; i < len && src[i]; i++) des[i] = src[i];
    des[i] = 0;  // unlike strncpy, this function null terminates the des cstring
    return des;
}
char* Utils::strncpy(char* des, const char* src, int len) const {
    int i = 0;
    while (i < len - 1 && src[i]) {
        des[i] = src[i];
        i++;
    }
    des[i] = src[i];
    return des;
}

int Utils::strlen(const char* str) const {
    int len;
    for (len = 0; str[len]; len++);
    return len;
}

// Dynamically reads a cstring from istream
char* Utils::read(char*& toRet, istream& istr, char delimiter) const {
    bool done = false;
    char* cstr = new char[AllocationBlockSize];
    toRet = cstr;
    int size = AllocationBlockSize;
    int nullindex = 1;
    do {
        cin.getline(cstr, AllocationBlockSize, delimiter);
        if (cin.fail()) {
            char* temp = new char[size + AllocationBlockSize];
            strcpy(temp, toRet);
            delete[] toRet;
            toRet = temp;
            cstr = &toRet[size - nullindex++];
            size += AllocationBlockSize;
            cin.clear();
        } else {
            done = true;
        }
    } while (!done);
    char* temp = new char[strlen(toRet) + 1];
    strcpy(temp, toRet);
    delete[] toRet;
    toRet = temp;
    return toRet;
}

bool Utils::isspace(char ch) const {
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f' || ch == '\r';
}

bool Utils::isspace(const char* cstring) const {
    while (cstring && isspace(*cstring)) {
        cstring++;
    }
    return cstring && *cstring == 0;
}

bool Utils::isInteger(char text[]) const {
    // validation
    bool valid = true;
    // check for integer
    for (int i = 0; i < strlen(text); i++) {
        if (!isdigit(text[i])) {
            valid = false;
            break;
        }
    }
    return valid;
}

int Utils::getInt() const {
    char answer[1000];
    int selection;
    bool valid = false;
    do {
        // input
        std::cin >> answer;
        // validation

        if (std::cin.fail()) {  // if cin fails

        } else if (strlen(answer) == 0) {  // if empty
            std::cout << "You must enter a value:";
        } else if (!isdigit(answer[0])) {  // if not an integer
            std::cout << "Invalid integer:";
        } else if (!isInteger(answer)) {  // if there are other chars except for digits
            std::cout << "Only an integer please:";
        } else {
            // std::cout << "answer: " << answer << std::endl;
            selection = atoi(answer);
            // std::cout << "selection: " << selection << std::endl;
            valid = true;
        }
    } while (!valid);
    return selection;
}

int Utils::getInt(int min, int max) const {
    int value = 0;
    bool valid = false;
    while (!valid) {
        value = getInt();
        if (value < min || value > max) {
            std::cout << "Invalid value: [" << min << " <= value <= " << max << "], try again:\n";
        } else {
            valid = true;
        }
    }
    return value;
}

}  // namespace seneca