/***********************************************************************
// OOP244 Project, milestone 5.5 : tester program
//
// File	ms51.cpp
// Version 1.0
// Date 2024-12-08
// Author Fardad
// Description
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//
/////////////////////////////////////////////////////////////////
***********************************************************************/

#include <iostream>

#include "Menu.h"
#include "Ordering.h"
using namespace std;
using namespace seneca;

// Entry point for menu ordering system
int main() {
    Ordering ord("drinks.csv", "foods.csv");
    if (ord) {
        size_t appSel{}, ordSel{};

        // Create Application Menu + Ordering Menu with 1 level indent
        Menu appMenu("Seneca Restaurant ", "End Program");
        appMenu << "Order" << "Print Bill" << "Start a New Bill" << "List Foods" << "List Drinks";
        Menu orderMenu("Order Menu", "Back to main menu", 1);
        orderMenu << "Food" << "Drink";

        // Display the Menu and get the user's selection:
        do {
            switch (appSel = appMenu.select()) {
                case 1:
                    do {
                        switch (ordSel = orderMenu.select()) {
                            case 1:
                                ord.orderFood();
                                break;
                            case 2:
                                ord.orderDrink();
                                break;
                        }
                    } while (ordSel);
                    break;
                case 2:
                    ord.printBill(cout);
                    break;
                case 3:
                    ord.resetBill();
                    break;
                case 4:
                    ord.listFoods();
                    break;
                case 5:
                    ord.listDrinks();
                    break;
            }  // switch

            // Checl for unsaved bills before exit
            if (appSel == 0 && ord.hasUnsavedBill()) {
                Menu areYouSure("You have bills that are not saved, are you sue you want to exit?", "No");
                areYouSure << "Yes";
                if (areYouSure.select() == 0) {
                    appSel = 1;
                }
            }

        } while (appSel);
    } else {
        cout << "Failed to open data files or the data files are corrupted!" << endl;
    }
    return 0;
}