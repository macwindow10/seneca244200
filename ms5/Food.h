/* Citation and Sources...
Project Milestone 5
Module: Food
Filename: Food.h
Version 1.0
Author   saiibi
Revision History
-----------------------------------------------------------
Date        Reason
2024/12/08  Class imported from Milestone 4
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#ifndef SENECA_FOOD_H
#define SENECA_FOOD_H

#include <iomanip>

#include "Billable.h"
namespace seneca {
class Food : public Billable {
    bool m_ordered;
    bool m_child;
    char* m_customize;

   public:
    Food() : m_ordered(false), m_child(false), m_customize(nullptr) {}
    Food(const Food& other);
    Food& operator=(const Food& other);
    ~Food();

    std::ostream& print(std::ostream& ostr = std::cout) const override;
    bool order() override;
    bool ordered() const override { return m_ordered; }
    std::ifstream& read(std::ifstream& file) override;
    double price() const override;

    double price(double price);
};
}  // namespace seneca
#endif  // !SENECA_FOOD_H
