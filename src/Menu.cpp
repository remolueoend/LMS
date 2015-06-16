#include "../headers/Menu.h"
#include <iostream>
#include "../headers/Action.h"

using namespace std;

Menu::Menu(string title)
    : Selectable(title)
{ }

Menu::~Menu()
{
    //dtor
}

void Menu::AddSubItem(Selectable* item){
    pSubItems.push_back(item);
}

void Menu::AddAction(string title, void (*handler)(LMS *sys, IO *io)) {
    AddSubItem(new Action(title, handler));
}

vector<Selectable*> Menu::GetSubItems(){
    return pSubItems;
}

void Menu::Render(vector<Menu*> menus){
    for (typename std::vector<Menu*>::iterator it = menus.begin(); it != menus.end(); ++it){
        if(it - menus.begin() > 0){
            cout << " > ";
        }
        cout << (*it)->GetTitle();
    }
    cout << endl << "============================================" << endl;

    vector<Selectable*>::iterator it = pSubItems.begin();
    for (it=pSubItems.begin(); it!=pSubItems.end(); ++it) {
        cout << (it - pSubItems.begin()) + 1 << ": " << (*it)->GetTitle() << endl;
    }
}
