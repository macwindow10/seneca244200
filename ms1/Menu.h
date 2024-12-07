/* Citation and Sources...
Project Milestone 1
Module: Menu
Filename: constants.h
Version 1.0
Author   saiibi
Revision History
-----------------------------------------------------------
Date        Reason
2024/11/25  file created and initialized
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#ifndef SENECA_MENU_H
#define SENECA_MENU_H

#include <cctype>
#include <cstring>
#include <iomanip>
#include <iostream>

#include "constants.h"

namespace seneca {
class MenuItem {
   private:
    char* m_content;        // content
    unsigned m_indent;      // number of indentations
    unsigned m_indentSize;  // indentation size
    int m_row;

    char* trimLeadingWhitespace(const char* str) const;

   public:
    // constructor
    MenuItem(const char* content, unsigned indent = 0, unsigned indentSize = 0, int row = -1)
        : m_content(nullptr), m_indent(indent), m_indentSize(indentSize), m_row(row) {
        if (content && *content != '\0' && std::strlen(content) > 0 &&
            indent <= 4 && indentSize <= 4 && row <= static_cast<int>(MaximumNumberOfMenuItems)) {
            m_content = trimLeadingWhitespace(content);
        }
    }

    ~MenuItem() {
        delete[] m_content;
    }

    MenuItem(const MenuItem& other) = delete;             // Non-copyable
    MenuItem& operator=(const MenuItem& other) = delete;  // Non-assignable

    // bool type conversion overload
    operator bool() const {
        return m_content != nullptr;
    }

    // display function
    std::ostream& display(std::ostream& ostr) const;

    // display function
    std::ostream& display() const;
};

}  // namespace seneca
#endif  // !SENECA_MENU_H
