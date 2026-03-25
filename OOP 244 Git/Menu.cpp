#include "Menu.h"

namespace seneca {
    //
    //MENU ITEM 
    //

    //CONSTRUCTOR 
    MenuItem::MenuItem(const char* content, size_t indentCount, size_t indentSize, int itemNumber)
        : m_indentCount(indentCount), m_indentSize(indentSize), m_itemNumber(itemNumber)
    {
        //allcate memory if needed
        if (content && content[0] != '\0') {
            m_content = ut.alocpy(content);
        }
        else {
            m_content = nullptr;
        }

        //validate
        if (m_content == nullptr || ut.isspace(m_content) ||
            indentCount > 4 || indentSize > 4 ||
            (itemNumber > 0 && static_cast<size_t>(itemNumber) > MaximumNumberOfMenuItems)) {
            m_indentCount = 0;
            m_indentSize = 0;
            m_itemNumber = 0;
            delete[] m_content;
            m_content = nullptr;
        }

    }

    //DESTRUCTOR 
    MenuItem::~MenuItem() {
        delete[] m_content;
        m_content = nullptr;
    }

    //CONVERSION OPERATOR
    MenuItem::operator bool() const {
        return m_content != nullptr;
    }

    //DISPLAY FUNCTION
    std::ostream& MenuItem::display(std::ostream& ostr) const {
        //validate
        if (!m_content || m_content[0] == '\0' || Utils().isspace(m_content)) {
            ostr << "??????????";
        }
        else {
            //indent
            for (size_t i = 0; i < m_indentCount * m_indentSize; ++i) {
                ostr << ' ';
            }

            //itertion number
            if (m_itemNumber >= 0) {
                ostr.width(2);
                ostr << m_itemNumber << "- ";
            }

            //skipping white lines
            const char* contentStart = m_content;
            while (contentStart && Utils().isspace(*contentStart)) {
                ++contentStart;
            }

            ostr << contentStart;
        }

        return ostr;
    }

    //
    //MENU 
    //

    // CONSTRUCTOR
    Menu::Menu(const char* title, const char* exitOption, size_t indentCount, size_t indentSize)
        : m_indentCount(indentCount),            
        m_indentSize(indentSize),              
        m_menuItemCount(0),                         
        m_title(title, 0, 3, 1),                
        m_exit(exitOption, 0, 3, 0),            
        m_prompt(">", indentCount, indentSize, -1),
        m_menuItems()
    {
        for (size_t i = 0; i < MaximumNumberOfMenuItems; ++i) {
            m_menuItems[i] = nullptr;
        }
    }

    // ADD ITEM OPERATOR
    Menu& Menu::operator<<(const char* content) {
        if (m_menuItemCount < MaximumNumberOfMenuItems) {
            m_menuItems[m_menuItemCount] = new MenuItem(content, m_indentCount, m_indentSize, m_menuItemCount + 1);
            ++m_menuItemCount;
        }
        return *this;
    }

    // DESTRUCTOR
    Menu::~Menu() {
        for (size_t i = 0; i < MaximumNumberOfMenuItems; ++i) {
            delete m_menuItems[i];  
            m_menuItems[i] = nullptr;
        }
    }

    // SELECT FUNCTION
    size_t Menu::select() const {
        size_t selection;

        if (m_title.m_content != nullptr && m_title.m_content[0] != '\0') {
            std::cout << std::string(m_indentCount * m_indentSize, ' ') << m_title.m_content << std::endl;
        }

        for (size_t i = 0; i < m_menuItemCount; ++i) {
            if (m_menuItems[i] != nullptr) {
                std::cout << std::string(m_indentCount * m_indentSize , ' ')
                    << std::setw(2) << std::setfill(' ') << i + 1<< "- " << m_menuItems[i]->m_content << std::endl;
            }
        }

        std::cout << std::string(m_indentCount * m_indentSize, ' ')
            << std::setw(2) << std::setfill(' ') << "0" << "- " << m_exit.m_content << std::endl;

        std::cout << std::string(m_indentCount * m_indentSize, ' ') << m_prompt.m_content << " ";

        selection = ut.getInt(0, m_menuItemCount);

        return selection;
    }

    // DISPLAY FUNCTION
    size_t operator<<(std::ostream& ostr, const Menu& m) {
        if (&ostr == &std::cout) {
            return m.select();
        }
        else {
            return 0;
        }
    }


}