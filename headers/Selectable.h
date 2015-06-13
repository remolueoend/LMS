#ifndef SELECTABLE_H
#define SELECTABLE_H

#include <string>

using namespace std;

class App;

/**
 * Base class of selectable menu items, such as sub menus or actions
 */
class Selectable
{
    public:
        /** Default constructor */
        Selectable(string title);
    
        /** Default destructor */
        virtual ~Selectable(){  };
    
        /** Access pTitle
         * \return The current value of pTitle
         */
        virtual string GetTitle() {
            return pTitle;
        }
    
    protected:
        string pTitle; //!< Member variable "pTitle"

    private:
};

#endif // SELECTABLE_H
