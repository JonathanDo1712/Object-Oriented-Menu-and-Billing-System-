#ifndef SENECA_DRINK_H
#define SENECA_DRINK_H

#include "Billable.h"

namespace seneca {
    class Drink : public Billable {
    private:
        char m_size;

    public:
        Drink();
        std::ostream& print(std::ostream& ostr = std::cout) const override;
        bool order() override;
        bool ordered() const override;
        std::ifstream& read(std::ifstream& file) override;
        double price() const override;
    };
}

#endif // !SENECA_DRINK_H
