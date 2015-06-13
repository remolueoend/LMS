//
// Created by Remo Zumsteg on 13/06/15.
//

#ifndef LMS_ACTIONS_H
#define LMS_ACTIONS_H

#include "Action.h"


class Actions {
public:
    static Action* CreateBook;
    static Action* RemoveBook;
    static Action* UpdateBook;
    static Action* CreateStudent;
    static Action* RemoveStudent;
    static Action* UpdateStudent;
    static Action* BorrowBook;
    static Action* ReturnBook;
    static Action* BooksInfo;
    static Action* BorrowedBooks;
    static Action* OverdueBooks;
    static Action* StudentsInfo;
    static Action* ShowRecords;
    static Action* ExportBooks;
    static Action* ExportStudents;
};


#endif //LMS_ACTIONS_H
