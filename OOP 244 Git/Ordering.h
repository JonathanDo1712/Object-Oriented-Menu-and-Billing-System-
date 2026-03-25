#ifndef SENECA_ORDERING_H
#define SENECA_ORDERING_H
#include "Food.h"
#include "Drink.h"
#include "Billable.h"
#include "constants.h"
#include <iostream>
namespace seneca {
    class Ordering {
    private:
        Food* m_foodArray{};
        Drink* m_drinkArray{};
        Billable* m_billItems[MaximumNumberOfBillItems];

        unsigned int m_foodCounter{};
        unsigned int m_drinkCounter{};
        unsigned int m_billableCounter{};

        unsigned int m_billSerialNumber = 1; 

        void BillTitlePrint(std::ostream& os) const;
        void PrintTotals(std::ostream& os, double totalAmount) const;

        size_t countRecords(const char* file)const;
    public:
        Ordering(const char* foodFile, const char* drinkFile);
        ~Ordering();

        operator bool() const;
        size_t noOfBillItems() const;
        bool hasUnsavedBill() const;

        void listFoods() const;
        void ListDrinks() const;

        void orderFood();
        void orderDrink();

        void printBill(std::ostream& ostr) const;
        void resetBill();
    };
}
#endif // !SENECA_ORDERING_H