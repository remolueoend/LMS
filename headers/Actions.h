//
// Created by Remo Zumsteg on 13/06/15.
//

#ifndef LMS_ACTIONS_H
#define LMS_ACTIONS_H

#include "Action.h"
#include "IO.h"
#include "LMS.h"
#include "Student.h"
#include "Book.h"


class Actions {
public:
    static void CreateBook(LMS *sys, IO *io);

    static void RemoveBook(LMS *sys, IO *io);

    static void UpdateBook(LMS *sys, IO *io);

    static void CreateStudent(LMS *sys, IO *io);

    static void RemoveStudent(LMS *sys, IO *io);

    static void UpdateStudent(LMS *sys, IO *io);

    static void BorrowBook(LMS *sys, IO *io);

    static void ReturnBook(LMS *sys, IO *io);

    static void BooksInfo(LMS *sys, IO *io);

    static void BorrowedBooks(LMS *sys, IO *io);

    static void OverdueBooks(LMS *sys, IO *io);

    static void StudentsInfo(LMS *sys, IO *io);

    static void ShowRecords(LMS *sys, IO *io);

    static void ExportBooks(LMS *sys, IO *io);

    static void ExportStudents(LMS *sys, IO *io);

private:
    static string getBookDetails(Book *book, List<Borrow *> *borrowings);

    static string getStudentDetails(Student *student, List<Borrow *> *borrowings);
};


#endif //LMS_ACTIONS_H
