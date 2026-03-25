#ifndef SENECA_FOOD_H
#define SENECA_FOOD_H

#include "Billable.h"

namespace seneca {
    class Food : public Billable {
    private:
        bool m_ordered; 
        bool m_child;    
        char* m_customize; 

    public:

        Food();
        Food(const Food& src);
        Food& operator=(const Food& src);
        virtual ~Food();

        virtual std::ostream& print(std::ostream& ostr = std::cout) const override;
        virtual bool order() override;
        virtual bool ordered() const override;
        virtual std::ifstream& read(std::ifstream& file) override;
        virtual double price() const override;

    };
}

#endif // !SENECA_FOOD_H
