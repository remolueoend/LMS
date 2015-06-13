#ifndef ACTION_H
#define ACTION_H

#include "Selectable.h"
#include "LMS.h"
#include <functional>
#include <string>
#include "App.h"
#include "IO.h"

using namespace std;

/**
 * Wraps an executable action rendered in the navigation.
 */
class Action : public Selectable
{
    public:
        /**
         * Creates a new action instance.
         * \param sys A reference to a library management system
         * \param title The title to show in the navigation
         * \param handler The handler function to execute
         */
        Action(string title, std::function<void (LMS* sys, IO* io)> handler) : Selectable(title){
            pHandler = handler;
        };

        /** Default destructor */
        virtual ~Action(){ };

        /**
         * Executes the attached handler function
         */
        void Handle(LMS* sys, IO* io){
            pHandler(sys, io);
        }
    
        string GetTitle(){
            return Selectable::GetTitle();
        }

    protected:

    private:
        std::function<void (LMS* sys, IO* io)> pHandler;
};

#endif // ACTION_H
