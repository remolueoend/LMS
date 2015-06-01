#include "../headers/LMS.h"
#include "../headers/Student.h"
#include "../headers/Book.h"
#include "../headers/Borrow.h"
#include "../headers/Record.h"
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

    long borrowCount = GetBorrowings(book)->Count();
    int q = book->GetQuantity();
    if(borrowCount < q){
        Borrow* newBorrow = new Borrow(student, book);
        pBorrows.Add(newBorrow);
        pRecords.Add(new Record(BORROW, book, student));
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

Borrow* LMS::ReturnBook(Book* book, Student* student){
    Borrow* b = pBorrows.First([book, student](Borrow* b) -> bool { return b->GetBook() == book && b->GetStudent() == student; });
    if(b == NULL){
        throw std::invalid_argument("This book was not borrowed by this student.");
    }
    pBorrows.Remove(b);
    pRecords.Add(new Record(RETURN, book, student));

    return b;
}

Book* LMS::BookByISBN(double ISBN){
    Book* b = pBooks.First([ISBN](Book* b) -> bool{ return b->GetISBN() == ISBN; });
    if(b == NULL){
        throw std::invalid_argument("Could not find a book with the given ISBN.");
    }
    return b;
}

List<Book *> *LMS::Books(std::function<bool(Book *s)> condition) {
    return pBooks.Filter(condition);
}

Book* LMS::BookByTitle(string bookTitle){
    List<Book*>* bks = Books([bookTitle](Book* b) -> bool { return b->GetTitle() == bookTitle; });
    if(bks->Count() > 1){
        throw std::invalid_argument("Multiple books found with the same title. Use the ISBN instead.");
    } else if(bks->Count() == 0){
        throw std::invalid_argument("Could not find a book with the given title.");
    }
    return bks->First();
}

List<Student *> *LMS::Students(std::function<bool(Student *s)> condition) {
    return pStudents.Filter(condition);
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

List<Borrow*>* LMS::GetBorrowings(bool overdueOnly) {
    if(overdueOnly){
        return pBorrows.Filter([](Borrow* b) -> bool { return b->IsOverdue(); });
    }else{
        return &pBorrows;
    }
}

List<Borrow*>* LMS::GetBorrowings() {
    return GetBorrowings(false);
}

List<Borrow*>* LMS::GetBorrowings(Book *book) {
    return pBorrows.Filter([book](Borrow* b) -> bool {
        return b->GetBook() == book;
    });
}

List<Borrow*>* LMS::GetBorrowings(Student *student) {
    return pBorrows.Filter([student](Borrow* b) -> bool {
        return b->GetStudent() == student;
    });
}

long LMS::QuantitiesLeft(Book *book) {
    return book->GetQuantity() - GetBorrowings(book)->Count();
}

List<Record *> *LMS::GetRecords(Book *book) {
    return pRecords.Filter([book](Record* r) -> bool { return r->ISBN() == book->GetISBN(); });
}
