/* Citation and Sources...
Project Milestone 5
Module: Menu
Filename: Menu.h
Version 3.0
Author   saiibi
Revision History
-----------------------------------------------------------
Date        Reason
2024/12/01  Menu code updated according to Milestone 3
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

#include "Utils.h"
#include "constants.h"

namespace seneca {
class Menu;
class MenuItem {
   private:
    char* m_content;
    size_t m_indents;
    size_t m_size;
    int m_row;

    MenuItem(const char* content, size_t indent = 0, size_t indentSize = 0, int row = -1)
        : m_content(nullptr), m_indents(indent), m_size(indentSize), m_row(row) {
        if (content && *content != '\0' && std::strlen(content) > 0 &&
            indent <= 4 && indentSize <= 4 && row <= static_cast<int>(MaximumNumberOfMenuItems)) {
            m_content = trimLeadingWhitespace(content);
        }
    }

    char* trimLeadingWhitespace(const char* str) const {
        while (*str && std::isspace(*str)) ++str;
        return strdup(str);
    }

    void display(std::ostream& ostr) const {
        if (m_content) {
            // ostr << m_indents << m_size << '\n';
            ostr << std::string(m_indents * m_size, ' ');
            if (m_row >= 0) {
                ostr << std::setw(2) << std::setfill(' ') << m_row << "- ";
            }
            ostr << m_content << std::endl;
        }
    }

    operator bool() const {
        return m_content != nullptr;
    }

    friend class Menu;
};

class Menu {
   private:
    unsigned int indentLevel;
    unsigned int indentSize;
    size_t numOfItems;
    MenuItem* title;
    MenuItem* exitOption;
    MenuItem* selectionPrompt;
    MenuItem* items[MaximumNumberOfMenuItems];

   public:
    Menu(const char* menuTitle, const char* exitOpt = "Exit", unsigned int level = 0, unsigned int size = 3)
        : indentLevel(level), indentSize(size), numOfItems(0), title(new MenuItem(menuTitle, 0, level, size)), exitOption(new MenuItem(exitOpt, 0, level, size)), selectionPrompt(new MenuItem("> ", 0, level, size)) {
        std::fill(std::begin(items), std::end(items), nullptr);
    }

    ~Menu() {
        delete title;
        delete exitOption;
        delete selectionPrompt;
        for (size_t i = 0; i < numOfItems; ++i) {
            delete items[i];
            items[i] = nullptr;
        }
    }

    Menu& operator<<(const char* menuItemContent) {
        // std::cout << "Menu& Menu::operator << (const char* content): " << menuItemContent << "\n";
        if (numOfItems < MaximumNumberOfMenuItems) {
            // std::cout << "operator<<" << menuItemContent << "\n";
            items[numOfItems] = new MenuItem(menuItemContent, indentLevel, indentSize, numOfItems + 1);
            ++numOfItems;
        }
        return *this;
    }

    size_t select() const {
        if (title != nullptr) {
            // std::cout << "select 1.1\n";
            // std::cout << title->m_indents << title->m_size;
            // for (unsigned int i = 0; i < title->m_indents * title->m_size; ++i)
            // std::cout << ' ';
            // std::cout << "select 1.2\n";
            if (title->m_content == nullptr) {
                // std::cout << "title->m_content is null" << '\n';
            } else {
                // std::cout << std::string(6, ' ');
                std::cout << title->m_content << '\n';
            }
            // std::cout << "select 1.3\n";
        }

        // std::cout << "select 2\n";
        // std::cout << numOfItems << "\n";
        for (size_t i = 0; i < numOfItems; ++i)
            if (items[i]) items[i]->display(std::cout);

        // if (exitOption) {
        // exitOption->display(std::cout);
        // std::cout << exitOption->m_indents << exitOption->m_size << std::endl;
        std::cout << std::string(items[0]->m_indents * items[0]->m_size, ' ');
        std::cout << std::setw(2) << std::setfill(' ') << "0" << "- ";
        std::cout << exitOption->m_content << '\n';
        //}

        // selectionPrompt->display(std::cout);
        for (unsigned int i = 0; i < selectionPrompt->m_indents * selectionPrompt->m_size; ++i)
            std::cout << ' ';
        std::cout << std::string(items[0]->m_indents * items[0]->m_size, ' ');
        std::cout << selectionPrompt->m_content;

        int selection = ut.getInt(0, static_cast<int>(numOfItems));
        // std::cout << "selection: " << selection << std::endl;
        return selection;
    }

    friend size_t operator<<(std::ostream& ostr, const Menu& menu) {
        // std::cout << "friend size_t operator<<(std::ostream& ostr, const Menu& menu)" << "\n";
        if (&ostr == &std::cout) {
            return menu.select();
        } else {
            return 0;
        }
    }

    // Prevent copying
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
};

}  // namespace seneca
#endif  // !SENECA_MENU_H
