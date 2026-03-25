#ifndef SENECA_MENU_H
#define SENECA_MENU_H

#include "constants.h"
#include "Utils.h"

#include <iostream> 
#include <iomanip>

namespace seneca {
    
    class Menu;

    class MenuItem {
    private:
        char* m_content;
        size_t m_indentCount;
        size_t m_indentSize;
        int m_itemNumber;

    //public:
        MenuItem(const char* content, size_t indentCount, size_t indentSize, int itemNumber);

        ~MenuItem();
        //Copy Constructor 
        MenuItem(const MenuItem& other) = delete;
        //Copy Assignment Operator 
        MenuItem& operator=(const MenuItem& other) = delete;

        //Conversion operator: Allows MenuItem object be evaluated as boolean
        operator bool() const;

        std::ostream& display(std::ostream& ostr = std::cout) const;

        friend class Menu;
    };

    class Menu {
    private: 
        size_t m_indentCount;
        size_t m_indentSize;
        size_t m_menuItemCount;

        MenuItem m_title;             
        MenuItem m_exit;        
        MenuItem m_prompt;   

        MenuItem* m_menuItems[MaximumNumberOfMenuItems]; 

    public:
        Menu(const char* title, const char* exitOption = "Exit", size_t indentCount = 0, size_t indentSize = 3);

        Menu& operator<<(const char* content);

        ~Menu();
        // Deleted copy constructor and assignment operator
        Menu(const Menu& other) = delete;
        Menu& operator=(const Menu& other) = delete;

        size_t select() const;

        friend size_t operator<<(std::ostream& ostr, const Menu& m);
    };

}

#endif // !SENECA_MENU_H

