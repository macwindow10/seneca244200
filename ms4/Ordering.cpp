#define _CRT_SECURE_NO_WARNINGS
#include "Ordering.h"

#include <cstdio>
#include <fstream>

#include "Billable.h"
#include "Drink.h"
#include "Food.h"
#include "Menu.h"
#include "Utils.h"
#include "constants.h"
using namespace std;
namespace seneca {

/*
size_t Ordering::countRecords(const char* thefile) const {
}
*/

Ordering::Ordering(const char* drinkFile, const char* foodFile)
    : foodCounter(0), drinkCounter(0), billableCounter(0), billSerialNumber(1), foodArray(nullptr), drinkArray(nullptr) {
    size_t foodRecords = countRecords(foodFile);
    size_t drinkRecords = countRecords(drinkFile);

    if (foodRecords && drinkRecords) {
        foodArray = new Food[foodRecords];
        drinkArray = new Drink[drinkRecords];

        std::ifstream foodStream(foodFile);
        std::ifstream drinkStream(drinkFile);

        if (foodStream && drinkStream) {
            for (size_t i = 0; i < foodRecords && foodArray[i].read(foodStream); ++i) {
                ++foodCounter;
            }
            for (size_t i = 0; i < drinkRecords && drinkArray[i].read(drinkStream); ++i) {
                ++drinkCounter;
            }
        }

        if (foodCounter != foodRecords || drinkCounter != drinkRecords) {
            delete[] foodArray;
            delete[] drinkArray;
            foodArray = nullptr;
            drinkArray = nullptr;
        }
    }
}

// Destructor
Ordering::~Ordering() {
    delete[] foodArray;
    delete[] drinkArray;
    for (unsigned i = 0; i < billableCounter; ++i) {
        delete billItems[i];
    }
}

// Count records in file
size_t Ordering::countRecords(const char* file) const {
    size_t count = 0;
    std::ifstream inFile(file);
    char ch;

    while (inFile.get(ch)) {
        if (ch == '\n') {
            ++count;
        }
    }

    return count;
}

// Safe empty state check
Ordering::operator bool() const {
    return foodArray && drinkArray;
}

// Number of bill items
unsigned Ordering::noOfBillItems() const {
    return billableCounter;
}

// Check for unsaved bill
bool Ordering::hasUnsavedBill() const {
    return billableCounter > 0;
}

// List available foods
void Ordering::listFoods() const {
    std::cout << "List Of Avaiable Meals\n========================================\n";
    for (unsigned i = 0; i < foodCounter; ++i) {
        foodArray[i].print(std::cout);
    }
    std::cout << "========================================\n";
}

// List available drinks
void Ordering::ListDrinks() const {
    std::cout << "List Of Avaiable Drinks\n========================================\n";
    for (unsigned i = 0; i < drinkCounter; ++i) {
        drinkArray[i].print(std::cout);
    }
    std::cout << "========================================\n";
}

// Order food
void Ordering::orderFood() {
    Menu menu("Food Menu", "Back to Order", 2);
    for (unsigned i = 0; i < foodCounter; ++i) {
        // menu.add(foodArray[i].getName());
        menu << foodArray[i];
    }
    int selection = menu.select();
    if (selection > 0) {
        Food* orderedFood = new Food(foodArray[selection - 1]);
        if (orderedFood->order()) {
            billItems[billableCounter++] = orderedFood;
        } else {
            delete orderedFood;
        }
    }
}

// Order drink
void Ordering::orderDrink() {
    Menu menu("Drink Menu", "Back to Order", 2);
    for (unsigned i = 0; i < drinkCounter; ++i) {
        // menu.add(drinkArray[i].getName());
        menu << drinkArray[i];
    }
    int selection = menu.select();

    if (selection > 0) {
        Drink* orderedDrink = new Drink(drinkArray[selection - 1]);
        if (orderedDrink->order()) {
            billItems[billableCounter++] = orderedDrink;
        } else {
            delete orderedDrink;
        }
    }
}

// Print bill
void Ordering::printBill(std::ostream& out) const {
    double total = 0.0;
    billTitlePrint(out);
    for (unsigned i = 0; i < billableCounter; ++i) {
        billItems[i]->print(out);
        total += billItems[i]->price();
    }
    printTotals(out, total);
}

// Reset bill
void Ordering::resetBill() {
    char billFilename[256];
    ut.makeBillFileName(billFilename, billSerialNumber);

    std::ofstream billFile(billFilename);
    if (billFile) {
        printBill(billFile);
        std::cout << "Saved bill number " << billSerialNumber << "\nStarting bill number " << (billSerialNumber + 1) << "\n";
    }

    for (unsigned i = 0; i < billableCounter; ++i) {
        delete billItems[i];
    }
    billableCounter = 0;
    ++billSerialNumber;
}

// Private: Print bill title
void Ordering::billTitlePrint(std::ostream& out) const {
    out << "Bill # " << std::setw(3) << std::setfill('0') << billSerialNumber << " =============================\n";
}

// Private: Print totals
void Ordering::printTotals(std::ostream& out, double total) const {
    double tax = total * Tax;
    out << std::fixed << std::setprecision(2);
    out << "                     Total:        " << total << "\n"
        << "                     Tax:           " << tax << "\n"
        << "                     Total+Tax:    " << (total + tax) << "\n"
        << "========================================\n";
}
}  // namespace seneca