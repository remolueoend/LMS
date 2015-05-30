#include <iostream>
#include "../headers/LMS.h"
#include "../headers/Menu.h"
#include "../headers/Action.h"
#include "../headers/Navigation.h"
#include "../headers/IO.h"

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

int main()
{
    // Global instances used in the application:
    LMS* lmsInstance = new LMS();
    IO* ioInstance = new IO();
    Navigation *nav = new Navigation(lmsInstance, ioInstance);

    // Implement all necessary actions:
    Action* aCreateBook = new Action("Register a new book", [](LMS* sys, IO* io) -> void{
        double iban = io->readISBN();
        string title = io->read("title");
        string author = io->read("author");
        string publisher = io->read("publisher");
        int year = io->readInt("year (-5000 - 3000)", -5000, 3000);
        int quantity = io->readInt("quantity (max: 10000)", 1, 10000);
        
        sys->AddBook(iban, title, author, publisher, year, quantity);
        cout << "Book successfully registered." << endl;
    });
    
    Action* aRemoveBook = new Action("Delete a book", [](LMS* sys, IO* io) -> void {
        Book* book = io->readBook(sys);
        sys->DeleteBook(book);
        cout << "Book was deleted successfully." << endl;
    });
    
    Action* aCreateStudent = new Action("Register a new student", [](LMS* sys, IO* io) -> void{
        int studentId = io->readStudentID();
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
        cout << "Book borrowed successfully. Quantity left: " << borrow->GetBook()->GetQuantity() << endl;
            
    });
    
    Action* aReturnBook = new Action("Return a book", [](LMS* sys, IO* io) -> void{
        Book* book = io->readBook(sys);
        Borrow* borrow = sys->ReturnBook(book);
        cout << "Book returned successfully. Quantity left: " << borrow->GetBook()->GetQuantity() << endl;
        
    });
    
    Action* aBookInfo = new Action("Get book info", [](LMS* sys, IO* io) -> void {
        Book* book = io->readBook(sys);
        cout << endl << "Book info:" << endl;
        cout << "ISBN:\t\t" << book->GetISBN() << endl;
        cout << "title:\t\t" << book->GetTitle() << endl;
        cout << "author:\t\t" << book->GetAuthors() << endl;
        cout << "publisher:\t" << book->GetPublisher() << endl;
        cout << "year:\t\t" << book->GetYear() << endl;
        cout << "quantity:\t" << book->GetQuantity() << endl;
    });
    
    Action* aStudentInfo = new Action("Get student info", [](LMS* sys, IO* io) -> void {
        Student* student = io->readStudent(sys);
        cout << endl << "Student info:" << endl;
        cout << "student ID:\t" << student->GetStudentId() << endl;
        cout << "name:\t\t" << student->GetName() << endl;
        cout << "department:\t" << student->GetDepartment() << endl;
        cout << "e-mail:\t\t" << student->GetEmail() << endl;
    });
    

    // Build the menu structure:
    Menu* mQuery = new Menu("Query the library");
    mQuery->AddSubItem(aBookInfo);
    mQuery->AddSubItem(aStudentInfo);
    
    Menu* mManageData = new Menu("Manage data");
    mManageData->AddSubItem(aCreateBook);
    mManageData->AddSubItem(aCreateStudent);
    mManageData->AddSubItem(aRemoveBook);
    mManageData->AddSubItem(aRemoveStudent);

    Menu* mRoot = new Menu("Main Menu");
    mRoot->AddSubItem(aBorrowBook);
    mRoot->AddSubItem(aReturnBook);
    mRoot->AddSubItem(mManageData);
    mRoot->AddSubItem(mQuery);

    // Show the start screen:
    cout << "Welcome to LMS (Library Management System)!" << endl;
    cout << "Enter the number of an action or menu to navigate through the programme." << endl;
    cout << "You can enter a single 'q' at any moment to quit an action or move a menu up." << endl;
    cout << "Have Fun!" << endl << endl;


    // Add some sample data:
    lmsInstance->AddBook(1, "my book", "Remo", "Zumsteg", 2012, 1);
    lmsInstance->AddBook(2693755987143, "your book", "Zumsteg", "Remo", 2012, 2);
    lmsInstance->AddBook(3, "your book", "Zumsteg", "Remo", 2012, 2);
    lmsInstance->AddStudent(1, "Remo", "R and D", "remo@zumsteg.com");
    lmsInstance->AddStudent(2, "Zumsteg", "R and D 2", "zumsteg@remo.com");
    lmsInstance->AddStudent(3, "Zumsteg", "R and D 2", "zumsteg@remo.com");
    
    // Render the main menu:
    nav->Render(mRoot);

    cout << "再见！";
    return 0;
}
