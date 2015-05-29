#include <iostream>
#include "LMS.h"
#include "Menu.h"
#include "Action.h"
#include "Navigation.h"
#include "IO.h"
#include <iostream>

using namespace std;

int main()
{
    LMS* sys = new LMS();
    IO* io = new IO();
    Navigation *nav = new Navigation(sys, io);
    
    Action* aCreateBook = new Action("Register a new book", [](LMS* sys, IO* io) -> void{
        double iban = 0;
        string title;
        string author;
        string publisher;
        int year = 0;
        int quantity;
        
        io->readISBN([&iban](double v) -> void{
            iban = v;
        });
        io->read("title", [&title](string v) -> void{
            title = v;
        });
        io->read("author", [&author](string v) -> void{
            author = v;
        });
        io->read("publisher", [&publisher](string v) -> void{
            publisher = v;
        });
        io->readInt("year (-5000 - 3000)", [&year](int v) -> void{
            year = v;
        }, -5000, 3000);
        io->readInt("quantity (max: 10000)", [&quantity](int v) -> void{
            quantity = v;
        }, 1, 10000);
        
        sys->AddBook(iban, title, author, publisher, year, quantity);
        cout << "Book successfully registered." << endl;
    });
    
    Action* aRemoveBook = new Action("Delete a book", [](LMS* sys, IO* io) -> void {
        Book* book;
        io->readBook(sys, [&book](Book* b) -> void {
            book = b;
        });
        
        sys->DeleteBook(book);
        cout << "Book was deleted successfully." << endl;
    });
    
    Action* aCreateStudent = new Action("Register a new student", [](LMS* sys, IO* io) -> void{
        int stundetId;
        string name;
        string dept;
        string email;
        
        io->readStudentID([&stundetId](int v) -> void{
            stundetId = v;
        });
        io->read("name", [&name](string v) -> void{
            name = v;
        });
        io->read("department", [&dept](string v) -> void{
            dept = v;
        });
        io->read("e-mail", [&email](string v) -> void{
            email = v;
        });
        
        sys->AddStudent(stundetId, name, dept, email);
        cout << "Stundent successfully registered" << endl;
    });
    
    Action* aRemoveStudent = new Action("Delete a student", [](LMS* sys, IO* io) -> void {
        Student* student;
        io->readStudent(sys, [&student](Student* s) -> void {
            student = s;
        });
        
        sys->DeleteStudent(student);
        cout << "Stundent was deleted successfully." << endl;
    });
    
    Action* aBorrowBook = new Action("Borrow a book", [](LMS* sys, IO* io) -> void{
        Book* book;
        Student* student;
        
        io->readBook(sys, [&book](Book* b) -> void{
            book = b;
        });
        
        io->readStudent(sys, [&student](Student* s) -> void{
            student = s;
        });
        
        Borrow* borrow = sys->BorrowBook(book, student);
        cout << "Book borrowed successfully. Quantity left: " << borrow->GetBook()->GetQuantity() << endl;
            
    });
    
    Action* aReturnBook = new Action("Return a book", [](LMS* sys, IO* io) -> void{
        Book* book;
        io->readBook(sys, [&book](Book* b) -> void{
            book = b;
        });
        
        Borrow* borrow = sys->ReturnBook(book);
        cout << "Book borrowed successfully. Quantity left: " << borrow->GetBook()->GetQuantity() << endl;
        
    });
    
    Action* aBookInfo = new Action("Get book info", [](LMS* sys, IO* io) -> void {
        Book* book;
        io->readBook(sys, [&book](Book* b) -> void {
            book = b;
        });
        cout << endl << "Book info:" << endl;
        cout << "ISBN:\t\t" << book->GetISBN() << endl;
        cout << "title:\t\t" << book->GetTitle() << endl;
        cout << "athor:\t\t" << book->GetAuthors() << endl;
        cout << "publisher:\t" << book->GetPublisher() << endl;
        cout << "year:\t\t" << book->GetYear() << endl;
        cout << "quantity:\t" << book->GetQuantity() << endl;
    });
    
    Action* aStudentInfo = new Action("Get student info", [](LMS* sys, IO* io) -> void {
        Student* student;
        io->readStudent(sys, [&student](Student* s) -> void {
            student = s;
        });
        cout << endl << "Student info:" << endl;
        cout << "student ID:\t" << student->GetStudentId() << endl;
        cout << "name:\t\t" << student->GetName() << endl;
        cout << "department:\t" << student->GetDepartment() << endl;
        cout << "e-mail:\t\t" << student->GetEmail() << endl;
    });
    
    
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
    
    cout << "Welcome to LMS (Library Management System)!" << endl;
    cout << "Enter the number of an action or menu to navigate through the programme." << endl;
    cout << "You can enter a single 'q' at any moment to quit an action or move a menu up." << endl;
    cout << "Have Fun!" << endl << endl;

    
    sys->AddBook(1, "my book", "Remo", "Zumsteg", 2012, 1);
    sys->AddBook(2693755987143, "your book", "Zumsteg", "Remo", 2012, 2);
    sys->AddBook(3, "your book", "Zumsteg", "Remo", 2012, 2);
    sys->AddStudent(1, "Remo", "R and D", "remo@zumsteg.com");
    sys->AddStudent(2, "Zumsteg", "R and D 2", "zumsteg@remo.com");
    sys->AddStudent(3, "Zumsteg", "R and D 2", "zumsteg@remo.com");
    
    
    
    nav->Render(mRoot);

    return 0;
}
