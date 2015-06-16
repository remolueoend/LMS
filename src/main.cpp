#include <iostream>
#include "../headers/LMS.h"
#include "../headers/Menu.h"
#include "../headers/Action.h"
#include <iomanip>
#include "../headers/Actions.h"

using namespace std;

/*
 This Library management system (LMS) consists of following components:

 * Data Model classes:
   -------------------------
   This classes are wrapping the actual data:
   - Book Class containing information of a book
   - Student Class containing information about a student
   - Borrow Class containing information about a borrowed book (which book, which students, what date/time)
   - Record Class wrapping single book records

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

 * The App Class
   -------------------------
   Manages the navigation through the menus and submenus and actions.

 * The Actions Class
   -------------------------
   Provides a list of action which can be accessed over the navigation.

*/

int main()
{
    // Global instances used in the application:
    LMS* lmsInstance = new LMS();
    IO* ioInstance = new IO();
    App *app = new App(lmsInstance, ioInstance);

    // Build the menu structure:
    Menu* mQuery = new Menu("Query the library");
    mQuery->AddAction("Show book info", Actions::BooksInfo);
    mQuery->AddAction("Show student info", Actions::StudentsInfo);
    mQuery->AddAction("Show borrowed books", Actions::BorrowedBooks);
    mQuery->AddAction("Show overdue books", Actions::OverdueBooks);
    mQuery->AddAction("Show book records", Actions::ShowRecords);
    
    Menu* mManageData = new Menu("Manage data");
    mManageData->AddAction("Register a new book", Actions::CreateBook);
    mManageData->AddAction("Update a book", Actions::UpdateBook);
    mManageData->AddAction("Remove a book", Actions::RemoveBook);
    mManageData->AddAction("Register a new student", Actions::CreateStudent);
    mManageData->AddAction("Update a student", Actions::UpdateStudent);
    mManageData->AddAction("Remove a student", Actions::RemoveStudent);

    Menu* mExport = new Menu("Export data");
    mExport->AddAction("Export books", Actions::ExportBooks);
    mExport->AddAction("Export students", Actions::ExportStudents);

    Menu* mRoot = new Menu("Main Menu");
    mRoot->AddAction("Borrow a book", Actions::BorrowBook);
    mRoot->AddAction("Return a book", Actions::ReturnBook);
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
    app->Render(mRoot);

    cout << "再见！" << endl;
    return 0;
}
