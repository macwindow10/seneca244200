/***********************************************************************
// OOP244 Project, Utils Module
//
// File	Utils.h
// Version 0.6
// Date 2024-11-13
// started by Fardad
// Description
// utility function to be used in the project
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
// Fardad          11-20           makeBillFileName
// saiibi          12-09           getInt method updated to validate user input
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include <iostream>
using namespace std;
#include "Utils.h"
namespace seneca {
Utils ut;
bool debug = false;
const size_t AllocationBlockSize = 128;

int Utils::isInteger(char text[]) const {
    bool allDigits = true;
    bool allCharacters = true;
    // bool mixed = false;
    // validation
    for (int i = 0; i < strlen(text); i++) {
        if (i == 0 && text[i] == '-') {
            if (strlen(text) == 1) {
                allCharacters = true;  // Input is just "-"
                break;
            }
            continue;  // Allow negative sign at the start
        }
        if (std::isdigit(text[i])) {
            allCharacters = false;
        } else {
            allDigits = false;
            // mixed = true;
        }
    }
    if (allCharacters == false && allDigits == false) {
        return -2;  // mixed
    }

    if (allDigits == false) {
        return -1;
    }
    return 1;
    // return valid;
}

int Utils::getInt() const {
    std::string input;
    char answer[1000];
    int selection;
    bool valid = false;
    do {
        // input
        // std::cin >> answer;

        while (true) {
            std::getline(std::cin, input);
            if (input.empty()) {
                std::cout << "You must enter a value: ";
                continue;
            }
            input.copy(answer, input.size());
            answer[input.size()] = '\0';
            break;
        }

        // validation
        if (std::cin.fail()) {  // if cin fails

        } else if (strlen(answer) == 0) {  // if empty
            std::cout << "You must enter a value: ";
        } /*else if (!isdigit(answer[0])) {  // if not an integer
            std::cout << "Invalid integer: ";
        }*/
        else if (isInteger(answer) == -1) {  // if there are other chars except for digits
            std::cout << "Invalid integer: ";
        } else if (isInteger(answer) == -2) {  // if there are other chars except for digits
            std::cout << "Only an integer please: ";
        } else {
            // std::cout << "answer: " << answer << std::endl;
            try {
                selection = atoi(answer);
                valid = true;
            } catch (const std::invalid_argument&) {
                std::cout << "Invalid integer: ";
            } catch (const std::out_of_range&) {
                // std::cout << "Error: Number out of range. Please enter a smaller integer.\n";
            }
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
            std::cout << "Invalid value: [" << min << "<= value <=" << max << "], try again: ";
        } else {
            valid = true;
        }
    }
    return value;
}

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
char* Utils::makeBillFileName(char* filename, size_t billNo) const {
    char billFileName[21] = "bill_";
    size_t temp = billNo;
    int cnt = 5;
    int length;
    // Calculate the number of digits
    do {
        cnt++;
        temp /= 10;
    } while (temp > 0);
    length = cnt;
    // Convert each digit to character from the end
    while (billNo > 0) {
        billFileName[--cnt] = (billNo % 10) + '0';
        billNo /= 10;
    }
    // Handle the case when billNo is 0
    if (billFileName[cnt - 1] == '\0') {
        billFileName[--cnt] = '0';
    }
    // Attach .txt to the end of the file name
    for (int i = 0; ".txt"[i]; i++) {
        billFileName[length++] = ".txt"[i];
    }
    billFileName[length] = '\0';
    strcpy(filename, billFileName);
    return filename;
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

}  // namespace seneca