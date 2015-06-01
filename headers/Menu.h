#ifndef MENU_H
#define MENU_H

#include "Selectable.h"
#include "List.h"
#include <vector>
#include <string>

using namespace std;

/**
 * Represents a single menu or sub menu of a navigation
 */
class Menu: public Selectable
{
    public:
        /** Default constructor */ 
        Menu(string title);

        /** Default destructor */
        virtual ~Menu();

        void AddSubItem(Selectable* item);
        vector<Selectable*> GetSubItems();
        void Render(vector<Menu*> menus);
    
        string GetTitle(){
            return Selectable::GetTitle();
        }

    protected:

    private:
        vector<Selectable*> pSubItems;

};

#endif // MENU_H
