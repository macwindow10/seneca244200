#include "Menu.h"

using namespace std;

namespace seneca {

// Helper function to trim leading whitespace from a string
char* MenuItem::trimLeadingWhitespace(const char* str) const {
    while (*str && std::isspace(*str)) ++str;
    return strdup(str);
}

// display function
std::ostream& MenuItem::display(std::ostream& ostr) const {
    if (m_content) {
        ostr << std::string(m_indent * m_indentSize, ' ');
        if (m_row >= 0) {
            ostr << std::setw(2) << std::setfill(' ') << m_row << "- ";
        }
        ostr << m_content;
    } else {
        ostr << "??????????";
    }
    return ostr;
}

// display function
std::ostream& MenuItem::display() const {
    display(std::cout);
    return std::cout;
}

}  // namespace seneca