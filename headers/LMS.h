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

        List<Borrow*>* BorrowedBooks(){
            return &pBorrows;
        }

        List<Borrow*>* OverdueBooks(){
            return BorrowedBooks()->Filter([](Borrow* b) -> bool { return b->IsOverdue(); });
        }

        void AddStudent(Student* student);
        void AddStudent(int studentID, string name, string department, string email);

        void AddBook(Book* book);
        void AddBook(double ISBN, string title, string authors, string publisher, int year, int quantity);

        bool DeleteStudent(Student* student);
        bool DeleteStudent(int studentID);

        bool DeleteBook(Book* book);
        bool DeleteBook(double ISBN);

        Borrow* BorrowBook(double ISBN, int studentID);
        Borrow* BorrowBook(double ISBN, Student* student);
        Borrow* BorrowBook(double ISBN, string studentName);
        Borrow* BorrowBook(Book* book, int studentID);
        Borrow* BorrowBook(Book* book, Student* student);
        Borrow* BorrowBook(Book* book, string studentName);
        Borrow* BorrowBook(string bookTitle, int studentID);
        Borrow* BorrowBook(string bookTitle, Student* student);
        Borrow* BorrowBook(string bookTitle, string studentName);

        Borrow* ReturnBook(Book* book, Student* student);

        List<Book*>* Books(std::function<bool (Book* s)> condition);
        Book* BookByISBN(double ISBN);
        Book* BookByTitle(string bookTitle);

        List<Student*>* Students(std::function<bool (Student* s)> condition);
        Student* StudentByID(int studentID);
        Student* StudentByName(string studentName);

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
