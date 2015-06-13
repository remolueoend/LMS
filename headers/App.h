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
class App
{
    public:
        /** Default constructor */
        App(LMS *sys, IO *io) {
            pSys = sys;
            pIO = io;
        }

        /** Default destructor */
        virtual ~App() { };

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
