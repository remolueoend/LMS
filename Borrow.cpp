#include "Borrow.h"

#include <ctime>
#include "Student.h"
#include "Book.h"

Borrow::Borrow(Student* student, Book* book)
{
    this->pStudent = student;
    this->pBook = book;
    // initialize the timestamp with the current time.
    SetTimestamp(time(0));
}

bool Borrow::IsOverdue(){
    // 30 * 24 * 3600 = 30 days in seconds:
    return difftime(time(0), this->GetTimestamp()) > 30 * 24 * 3600;
}

Borrow::~Borrow()
{
    //dtor
}
