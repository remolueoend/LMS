#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "LMS.h"
#include <vector>
#include "Menu.h"
#include "IO.h"
#include <string>
#include <functional>

class Menu;

/**
 * Manages the app's menus and actions and renders the navigation
 */
class Navigation
{
    public:
        /** Default constructor */
        Navigation(LMS* sys, IO* io){
            pSys = sys;
            pIO = io;
        }

        /** Default destructor */
        virtual ~Navigation(){};

        void Render(Menu* root);
        void OpenMenu(Menu* menu);
        void OpenItem(int index);
        void OpenMenu();

    protected:
    

    private:
        vector<Menu*> pOpenMenus;
        LMS* pSys;
        IO* pIO;
};

#endif // NAVIGATION_H
