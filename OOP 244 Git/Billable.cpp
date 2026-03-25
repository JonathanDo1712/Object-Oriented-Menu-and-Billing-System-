#include "Billable.h"
#include "Utils.h"
#include <cstring>

namespace seneca {
    //PRICE SETTER
    void Billable::price(double value) {
        m_price = value;
    }

    //NAME SETTER
    void Billable::name(const char* name) {
        if (m_name) {
            delete[] m_name;
        }
        m_name = ut.alocpy(name);
    }

    //DEFAULT CONSTRUCTOR 
    Billable::Billable() : m_name(nullptr), m_price(0.0) {}

    //COPY CONSTRUCTOR
    Billable::Billable(const Billable& src) : m_name(nullptr), m_price(0.0) {
        *this = src;
    }

    //ASSIGNMENT OPERATOR
    Billable& Billable::operator=(const Billable& src) {
        if (this != &src) {
            name(src.m_name);
            m_price = src.m_price;
        }
        return *this;
    }

    //DESTRUCTOR
    Billable::~Billable() {
        delete[] m_name;
    }

    //PRICE GETTER
    double Billable::price() const {
        return m_price;
    }

    //CONVERT BILLABLE OBJECT TO NAME 
    Billable::operator const char* () const {
        return m_name;
    }

    // + ADD BILLABLE OBJECT PRICE TO VALUE
    double operator+(double money, const Billable& B) {
        return money + B.price();
    }

    // += ADD BILLABLE OBJECT PRICE TO VALUE
    double& operator+=(double& money, const Billable& B) {
        money += B.price();
        return money;
    }
}
