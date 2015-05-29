
#include "EscapeException.h"
#include <stdio.h>
#include "IO.h"
#include <string>
#include <iostream>
#include <functional>
#include <limits>
#include "Book.h"
#include "LMS.h"

using namespace std;

void IO::read(string text, std::function<void (string input)> callback){
    string res;
    cout << text << ": ";
    std::getline(std::cin, res);
    
    if(res != "q"){
        callback(res);
    }else{
        throw EscapeException();
    }
}

void IO::readInt(string text, std::function<void (int input)> callback){
    readInt(text, callback, numeric_limits<int>::min(), numeric_limits<int>::max());
}

void IO::readInt(string text, std::function<void (int input)> callback, int min, int max){
    string input;
    int res = 0;
    
    read(text, [&input](string str) -> void {
        input = str;
    });
    
    try{
        res = stoi(input);
        if(res < min || res > max){
            throw exception();
        }
        callback(res);
        
    }catch(exception ex){
        cout << "Invalid entry. ";
        readInt(text, callback, min, max);
    }
}

void IO::readDouble(string text, std::function<void (double input)> callback){
    readDouble(text, callback, numeric_limits<double>::min(), numeric_limits<double>::max());
}

void IO::readDouble(string text, std::function<void (double input)> callback, double min, double max){
    string input;
    double res = 0;
    
    read(text, [&input](string str) -> void {
        input = str;
    });
    
    try{
        res = stod(input);
        if(res < min || res > max){
            throw exception();
        }
        callback(res);
        
    }catch(exception ex){
        cout << "Invalid entry. ";
        readDouble(text, callback, min, max);
    }
}

void IO::readISBN(std::function<void (double input)> callback){
    //todo: Set minimum to 1000000000
    readDouble("ISBN", callback, 1, 9999999999999);
}

void IO::readStudentID(std::function<void (int input)> callback){\
    //todo: Set minimum to 100000
    readInt("student ID", callback, 1, 999999);
}

void IO::readBook(LMS* sys, std::function<void (Book* book)> callback){
    cout << "Look for:" << endl;
    cout << "1: ISBN" << endl;
    cout << "2: book title" << endl;
    
    int choice;
    readInt("choose", [&choice](int c) -> void { choice = c; }, 1, 2);
    
    if(choice == 1){
        double ISBN;
        try{
            readISBN([&ISBN](double v) -> void{
                ISBN = v;
            });
        }catch(EscapeException& ex){
            cout << "Canceled." << endl << endl;
            readBook(sys, callback);
            return;
        }
        try{
            callback(sys->BookByISBN(ISBN));
        }catch(exception& ex){
            cout << ex.what() << endl << endl;
            readBook(sys, callback);
        }
        
    }else{
        string title;
        try{
            read("book title", [&title](string v) -> void{
                title = v;
            });
        }catch(EscapeException& ex){
            cout << "Canceled." << endl << endl;
            readBook(sys, callback);
            return;
        }
        try{
            callback(sys->BookByTitle(title));
        }catch(exception& ex){
            cout << ex.what() << endl << endl;
            readBook(sys, callback);
        }

    }
}

void IO::readStudent(LMS* sys, std::function<void (Student* student)> callback){
    cout << "Look for:" << endl;
    cout << "1: student ID" << endl;
    cout << "2: student name" << endl;
    
    int choice;
    readInt("choose", [&choice](int c) -> void { choice = c; }, 1, 2);
    
    if(choice == 1){
        double stuId;
        try{
            readStudentID([&stuId](int v) -> void{
                stuId = v;
            });
        }catch(EscapeException& ex){
            cout << "Canceled." << endl << endl;
            readStudent(sys, callback);
            return;
        }
        try{
            callback(sys->StudentByID(stuId));
        }catch(exception& ex){
            cout << ex.what() << endl << endl;
            readStudent(sys, callback);
        }
        
    }else{
        string name;
        try{
            read("name", [&name](string v) -> void{
                name = v;
            });
        }catch(EscapeException& ex){
            cout << "Canceled." << endl << endl;
            readStudent(sys, callback);
            return;
        }
        try{
            callback(sys->StudentByName(name));
        }catch(exception& ex){
            cout << ex.what() << endl << endl;
            readStudent(sys, callback);
        }
    }
}
