#ifndef LMS_H
#define LMS_H

#include "Student.h"
#include "Book.h"
#include "Borrow.h"
#include "Record.h"
#include "List.h"
#include <string>
#include <vector>

using namespace std;


/**
 * Class offering a library management system
 */
class LMS
{
    public:
        /** Default constructor */
        LMS();

        /** Default destructor */
        virtual ~LMS(){};

        void AddStudent(Student* student);
        void AddStudent(string studentID, string name, string department, string email);

        void AddBook(Book* book);
        void AddBook(string ISBN, string title, string authors, string publisher, int year, int quantity);

        bool DeleteStudent(Student* student);
        bool DeleteBook(Book* book);

        Borrow* BorrowBook(Book* book, Student* student);
        Borrow* ReturnBook(Book* book, Student* student);

        List<Book*>* Books();
        List<Book*>* Books(std::function<bool (Book* s)> condition);

        List<Student*>* Students();
        List<Student*>* Students(std::function<bool (Student* s)> condition);

        List<Borrow*>* GetBorrowings();
        List<Borrow*>* GetBorrowings(bool overdueOnly);
        List<Borrow*>* GetBorrowings(Book* book);
        List<Borrow*>* GetBorrowings(Student* student);

        long QuantitiesLeft(Book* book);

        List<Record*>* GetRecords(Book* book);

    protected:

    private:
        List<Student*> pStudents;
        List<Book*> pBooks;
        List<Borrow*> pBorrows;
        List<Record*> pRecords;


};

#endif // LMS_H
