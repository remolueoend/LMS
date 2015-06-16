//
// Created by Remo Zumsteg on 13/06/15.
//

#include "../headers/Actions.h"
#include <iostream>
#include "../headers/GroupableList.h"
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

// Helper functions

/**
 * Returns a pretty printed string of the gven book and its borrowings
 */
string Actions::getBookDetails(Book *book, List<Borrow *> *borrowings) {
    stringstream ss;
    ss << "ISBN:\t\t" << book->GetISBN() << endl;
    ss << "title:\t\t" << book->GetTitle() << endl;
    ss << "author:\t\t" << book->GetAuthors() << endl;
    ss << "publisher:\t" << book->GetPublisher() << endl;
    ss << "year:\t\t" << book->GetYear() << endl;
    ss << "quantity:\t" << book->GetQuantity() << endl;
    ss << "books left:\t" <<  book->GetQuantity() - borrowings->Count() << endl;

    if(borrowings->Count() > 0) {
        ss << endl << "Borrowed " << borrowings->Count() << " time(s) by:" << endl;
        borrowings->ForEach([&ss](Borrow *bor) -> void {
            ss << "ID: " << bor->GetStudent()->GetStudentId()
            << ", name: " << bor->GetStudent()->GetName()
            << ", overdue: " << (bor->IsOverdue() ? "yes" : "no")
            << endl;
        });
    }else{
        ss << "This book is not borrowed by anyone." << endl;
    }

    return ss.str();
}

/**
 * Returns a pretty printed string of the gven book and its borrowings
 */
string Actions::getStudentDetails(Student *student, List<Borrow *> *borrowings) {
    stringstream ss;
    ss << "student ID:\t" << student->GetStudentId() << endl;
    ss << "name:\t\t" << student->GetName() << endl;
    ss << "department:\t" << student->GetDepartment() << endl;
    ss << "e-mail:\t\t" << student->GetEmail() << endl;

    if(borrowings->Count() > 0){
        ss << endl << "Borrowed " << borrowings->Count() << " book(s):" << endl;
        borrowings->ForEach([&ss](Borrow* b) -> void {
            ss
            << "ISBN: " << b->GetBook()->GetISBN()
            << ", title: " << b->GetBook()->GetTitle()
            << ", overdue: " << (b->IsOverdue() ? "yes" : "no")
            << endl;
        });
    }else{
        ss << "No books borrowed so far." << endl;
    }

    return ss.str();
}

/**
 * Allows registering a new book by entering all necessary information.
 */
void Actions::CreateBook(LMS *sys, IO *io) {
    string isbn = io->readISBN();
    string title = io->read("title");
    string author = io->read("author");
    string publisher = io->read("publisher");
    int year = io->readInt("year (-5000 - 3000)", -5000, 3000);
    int quantity = io->readInt("quantity (max: 10000)", 1, 10000);

    sys->AddBook(isbn, title, author, publisher, year, quantity);
    cout << "Book successfully registered." << endl;
};

/**
 * Allows selecting a single book and delete it
 */
void Actions::RemoveBook(LMS *sys, IO *io) {
    Book* book = io->readBook(sys);
    sys->DeleteBook(book);
    cout << "Book was deleted successfully." << endl;
};

/**
 * Allows registering a new student by entering all necessary information.
 */
void Actions::CreateStudent(LMS *sys, IO *io) {
    string studentId = io->readStudentID();
    string name = io->read("name");
    string dept = io->read("department");
    string email = io->read("e-mail");

    sys->AddStudent(studentId, name, dept, email);
    cout << "Stundent successfully registered" << endl;
};

/**
 * Allows querying for a single student and delete it.
 */
void Actions::RemoveStudent(LMS *sys, IO *io) {
    Student* student = io->readStudent(sys);
    sys->DeleteStudent(student);
    cout << "Stundent was deleted successfully." << endl;
};

/**
 * Allows borrowing a book by querying for a single student and book.
 */
void Actions::BorrowBook(LMS *sys, IO *io) {
    Book* book = io->readBook(sys);
    Student* student = io->readStudent(sys);
    sys->BorrowBook(book, student);
    cout << "Book borrowed successfully. Quantity left: " << sys->QuantitiesLeft(book) << endl;

};

/**
 * Allows returning a book by querying for the book and the student.
 */
void Actions::ReturnBook(LMS *sys, IO *io) {
    Book* book = io->readBook(sys);
    Student* student = io->readStudent(sys);
    sys->ReturnBook(book, student);
    cout << "Book returned successfully. Quantity left: " << sys->QuantitiesLeft(book) << endl;
};

/**
 *  Allows querying for one or more books and shows the details about the found books.
 */
void Actions::BooksInfo(LMS *sys, IO *io) {
    List<Book*>* books = io->readBooks(sys, true);
    cout << endl << "Found " << books->Count() << " book(s):" << endl;
    books->ForEach([sys](Book* b) -> void {
        cout << "---------------------------------------------------" << endl;
        List<Borrow*>* borrowings = sys->GetBorrowings(b);
        cout << getBookDetails(b, borrowings);
    });
};

/**
 * Shows a detailed list of all books which are borrowed and by whom.
 */
void Actions::BorrowedBooks(LMS *sys, IO *io) {
    GroupableList<Book*, Borrow*>* list = new GroupableList<Book*, Borrow*>(sys->GetBorrowings());
    Dictionary<Book*, List<Borrow*>*> dict = list->GroupBy([](Borrow* b) -> Book* { return b->GetBook(); });
    if(dict.Count() > 0){
        dict.ForEach([](KeyValuePair<Book*, List<Borrow*>*>* pair) -> void {
            cout << "---------------------------------------------------" << endl;
            cout << getBookDetails(pair->Key(), pair->Value());
        });
    }else{
        cout << "Currenty no books are borrowed." << endl;
    }
};

/**
 * Shows a list of all borrowed books which are overdue.
 */
void Actions::OverdueBooks(LMS *sys, IO *io) {
    GroupableList<Book*, Borrow*>* list = new GroupableList<Book*, Borrow*>(sys->GetBorrowings(true));
    Dictionary<Book*, List<Borrow*>*> dict = list->GroupBy([](Borrow* b) -> Book* { return b->GetBook(); });
    if(dict.Count() > 0){
        dict.ForEach([](KeyValuePair<Book*, List<Borrow*>*>* pair) -> void {
            cout << "---------------------------------------------------" << endl;
            cout << getBookDetails(pair->Key(), pair->Value());
        });
    }else{
        cout << "Currenty no books are overdue." << endl;
    }
};

/**
 * Shows detailed information about one or more students.
 */
void Actions::StudentsInfo(LMS *sys, IO *io) {
    List<Student*>* students = io->readStudents(sys, true);
    cout << endl << "Found " << students->Count() << " student(s):" << endl;
    students->ForEach([sys](Student* s) -> void {
        cout << "---------------------------------------------------" << endl;
        List<Borrow*>* borrowings = sys->GetBorrowings(s);
        cout << getStudentDetails(s, borrowings);
    });
};

/**
 * Allows querying for a single book and update its properties.
 */
void Actions::UpdateBook(LMS *sys, IO *io) {
    Book* book = io->readBook(sys);
    Book* nb = new Book();

    cout << "Enter the new data. To keep a current value, just press enter:" << endl;

    nb->SetISBN(io->readISBN(true, book->GetISBN()));
    nb->SetTitle(io->read("book title", true, book->GetTitle()));
    nb->SetAuthors(io->read("author", true, book->GetAuthors()));
    nb->SetPublisher(io->read("publsher", true, book->GetPublisher()));
    nb->SetYear(io->readInt("year", -5000, 3000, true, book->GetYear()));
    nb->SetQuantity(io->readInt("quantity", true, book->GetQuantity()));

    book->Update(nb);
    cout << "Book updated successfully." << endl;
};

/**
 * ALlows querying for a single student and update its properties.
 */
void Actions::UpdateStudent(LMS *sys, IO *io) {
    Student* student = io->readStudent(sys);
    Student* ns = new Student();

    cout << "Enter the new data. To keep a current value, just press enter:" << endl;

    ns->SetStudentId(io->readStudentID(true, student->GetStudentId()));
    ns->SetName(io->read("student name", true, student->GetName()));
    ns->SetEmail(io->read("e-mail", true, student->GetEmail()));
    ns->SetDepartment(io->read("department", true, student->GetDepartment()));

    student->Update(ns);
    cout << "Student updated successfully." << endl;
};

/**
 * Allows querying for a single book and shows its record list.
 */
void Actions::ShowRecords(LMS *sys, IO *io) {
    Book* book = io->readBook(sys);
    List<Record*>* records = sys->GetRecords(book);

    cout
    << "Records for book " << book->GetISBN() << ": "
    << book->GetTitle() << " (" << book->GetAuthors() << "):" << endl;

    if(records->Count() == 0){
        cout << "No records found." << endl;
        return;
    }
    records->ForEach([](Record* r) -> void {
        cout << "---------------------------------------------------" << endl;
        cout
        << r->GetDateTimeStr() << ": "
        << (r->GetType() == BORROW ? "borrowed" : "returned") << " by: "
        << r->StudentName() << " (" << r->StudentID() << ")"
        << endl;
    });
};

/**
 * Allows exporting all book records to the specified file path.
 */
void Actions::ExportBooks(LMS *sys, IO *io) {
    cout << "The information of all registered books will be stored in the given path." << endl;
    cout << "If the path already exists, the existing file will be replaced!" << endl;
    cout << "The provided path can be relative to the LMS executable's location or a static path." << endl;

    string filePath = io->read("file name", true, "books.txt");

    ofstream myfile;
    myfile.open(filePath, ios::trunc);

    cout << endl << "Exporting " << sys->Books()->Count() << " books..." << endl;
    sys->Books()->ForEach([sys, &myfile](Book* b) -> void {
        myfile << "---------------------------------------------------" << endl;
        List<Borrow*>* borrowings = sys->GetBorrowings(b);
        myfile << getBookDetails(b, borrowings);
    });

    myfile.close();
    cout << "Export done." << endl;
};

/**
 * Allows exporting all student records to the specified file path.
 */
void Actions::ExportStudents(LMS *sys, IO *io) {
    cout << "The information of all registered students will be stored in the given path." << endl;
    cout << "If the path already exists, the existing file will be replaced!" << endl;
    cout << "The provided path can be relative to the LMS executable's location or a static path." << endl;

    string filePath = io->read("file name", true, "students.txt");

    ofstream myfile;
    myfile.open(filePath, ios::trunc);

    cout << endl << "Exporting " << sys->Students()->Count() << " students..." << endl;
    sys->Students()->ForEach([sys, &myfile](Student* s) -> void {
        myfile << "---------------------------------------------------" << endl;
        List<Borrow*>* borrowings = sys->GetBorrowings(s);
        myfile << getStudentDetails(s, borrowings);
    });

    myfile.close();
    cout << "Export done." << endl;
};

void Actions::ShowAllBooks(LMS *sys, IO *io) {
    List<Book *> *books = sys->Books();
    cout << books->Count() << " book(s) are registered in the system." << endl;
    books->ForEach([sys](Book *b) -> void {
        cout << "---------------------------------------------------" << endl;
        List<Borrow *> *borrowings = sys->GetBorrowings(b);
        cout << getBookDetails(b, borrowings);
    });
}

void Actions::ShowAllStudents(LMS *sys, IO *io) {
    List<Student *> *students = sys->Students();
    cout << students->Count() << " students(s) are registered in the system." << endl;
    students->ForEach([sys](Student *s) -> void {
        cout << "---------------------------------------------------" << endl;
        List<Borrow *> *borrowings = sys->GetBorrowings(s);
        cout << getStudentDetails(s, borrowings);
    });
}