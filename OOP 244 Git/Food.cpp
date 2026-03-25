#include "Food.h"
#include "Utils.h"

#include <iostream>
#include <cstring>
#include <string>    
#include <iomanip>

namespace seneca {

    //CONSTURCTOR
    Food::Food() : m_ordered(false), m_child(false), m_customize(nullptr) {}

    //COPY CONSTRUCTOR 
    Food::Food(const Food& src) : Billable(src), m_ordered(src.m_ordered), m_child(src.m_child), m_customize(nullptr) {
        if (src.m_customize) {
            m_customize = ut.alocpy(src.m_customize);
        }
    }

    //ASSIGNMENT OPERATOR
    Food& Food::operator=(const Food& src) {
        if (this != &src) {
            Billable::operator=(src);
            m_ordered = src.m_ordered;
            m_child = src.m_child;
            if (src.m_customize) {
                m_customize = ut.alocpy(src.m_customize);
            }
            else {
                delete[] m_customize;
                m_customize = nullptr;
            }
        }
        return *this;
    }

    //DESTRUCTOR
    Food::~Food() {
        delete[] m_customize;
    }

    //PRINT
    std::ostream& Food::print(std::ostream& ostr) const {
        ostr << std::left << std::setw(28) << std::setfill('.') << (const char*)*this;

        if (ordered()) {
            if (m_child) {
                ostr << "Child ";
            }
            else {
                ostr << "Adult ";
            }
        }
        else {
            ostr << "..... ";
        }

        ostr << std::right << std::setw(6) << std::setfill(' ') << std::fixed << std::setprecision(2) << price();

     
        if (m_customize && &ostr == &std::cout) {
            std::string customizeStr(m_customize);
            ostr << " >> " << customizeStr.substr(0, 30); 
        }

        return ostr;
    }



    //ORDER
    bool Food::order() {
        std::cout << "         Food Size Selection\n"
            << "          1- Adult\n"
            << "          2- Child\n"
            << "          0- Back\n"
            << "         > ";
        int choice = ut.getInt(0, 2);
        if (choice == 1) {
            m_child = false;
        }
        else if (choice == 2) {
            m_child = true;
        }
        else {
            m_ordered = false;
            delete[] m_customize;
            m_customize = nullptr;
            return false;
        }
        m_ordered = true;

        std::cout << "Special instructions\n> ";
        std::string input;
        std::getline(std::cin, input);
        if (!input.empty()) {
            m_customize = ut.alocpy(input.c_str());
        }
        else {
            delete[] m_customize;
            m_customize = nullptr;
        }
        return true;
    }

    //OREDERED
    bool Food::ordered() const {
        return m_ordered;
    }

    //READ
    std::ifstream& Food::read(std::ifstream& file) {
        std::string line;
        if (std::getline(file, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != std::string::npos) {
                std::string foodName = line.substr(0, commaPos);
                double price = std::stod(line.substr(commaPos + 1));
                name(foodName.c_str()); 
                Billable::price(price);           
            }
            m_child = false;
            m_ordered = false;
            delete[] m_customize;
            m_customize = nullptr;
        }
        return file;
    }

    //RETRUN PRICE
    double Food::price() const {
        if (m_ordered && m_child) {
            return Billable::price() / 2;  
        }
        return Billable::price();  
    }

}
