#include "../headers/Menu.h"
#include "../headers/Action.h"
#include <iostream>
#include "../headers/EscapeException.h"

using namespace std;

void App::Render(Menu *root) {
    OpenMenu(root);
}

void App::OpenItem(int index) {
    Menu* cMenu = pOpenMenus.back();
    if(index > cMenu->GetSubItems().size() || index < 1){
        throw invalid_argument("Invalid index.");
    }
    Selectable* cItem = cMenu->GetSubItems()[index - 1];

    if (Menu *m = dynamic_cast<Menu *>(cItem)) {
        OpenMenu(m);
    } else if (Action *a = dynamic_cast<Action *>(cItem)) {
        cout << endl << a->GetTitle() << ":" << endl;
        try{
            a->Handle(pSys, pIO);
        }catch(EscapeException& ex){
            cout << "Canceled." << endl;
        }catch(exception& ex){
            cout << "Error: " << ex.what() << endl;
        }
        OpenMenu();
    }else{
        throw runtime_error("Unhandled selectable item detected");
    }
}

void App::OpenMenu() {
    if(pOpenMenus.size() == 0){
        return;
    }
    Menu* cm = pOpenMenus.back();
    int maxIndex = (int) cm->GetSubItems().size();
    cout << endl;
    cm->Render(pOpenMenus);

    try{
        int selection = pIO->readInt(">> your choice", 1, maxIndex);
        OpenItem(selection);
    }catch(EscapeException& ex){
        if(pOpenMenus.size() > 1){
            pOpenMenus.pop_back();
        }else{
            cout << "Do you really want to quit (y or n)? ";
            string ans = "";
            cin >> ans;
            if(ans == "y" || ans == "yes"){
                return;
            }
        }
        OpenMenu();
    }
}

void App::OpenMenu(Menu *menu) {
    pOpenMenus.push_back(menu);
    OpenMenu();
}