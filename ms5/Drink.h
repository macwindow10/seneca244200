/* Citation and Sources...
Project Milestone 5
Module: Food
Filename: Drink.h
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

#ifndef SENECA_DRINK_H
#define SENECA_DRINK_H

#include <iomanip>
#include <ios>

#include "Billable.h"

namespace seneca {
class Drink : public Billable {
    char m_size;

   public:
    Drink() : m_size('\0') {}
    std::ostream& print(std::ostream& ostr = std::cout) const override;
    bool order() override;
    bool ordered() const override { return m_size != '\0'; }
    std::ifstream& read(std::ifstream& file) override;
    double price() const override;

    double price(double price);
};
}  // namespace seneca
#endif  // !SENECA_DRINK_H
