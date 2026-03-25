#include "Drink.h"

#include <iomanip>
#include <cstring>

using namespace std;
namespace seneca {
    //DEFAULT CONSTRUCTOR
    Drink::Drink() : Billable(), m_size('\0') {}

    //PRINT
    std::ostream& Drink::print(std::ostream& ostr) const {
        ostr << std::left << std::setw(28) << std::setfill('.')
            << (const char*)(*this);

        switch (m_size) {
        case 'S': ostr << "SML.."; break;
        case 'M': ostr << "MID.."; break;
        case 'L': ostr << "LRG.."; break;
        case 'X': ostr << "XLR.."; break;
        default:  ostr << ".....";
        }

        ostr << std::right << std::setw(7) << std::setfill(' ')
            << std::fixed << std::setprecision(2) << price();

        return ostr;
    }

    //ORDER
    bool Drink::order() {
        std::cout << "         Drink Size Selection\n"
            << "          1- Small\n"
            << "          2- Medium\n"
            << "          3- Larg\n"
            << "          4- Extra Large\n"
            << "          0- Back\n         > ";
        int selection = ut.getInt(0, 4);
        switch (selection) {
        case 1: m_size = 'S'; break;
        case 2: m_size = 'M'; break;
        case 3: m_size = 'L'; break;
        case 4: m_size = 'X'; break;
        default: m_size = '\0'; return false;
        }
        return true;
    }

    //ORDERED
    bool Drink::ordered() const {
        return m_size != '\0';
    }

    //READ
    std::ifstream& Drink::read(std::ifstream& file) {
        char name[256];
        double price;
        if (file.getline(name, 256, ',') && file >> price) {
            file.ignore(1000, '\n');
            this->name(name);
            this->Billable::price(price); 
            m_size = '\0';
        }
        return file;
    }

    //RETURN PRICE BASE ON SIZE
    double Drink::price() const {
        switch (m_size) {
        case 'S': return Billable::price() * 0.5;
        case 'M': return Billable::price() * 0.75;
        case 'L': return Billable::price();
        case 'X': return Billable::price() * 1.5;
        default:  return Billable::price();
        }
    }
}
