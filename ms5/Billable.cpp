/* Citation and Sources...
Project Milestone 5
Module: Order
Filename: Billable.cpp
Version 1.0
Author   saiibi
Revision History
-----------------------------------------------------------
Date        Reason
2024/12/04  Class created for Milestone 5
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#include "Billable.h"

namespace seneca {

void Billable::name(const char* name) {
    delete[] m_name;
    m_name = new char[strlen(name) + 1];
    strcpy(m_name, name);
}

Billable::Billable(const Billable& other) : m_name(nullptr) {
    *this = other;
}

Billable& Billable::operator=(const Billable& other) {
    if (this != &other) {
        name(other.m_name);
        m_price = other.m_price;
    }
    return *this;
}

Billable::~Billable() {
    delete[] m_name;
}

}  // namespace seneca
