#include <iostream>
#include <fstream>
#include "Menu.h"
#include "Ordering.h"
using namespace std;
using namespace seneca;

int main() {
    Menu sen("Seneca Restaurant ", "End Program", 0, 0);
    Ordering ord("drinks.csv", "foods.csv");
    Menu om("Order Menu", "Back to main menu", 3, 1);
    Menu exit("You have bills that are not saved, are you sure you want to exit?", "No", 0, 0);

    sen << "Order"
        << "Print Bill"
        << "Start a New Bill"
        << "List Foods"
        << "List Drinks";

    om << "Food"
        << "Drink";

    exit << "Yes";

    size_t selection;
    do {
        selection = sen.select();
        switch (selection) {
        case 1:
            size_t o_selection;
            do {
                o_selection = om.select();
                switch (o_selection) {
                case 1:
                    ord.orderFood();
                    break;
                case 2:
                    ord.orderDrink();
                    break;
                }
            } while (o_selection != 0);
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
            ord.ListDrinks();
            break;
        case 0:
            if (ord.hasUnsavedBill()) {
                size_t e_selection;
                e_selection = exit.select();
                switch (e_selection) {
                case 0:
                    selection = 1;
                    break;
                }
            }

            break;
        }
    } while (selection != 0);
}