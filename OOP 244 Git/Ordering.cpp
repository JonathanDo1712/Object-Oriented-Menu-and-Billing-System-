#define _CRT_SECURE_NO_WARNINGS
#include "Drink.h"
#include "Food.h"
#include "Billable.h"
#include "Ordering.h"
#include "constants.h"
#include "Menu.h"
#include "Utils.h"
#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
namespace seneca {
	void Ordering::BillTitlePrint(std::ostream& os) const {
		os << "Bill # " << std::setw(3) << std::setfill('0') << m_billSerialNumber
			<< " =============================" << std::endl;
	}

	void Ordering::PrintTotals(std::ostream& os, double totalAmount) const {
		double tax = totalAmount * Tax;  
		double totalWithTax = totalAmount + tax;

		os << "                     Total:        " << totalAmount << std::endl;
		os << "                     Tax:           " << tax << std::endl;
		os << "                     Total+Tax:    " << totalWithTax << std::endl;
		os << "========================================" << std::endl;
	}

    size_t Ordering::countRecords(const char* file) const {
        size_t newlineCount = 0;  
        char ch;  

        std::ifstream inFile(file);

        if (!inFile.is_open()) {
            return 0;  
        }

        while (inFile.get(ch)) {
            if (ch == '\n') {
                newlineCount++;
            }
        }

        inFile.close();

        return newlineCount;
    }

    ////////////////////
    //PUBLIC FUNCTIONS
    ///////////////////

    Ordering::Ordering(const char* drinkFile, const char* foodFile)
        : m_foodArray(nullptr), m_drinkArray(nullptr), m_foodCounter(0), m_drinkCounter(0) {

        size_t foodRecords = countRecords(foodFile);
        size_t drinkRecords = countRecords(drinkFile);

        std::ifstream foodFileStream(foodFile);
        if (!foodFileStream.is_open()) {
            // Mark as invalid if file can't be opened
            return;
        }

        std::ifstream drinkFileStream(drinkFile);
        if (!drinkFileStream.is_open()) {
            // Mark as invalid if file can't be opened
            return;
        }

        m_foodArray = new Food[foodRecords];
        m_drinkArray = new Drink[drinkRecords];

        bool validFoodData = true;
        for (size_t i = 0; i < foodRecords && foodFileStream; ++i) {
            std::string line;
            std::getline(foodFileStream, line);
            std::istringstream ss(line);

            std::string name;
            double price;

            std::getline(ss, name, ',');
            ss >> price;

            if (!name.empty() && price > 0) {
                m_foodArray[i].name(name.c_str());
                m_foodArray[i].Billable::price(price);
            }
            else {
                validFoodData = false;
            }
        }

        bool validDrinkData = true;
        for (size_t i = 0; i < drinkRecords && drinkFileStream; ++i) {
            std::string line;
            std::getline(drinkFileStream, line);
            std::istringstream ss(line);

            std::string name;
            double price;

            std::getline(ss, name, ',');
            ss >> price;

            if (!name.empty() && price > 0) {
                m_drinkArray[i].name(name.c_str());
                m_drinkArray[i].Billable::price(price);
            }
            else {
                validDrinkData = false;
            }
        }

        if (!validFoodData || !validDrinkData || foodFileStream.fail() || drinkFileStream.fail()) {
            delete[] m_foodArray;
            delete[] m_drinkArray;
            m_foodArray = nullptr;
            m_drinkArray = nullptr;
            m_foodCounter = 0;
            m_drinkCounter = 0;
        }
        else {
            m_foodCounter = foodRecords;
            m_drinkCounter = drinkRecords;
        }

        foodFileStream.close();
        drinkFileStream.close();
    }


    Ordering::~Ordering() {
        for (size_t i = 0; i < m_billableCounter; ++i) {
            delete m_billItems[i]; 
        }
        delete[] m_foodArray;   
        delete[] m_drinkArray;  
    }

    Ordering::operator bool() const {
        return (m_foodArray != nullptr && m_drinkArray != nullptr);
    }

    size_t Ordering::noOfBillItems() const {
        return m_billableCounter;
    }

    bool Ordering::hasUnsavedBill() const {
        return m_billableCounter > 0;
    }

    void Ordering::listFoods() const {
        std::cout << "List Of Avaiable Meals" << std::endl;
        std::cout << "========================================" << std::endl;

        for (size_t i = 0; i < m_foodCounter; ++i) {
            m_foodArray[i].print(); 
            std::cout << std::endl;
        }

        std::cout << "========================================" << std::endl;
    }

    void Ordering::ListDrinks() const {
        std::cout << "List Of Avaiable Drinks" << std::endl;
        std::cout << "========================================" << std::endl;

        for (size_t i = 0; i < m_drinkCounter; ++i) {
            m_drinkArray[i].print(); 
            std::cout << std::endl;
        }

        std::cout << "========================================" << std::endl;
    }

    void Ordering::orderFood() {
        Menu foodMenu("Food Menu", "Back to Order", 2, 3); 

        for (size_t i = 0; i < m_foodCounter; ++i) {
            foodMenu << static_cast<const char*>(m_foodArray[i]);
        }

        size_t selection = foodMenu.select(); 

        if (selection != 0) {
            Food* selectedFood = new Food(m_foodArray[selection - 1]); 

            m_billItems[m_billableCounter] = selectedFood;

            if (m_billItems[m_billableCounter]->order()) {
                ++m_billableCounter;
            }
            else {
                delete selectedFood;
                std::cerr << "Order failed. The food item has been removed." << std::endl;
            }
        }
    }

    void Ordering::orderDrink() {
        Menu drinkMenu("Drink Menu", "Back to Order", 2, 3);

        for (size_t i = 0; i < m_drinkCounter; ++i) {
            drinkMenu << static_cast<const char*>(m_drinkArray[i]);
        }

        size_t selection = drinkMenu.select();

        if (selection != 0) {
            Drink* selectedDrink = new Drink(m_drinkArray[selection - 1]);

            if (selectedDrink->order()) {
                m_billItems[m_billableCounter] = selectedDrink;
                ++m_billableCounter;
            }
            else {
                delete selectedDrink;
            }
        }
    }

    void Ordering::printBill(std::ostream& ostr) const {
        double totalPrice = 0.0;

        ostr << "Bill # " << std::setw(3) << std::setfill('0') << std::right << m_billSerialNumber
            << " =============================" << std::endl;

        for (size_t i = 0; i < m_billableCounter; ++i) {
            m_billItems[i]->print(ostr);

            totalPrice += m_billItems[i]->price();
            ostr << std::endl;
        }

        ostr << std::left << "                     Total:        " << totalPrice << std::endl;

        ostr << std::left << "                     Tax:           " << totalPrice * Tax << std::endl;

        ostr << std::left << "                     Total+Tax:    " << totalPrice * (1 + Tax) << std::endl;


        ostr << "========================================" << std::endl;
    }

    void Ordering::resetBill() {
        char filename[21]; 
        ut.makeBillFileName(filename, m_billSerialNumber);

        std::ofstream billFile(filename);

        if (billFile.is_open()) {
            printBill(billFile);

            std::cout << "Saved bill number " << m_billSerialNumber << std::endl;
            std::cout << "Starting bill number " << (m_billSerialNumber + 1) << std::endl;

            for (size_t i = 0; i < m_billableCounter; ++i) {
                delete m_billItems[i]; 
                m_billItems[i] = nullptr;
            }

            m_billableCounter = 0;

            ++m_billSerialNumber;
        }
        else {
            std::cerr << "Error opening file " << filename << " for saving the bill." << std::endl;
        }
    }

}