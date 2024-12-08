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
