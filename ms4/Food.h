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
