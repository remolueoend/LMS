#include "LMS.h"
#include "Student.h"
#include "Book.h"
#include "Borrow.h"
#include <stdexcept>

LMS::LMS()
{
    //ctor
}

/** Adds a book to the system and throws an exception if a book with the same ISB already exists.
 * \param book The book to add.
 */
void LMS::AddBook(Book* book){
    if(pBooks.Any([book](Book* b) -> bool { return b->GetISBN() == book->GetISBN(); })){
        throw runtime_error("A book with the same ISBN is already registered.");
    }
    this->pBooks.Add(book);
}

void LMS::AddBook(double ISBN, string title, string authors, string publisher, int year, int quantity){
    this->AddBook(new Book(ISBN, title, authors, publisher, year, quantity));
}

void LMS::AddStudent(Student* student){
    if(pStudents.Any([student](Student* s) -> bool { return s->GetStudentId() == student->GetStudentId(); })){
        throw std::invalid_argument("A student with the same student ID is already registered.");
    }
    this->pStudents.Add(student);
}

void LMS::AddStudent(int studentID, string name, string department, string email){
    this->AddStudent(new Student(studentID, name, department, email));
}

bool LMS::DeleteBook(Book* book){
    return pBooks.Remove(book);
}

bool LMS::DeleteBook(double ISBN){
    return pBooks.RemoveFirst([ISBN](Book* b) -> bool{ return b->GetISBN() == ISBN; });
}

bool LMS::DeleteStudent(Student* student){
    return pStudents.Remove(student);
}

bool LMS::DeleteStudent(int studentID){
    return pStudents.RemoveFirst([studentID](Student* s) -> bool { return s->GetStudentId() == studentID; });
}

Borrow* LMS::BorrowBook(Book* book, Student* student){
    if(!pBooks.Exists(book)){
        throw std::invalid_argument("Book is not registered");
    }
    if(!pStudents.Exists(student)){
        throw std::invalid_argument("Student is not registered");
    }

    int q = book->GetQuantity();
    if(q > 0){
        book->SetQuantity(q - 1);
        Borrow* newBorrow = new Borrow(student, book);
        pBorrows.Add(newBorrow);
        return newBorrow;
    }else{
        throw std::logic_error("Book is currently unavailable");
    }
}

Borrow* LMS::BorrowBook(Book* book, int studentID){
    return BorrowBook(book, StudentByID(studentID));
}

Borrow* LMS::BorrowBook(Book* book, string studentName){
    return BorrowBook(book, StudentByName(studentName));
}

Borrow* LMS::BorrowBook(double ISBN, Student* student){
    return BorrowBook(BookByISBN(ISBN), student);
}

Borrow* LMS::BorrowBook(double ISBN, int studentID){
    return BorrowBook(BookByISBN(ISBN), studentID);
}

Borrow* LMS::BorrowBook(double ISBN, string studentName){
    return BorrowBook(BookByISBN(ISBN), studentName);
}

Borrow* LMS::BorrowBook(string bookTitle, Student* student){
    return BorrowBook(BookByTitle(bookTitle), student);
}

Borrow* LMS::BorrowBook(string bookTitle, int studentID){
    return BorrowBook(bookTitle, StudentByID(studentID));
}

Borrow* LMS::BorrowBook(string bookTitle, string studentName){
    return BorrowBook(BookByTitle(bookTitle), StudentByName(studentName));
}

Borrow* LMS::ReturnBook(Book* book){
    Borrow* b = pBorrows.First([book](Borrow* b) -> bool { return b->GetBook() == book; });
    if(b == NULL){
        throw std::invalid_argument("The given book was never borrowed.");
    }
    book->SetQuantity(book->GetQuantity() + 1);
    pBorrows.Remove(b);
    
    return b;
}

Borrow* LMS::ReturnBook(double ISBN){
    Book* b = BookByISBN(ISBN);
    return ReturnBook(b);
}

Borrow* LMS::ReturnBook(string bookTitle){
    Book* b = BookByTitle(bookTitle);
    return ReturnBook(b);
}

Book* LMS::BookByISBN(double ISBN){
    Book* b = pBooks.First([ISBN](Book* b) -> bool{ return b->GetISBN() == ISBN; });
    if(b == NULL){
        throw std::invalid_argument("Could not find a book with the given ISBN.");
    }
    return b;
}

Book* LMS::BookByTitle(string bookTitle){
    List<Book*>* bks = pBooks.Filter([bookTitle](Book* b) -> bool { return b->GetTitle() == bookTitle; });
    if(bks->Count() > 1){
        throw std::invalid_argument("Multiple books found with the same title. Use the ISBN instead.");
    } else if(bks->Count() == 0){
        throw std::invalid_argument("Could not find a book with the given title.");
    }
    return bks->First();
}

Student* LMS::StudentByID(int studentID){
    Student* s = pStudents.First([studentID](Student* s) -> bool { return s->GetStudentId() == studentID; });
    if(s == NULL){
        throw std::invalid_argument("Could not find a student with the given student ID.");
    }
    return s;
}

Student* LMS::StudentByName(string studentName){
    List<Student*>* stds = pStudents.Filter([studentName](Student* s) -> bool { return s->GetName() == studentName; });
    if(stds->Count() > 1){
        throw std::invalid_argument("Multiple students found with the same name. Use the student ID instead.");
    } else if(stds->Count() == 0){
        throw std::invalid_argument("Could not find a student with the given name.");
    }
    return stds->First();
}


LMS::~LMS()
{
    //dtor
}
