/* Citation and Sources...
Project Milestone 2
Module: Menu
Filename: Util.h
Version 1.0
Author   saiibi
Revision History
-----------------------------------------------------------
Date        Reason
2024/11/27  file created and initialized
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#ifndef SENECA_UTILS_H
#define SENECA_UTILS_H

#include <cctype>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>

#include "constants.h"

namespace seneca {
class Utils {
   public:
    static bool isInteger(char text[]) {
        // validation
        bool valid = true;
        // check for integer
        for (size_t i = 0; i < strlen(text); i++) {
            if (!isdigit(text[i])) {
                valid = false;
                break;
            }
        }
        return valid;
    }

    static int getInt() {
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

    static int getInt(int min, int max) {
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
};

}  // namespace seneca
#endif