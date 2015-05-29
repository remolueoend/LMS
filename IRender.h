#ifndef IRENDER_H
#define IRENDER_H

#include <string>

class ISelectable
{
    public:
        /** Default constructor */
        ISelectable() {}
        /** Default destructor */
        virtual ~ISelectable() {}

    protected:
        string title;
        int number;

    private:
};

#endif // IRENDER_H
