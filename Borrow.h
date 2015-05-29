#ifndef BORROW_H
#define BORROW_H

#include <sys/time.h>
#include "Student.h"
#include "Book.h"

class Borrow
{
    public:
        /** Default constructor */
        Borrow(Student* student, Book* book);

        /** Default destructor */
        virtual ~Borrow();

        /** Access pStudent
         * \return The current value of pStudent
         */
        Student* GetStudent() { return pStudent; }

        /** Set pStudent
         * \param val New value to set
         */
        void SetStudent(Student* val) { pStudent = val; }

        /** Access pBook
         * \return The current value of pBook
         */
        Book* GetBook() { return pBook; }

        /** Set pBook
         * \param val New value to set
         */
        void SetBook(Book* val) { pBook = val; }

        /** Access timestamp
         * \return The current value of timestamp
         */
        long GetTimestamp() { return pTimestamp; }

        /** Set timestamp
         * \param val New value to set
         */
        void SetTimestamp(long val) { pTimestamp = val; }

        /** Returns true if the book is borrowed for more than 30 days
         * \return If the borrow is overdue
         */
        bool IsOverdue();

    protected:

    private:
        Student* pStudent; //!< Member variable "pStudent"
        Book* pBook; //!< Member variable "pBook"
        long pTimestamp; //!< Member variable "timestamp"
};

#endif // BORROW_H
