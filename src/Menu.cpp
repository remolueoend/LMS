#include "Menu.h"
#include "Selectable.h"
#include <iostream>
#include <string>
#include <vector>

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

vector<Selectable*> Menu::GetSubItems(){
    return pSubItems;
}

void Menu::Render(){
    cout << this->GetTitle() << endl;
    cout << "============================================" << endl;

    vector<Selectable*>::iterator it = pSubItems.begin();
    for (it=pSubItems.begin(); it!=pSubItems.end(); ++it) {
        cout << (it - pSubItems.begin()) + 1 << ": " << (*it)->GetTitle() << endl;
    }
}
