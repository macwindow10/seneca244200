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
    std::string content;
    unsigned int rowNumber = 0;
    unsigned int indentLevel = 0;
    unsigned int indentSize = 0;

    MenuItem(const std::string& itemContent, unsigned int rowNum, unsigned int level, unsigned int size)
        : content(itemContent), rowNumber(rowNum), indentLevel(level), indentSize(size) {}

    void display(std::ostream& ostr) const {
        for (unsigned int i = 0; i < indentLevel * indentSize; ++i)
            ostr << ' ';
        ostr << rowNumber << "- " << content << '\n';
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
        if (numOfItems < MaximumNumberOfMenuItems) {
            items[numOfItems] = new MenuItem(menuItemContent, numOfItems + 1, indentLevel, indentSize);
            ++numOfItems;
        }
        return *this;
    }

    size_t select() const {
        if (title) {
            for (unsigned int i = 0; i < title->indentLevel * title->indentSize; ++i)
                std::cout << ' ';
            std::cout << title->content << '\n';
        }

        for (size_t i = 0; i < numOfItems; ++i)
            if (items[i]) items[i]->display(std::cout);

        if (exitOption)
            exitOption->display(std::cout);

        // selectionPrompt->display(std::cout);
        for (unsigned int i = 0; i < selectionPrompt->indentLevel * selectionPrompt->indentSize; ++i)
            std::cout << ' ';
        std::cout << selectionPrompt->content;

        return Utils::getInt(0, static_cast<int>(numOfItems));
    }

    friend size_t operator<<(std::ostream& ostr, const Menu& menu) {
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
