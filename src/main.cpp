#include <iostream>
#include "../headers/LMS.h"
#include "../headers/Menu.h"
#include "../headers/Action.h"
#include "../headers/Navigation.h"
#include "../headers/IO.h"
#include "../headers/GroupableList.h"
#include <ctime>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

/*
 This Library management system (LMS) consists of following components:

 * Data Model classes:
   -------------------------
   This classes are wrapping the actual data:
   - Book Class containing information of a book
   - Student Class containing information about a student
   - Borrow Class containg informatin about a borrowed book (which book, which students, what date/time)

 * The LMS Class
   -------------------------
   This class provides all necessary interfaces and methods to manage the library (add/remove/query, etc)

 * The IO Class
   -------------------------
   Provides methods to interact with the user/read inputs from the console.

 * The Action Class
   -------------------------
   Represents an excutable action. Has a title and a lambda based handler which gets executed
   when the user selects the action from a menu.

 * The Menu Class
   -------------------------
   Represents a menu or a submenu, containing submenu and actions.

 * The Navigation Class
   -------------------------
   Manages the navigation through the menus and submenus and actions.

*/

// Helper functions
string _getBookDetails(Book *book, List<Borrow *> *borrowings){
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

string _getStundetDetails(Student* student, List<Borrow*>* borrowings){
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

int main()
{
    // Global instances used in the application:
    LMS* lmsInstance = new LMS();
    IO* ioInstance = new IO();
    Navigation *nav = new Navigation(lmsInstance, ioInstance);

    // Implement all necessary actions:
    Action* aCreateBook = new Action("Register a new book", [](LMS* sys, IO* io) -> void{
        string isbn = io->readISBN();
        string title = io->read("title");
        string author = io->read("author");
        string publisher = io->read("publisher");
        int year = io->readInt("year (-5000 - 3000)", -5000, 3000);
        int quantity = io->readInt("quantity (max: 10000)", 1, 10000);
        
        sys->AddBook(isbn, title, author, publisher, year, quantity);
        cout << "Book successfully registered." << endl;
    });
    
    Action* aRemoveBook = new Action("Delete a book", [](LMS* sys, IO* io) -> void {
        Book* book = io->readBook(sys);
        sys->DeleteBook(book);
        cout << "Book was deleted successfully." << endl;
    });
    
    Action* aCreateStudent = new Action("Register a new student", [](LMS* sys, IO* io) -> void{
        string studentId = io->readStudentID();
        string name = io->read("name");
        string dept = io->read("department");
        string email = io->read("e-mail");
        
        sys->AddStudent(studentId, name, dept, email);
        cout << "Stundent successfully registered" << endl;
    });
    
    Action* aRemoveStudent = new Action("Delete a student", [](LMS* sys, IO* io) -> void {
        Student* student = io->readStudent(sys);
        sys->DeleteStudent(student);
        cout << "Stundent was deleted successfully." << endl;
    });
    
    Action* aBorrowBook = new Action("Borrow a book", [](LMS* sys, IO* io) -> void{
        Book* book = io->readBook(sys);
        Student* student = io->readStudent(sys);
        Borrow* borrow = sys->BorrowBook(book, student);
        cout << "Book borrowed successfully. Quantity left: " << sys->QuantitiesLeft(book) << endl;
            
    });
    
    Action* aReturnBook = new Action("Return a book", [](LMS* sys, IO* io) -> void{
        Book* book = io->readBook(sys);
        Student* student = io->readStudent(sys);
        Borrow* borrow = sys->ReturnBook(book, student);
        cout << "Book returned successfully. Quantity left: " << sys->QuantitiesLeft(book) << endl;
    });
    
    Action* aBookInfo = new Action("Get book info", [](LMS* sys, IO* io) -> void {
        List<Book*>* books = io->readBooks(sys, true);
        cout << endl << "Found " << books->Count() << " book(s):" << endl;
        books->ForEach([sys](Book* b) -> void {
            cout << "---------------------------------------------------" << endl;
            List<Borrow*>* borrowings = sys->GetBorrowings(b);
            cout << _getBookDetails(b, borrowings);
        });
    });

    Action* aBorrowedBooks = new Action("Show borrowed books", [](LMS* sys, IO* io) -> void {
        GroupableList<Book*, Borrow*>* list = new GroupableList<Book*, Borrow*>(sys->GetBorrowings());
        Dictionary<Book*, List<Borrow*>*> dict = list->GroupBy([](Borrow* b) -> Book* { return b->GetBook(); });
        if(dict.Count() > 0){
            dict.ForEach([](KeyValuePair<Book*, List<Borrow*>*>* pair) -> void {
                cout << "---------------------------------------------------" << endl;
                cout << _getBookDetails(pair->Key(), pair->Value());
            });
        }else{
            cout << "Currenty no books are borrowed." << endl;
        }
    });

    Action* aOverdueBooks = new Action("Show overdue books", [](LMS* sys, IO* io) -> void {
        GroupableList<Book*, Borrow*>* list = new GroupableList<Book*, Borrow*>(sys->GetBorrowings(true));
        Dictionary<Book*, List<Borrow*>*> dict = list->GroupBy([](Borrow* b) -> Book* { return b->GetBook(); });
        if(dict.Count() > 0){
            dict.ForEach([](KeyValuePair<Book*, List<Borrow*>*>* pair) -> void {
                cout << "---------------------------------------------------" << endl;
                cout << _getBookDetails(pair->Key(), pair->Value());
            });
        }else{
            cout << "Currenty no books are overdue." << endl;
        }
    });
    
    Action* aStudentInfo = new Action("Get student info", [](LMS* sys, IO* io) -> void {
        List<Student*>* students = io->readStudents(sys, true);
        cout << endl << "Found " << students->Count() << " student(s):" << endl;
        students->ForEach([sys](Student* s) -> void {
            cout << "---------------------------------------------------" << endl;
            List<Borrow*>* borrowings = sys->GetBorrowings(s);
            cout << _getStundetDetails(s, borrowings);
        });
    });

    Action* aUpdateBook = new Action("Update book", [](LMS* sys, IO* io) -> void {
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
    });

    Action* aUpdateStudent = new Action("Update student", [](LMS* sys, IO* io) -> void {
        Student* student = io->readStudent(sys);
        Student* ns = new Student();

        cout << "Enter the new data. To keep a current value, just press enter:" << endl;

        ns->SetStudentId(io->readStudentID(true, student->GetStudentId()));
        ns->SetName(io->read("student name", true, student->GetName()));
        ns->SetEmail(io->read("e-mail", true, student->GetEmail()));
        ns->SetDepartment(io->read("department", true, student->GetDepartment()));

        student->Update(ns);
        cout << "Student updated successfully." << endl;
    });

    Action* aShowRecords = new Action("show book records", [](LMS* sys, IO* io) -> void {
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
    });

    Action* aExportBooks = new Action("Export books", [](LMS* sys, IO* io) -> void {
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
            myfile << _getBookDetails(b, borrowings);
        });

        myfile.close();
        cout << "Export done." << endl;
    });

    Action* aExportStudents = new Action("Export students", [](LMS* sys, IO* io) -> void {
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
            myfile << _getStundetDetails(s, borrowings);
        });

        myfile.close();
        cout << "Export done." << endl;
    });
    

    // Build the menu structure:
    Menu* mQuery = new Menu("Query the library");
    mQuery->AddSubItem(aBookInfo);
    mQuery->AddSubItem(aStudentInfo);
    mQuery->AddSubItem(aBorrowedBooks);
    mQuery->AddSubItem(aOverdueBooks);
    mQuery->AddSubItem(aShowRecords);
    
    Menu* mManageData = new Menu("Manage data");
    mManageData->AddSubItem(aCreateBook);
    mManageData->AddSubItem(aUpdateBook);
    mManageData->AddSubItem(aRemoveBook);
    mManageData->AddSubItem(aCreateStudent);
    mManageData->AddSubItem(aUpdateStudent);
    mManageData->AddSubItem(aRemoveStudent);

    Menu* mExport = new Menu("Export data");
    mExport->AddSubItem(aExportBooks);
    mExport->AddSubItem(aExportStudents);

    Menu* mRoot = new Menu("Main Menu");
    mRoot->AddSubItem(aBorrowBook);
    mRoot->AddSubItem(aReturnBook);
    mRoot->AddSubItem(mManageData);
    mRoot->AddSubItem(mQuery);
    mRoot->AddSubItem(mExport);

    // Show the start screen:
    cout << "Welcome to LMS (Library Management System)!" << endl;
    cout << "Enter the number of an action or menu to navigate through the programme." << endl;
    cout << "You can enter a single 'q' at any moment to quit an action or move a menu up." << endl;
    cout << "Have Fun!" << endl << endl;


    // Add some sample data:
    lmsInstance->AddBook("1234567890", "my book", "Remo", "Zumsteg", 2012, 3);
    lmsInstance->AddBook("1234567891", "your book", "Zumsteg", "Remo", 2012, 5);
    lmsInstance->AddBook("1234567892", "your book", "Zumsteg", "Remo", 2012, 5);
    lmsInstance->AddStudent("0123456", "Remo", "R and D", "remo@zumsteg.com");
    lmsInstance->AddStudent("0123457", "Zumsteg", "R and D 2", "zumsteg@remo.com");
    lmsInstance->AddStudent("0123458", "Zumsteg", "R and D 2", "zumsteg@remo.com");
    
    // Render the main menu:
    nav->Render(mRoot);

    cout << "再见！" << endl;
    return 0;
}
