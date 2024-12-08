/* Citation and Sources...
Project Milestone 5
Module: Order
Filename: Ordering.h
Version 1.0
Author   saiibi
Revision History
-----------------------------------------------------------
Date        Reason
2024/12/04  Class created for Milestone 4
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#ifndef SENECA_ORDERING_H
#define SENECA_ORDERING_H
#include <iostream>

#include "Billable.h"
#include "Drink.h"
#include "Food.h"
#include "constants.h"
namespace seneca {
class Ordering {
   protected:
    unsigned foodCounter;
    unsigned drinkCounter;
    unsigned billableCounter;
    unsigned billSerialNumber;
    Food* foodArray;
    Drink* drinkArray;
    Billable* billItems[MaximumNumberOfBillItems];

    void billTitlePrint(std::ostream& out) const;
    void printTotals(std::ostream& out, double total) const;
    size_t countRecords(const char* file) const;

   public:
    Ordering(const char* foodFile, const char* drinkFile);
    ~Ordering();

    operator bool() const;
    unsigned noOfBillItems() const;
    bool hasUnsavedBill() const;

    void listFoods() const;
    void listDrinks() const;
    void orderFood();
    void orderDrink();
    void printBill(std::ostream& out) const;
    void resetBill();
};
}  // namespace seneca
#endif  // !SENECA_ORDERING_H
