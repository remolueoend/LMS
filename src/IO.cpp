
#include "../headers/EscapeException.h"
#include <stdio.h>
#include "../headers/IO.h"
#include <string>
#include <iostream>
#include <functional>
#include <limits>
#include "../headers/Book.h"
#include "../headers/LMS.h"

using namespace std;

string IO::read(string text){
    string res;
    cout << text << ": ";
    std::getline(std::cin, res);
    
    if(res != "q"){
        return res;
    }else{
        throw EscapeException();
    }
}

int IO::readInt(string text){
    return readInt(text, numeric_limits<int>::min(), numeric_limits<int>::max());
}

int IO::readInt(string text, int min, int max){
    int res = 0;
    string input = read(text);
    
    try{
        res = stoi(input);
        if(res < min || res > max){
            throw exception();
        }
        return res;
        
    }catch(exception ex){
        cout << "Invalid entry. ";
        return readInt(text, min, max);
    }
}

double IO::readDouble(string text){
    return readDouble(text, numeric_limits<double>::min(), numeric_limits<double>::max());
}

double IO::readDouble(string text, double min, double max){
    double res = 0;
    string input = read(text);
    
    try{
        res = stod(input);
        if(res < min || res > max){
            throw exception();
        }
        return res;
        
    }catch(exception ex){
        cout << "Invalid entry. ";
        return readDouble(text, min, max);
    }
}

double IO::readISBN(){
    //todo: Set minimum to 1000000000
    return readDouble("ISBN", 1, 9999999999999);
}

int IO::readStudentID(){
    //todo: Set minimum to 100000
    return readInt("student ID", 1, 999999);
}

Book* IO::readBook(LMS* sys){
    cout << "Look for:" << endl;
    cout << "1: ISBN" << endl;
    cout << "2: book title" << endl;

    int choice = readInt("choose", 1, 2);
    
    if(choice == 1){
        try{
            double ISBN = readISBN();
            return sys->BookByISBN(ISBN);
        }catch(exception& ex){
            cout << ex.what() << endl << endl;
            return readBook(sys);
        }
    }else{
        try{
            string title = read("book title");
            return sys->BookByTitle(title);
        }catch(exception& ex){
            cout << ex.what() << endl << endl;
            return readBook(sys);
        }
    }
}

Student* IO::readStudent(LMS* sys){
    cout << "Look for:" << endl;
    cout << "1: student ID" << endl;
    cout << "2: student name" << endl;

    int choice = readInt("choose", 1, 2);

    if(choice == 1){
        try{
            double stuId = readStudentID();
            return sys->StudentByID(stuId);
        }catch(exception& ex){
            cout << ex.what() << endl << endl;
            return readStudent(sys);
        }
    }else{
        try{
            string name = read("student name");
            return sys->StudentByName(name);
        }catch(exception& ex){
            cout << ex.what() << endl << endl;
            return readStudent(sys);
        }
    }
}
