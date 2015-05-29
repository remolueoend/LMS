#ifndef LMS_App_h
#define LMS_App_h

#include "Navigation.h"
#include "LMS.h"

class LMS;
class Navigation;

class App{

public:
    LMS* LMS(){
        return pLMS;
    }
    
    Navigation* Nav(){
        return pNav;
    }
    
private:
    LMS* pLMS;
    Navigation* pNav;
    
};


#endif
