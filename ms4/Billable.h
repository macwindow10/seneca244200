#ifndef SENECA_BILLABLE_H
#define SENECA_BILLABLE_H
#include <string.h>

#include <fstream>
#include <iostream>
#include <ostream>
namespace seneca {
class Billable {
   protected:
    char* m_name;
    double m_price;

   protected:
    void price(double value) { m_price = value; }
    void name(const char* name);

   public:
    Billable() : m_name(nullptr), m_price(0.0) {}
    Billable(const Billable& other);
    Billable& operator=(const Billable& other);
    virtual ~Billable();

    virtual double price() const { return m_price; }
    virtual std::ostream& print(std::ostream& ostr = std::cout) const = 0;
    virtual bool order() = 0;
    virtual bool ordered() const = 0;
    virtual std::ifstream& read(std::ifstream& file) = 0;

    operator const char*() const { return m_name; }

    friend double operator+(double money, const Billable& B) {
        return money + B.price();
    }
    friend double& operator+=(double& money, const Billable& B) {
        money += B.price();
        return money;
    }
};
}  // namespace seneca
#endif  // !SENECA_BILLABLE_H
