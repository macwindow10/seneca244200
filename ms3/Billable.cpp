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
