
#include "../headers/EscapeException.h"
#include <stdio.h>
#include "../headers/IO.h"
#include <string>
#include <iostream>
#include <functional>
#include <limits>
#include "../headers/Book.h"
#include "../headers/LMS.h"
#include <stdlib.h>
#include <sstream>

using namespace std;

string _itostr(int val){
    stringstream ss;
    ss << val;
    return ss.str();
}
string _dtostr(double val){
    stringstream ss;
    ss << val;
    return ss.str();
}

inline bool isInteger(const std::string & s)
{
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;
    char * p ;
    strtol(s.c_str(), &p, 10);
    return (*p == 0) ;
}
inline bool isDouble(const std::string & s)
{
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

    char * p ;
    strtod(s.c_str(), &p);

    return (*p == 0) ;
}

string IO::read(string text) {
    return read(text, false, "");
}
string IO::read(string text, bool hasDefault, string defaultValue){
    string res;
    cout << text << (hasDefault ? " (" + defaultValue + ")" : "") << ": ";
    std::getline(std::cin, res);

    if(res.length() == 0 && hasDefault){
        return defaultValue;
    }
    
    if(res != "q"){
        return res;
    }else{
        throw EscapeException();
    }
}

int IO::readInt(string text) {
    return readInt(text, false, 0);
}
int IO::readInt(string text, bool hasDefault, int defaultValue){
    return readInt(text, -numeric_limits<int>::max(), numeric_limits<int>::max(), hasDefault, defaultValue);
}

int IO::readInt(string text, int min, int max){
    return readInt(text, min, max, false, 0);
}
int IO::readInt(string text, int min, int max, bool hasDefault, int defaultValue){
    int res = 0;

    string input = read(text, hasDefault, _itostr(defaultValue));
    if(input.length() == 0 && hasDefault){
        return defaultValue;
    }

    if(isInteger(input)){
        res = strtol(input.c_str(), NULL, 10);
        if(res >= min && res <= max){
            return res;
        }
    }
    cout << "Invalid entry. ";
    return readInt(text, min, max, hasDefault, defaultValue);
}

double IO::readDouble(string text){
    return readDouble(text, false, 0);
}
double IO::readDouble(string text, bool hasDefault, double defaultValue){
    return readDouble(text, -numeric_limits<double>::max(), numeric_limits<double>::max(), hasDefault, defaultValue);
}

double IO::readDouble(string text, double min, double max){
    return readDouble(text, min, max, false, 0);
}
double IO::readDouble(string text, double min, double max, bool hasDefault, double defaultValue){
    double res = 0;
    string input = read(text, hasDefault, _dtostr(defaultValue));

    if(input.length() == 0 && hasDefault){
        return defaultValue;
    }

    if(isDouble(input)){
        res = strtod(input.c_str(), NULL);
        if(res >= min && res <= max){
            return res;
        }
    }
    cout << "Invalid entry. ";
    return readDouble(text, min, max);
}

string IO::readISBN(){
    return readISBN(false, "");
}
string IO::readISBN(bool hasDefault, string defaultValue){
    string result = "";
    while(result.length() == 0){
        string inp = read("ISBN", hasDefault, defaultValue);
        if(inp.length() < 10 || inp.length() > 13){
            cout << "Invalid ISBN. Must have 10 to 13 digits." << endl;
        }else{
            result = inp;
        }
    }
    return result;
}

string IO::readStudentID(){
    return readStudentID(false, "");
}
string IO::readStudentID(bool hasDefault, string defaultValue){
    string result = "";
    while(result.length() == 0){
        string inp = read("student ID", hasDefault, defaultValue);
        if(inp.length() != 7){
            cout << "Invalid student ID. Must be between 0100000 and 0999999." << endl;
        }else{
            result = inp;
        }
    }
    return result;
}

Book* IO::readBook(LMS* sys){

    List<Book*>* books = readBooks(sys, true);
    if(books->Count() == 1){
        return books->First();
    }else{
        cout << "Multiple books found. Choose one:" << endl;
        books->ForEach([](Book* b, int i) -> void {
            cout << i + 1 << ": " << b->GetISBN() << ": " << b->GetTitle() << " (" << b->GetAuthors() << ")" << endl;
        });
        try{
            int choice = readInt("choose", 1, books->Count());
            return books->At(choice - 1);
        }catch(EscapeException& ex){
            cout << ex.what() << endl << endl;
            return readBook(sys);
        }
    }
}

List<Book *> *IO::readBooks(LMS *sys) {
    return readBooks(sys, false);
}

List<Book *> *IO::readBooks(LMS *sys, bool requireOne) {
    cout << "Search for book(s) by:" << endl;
    cout << "1: ISBN" << endl;
    cout << "2: title" << endl;
    cout << "3: author" << endl;
    cout << "4: publisher" << endl;
    cout << "5: year" << endl;

    std::function<bool (Book* s)> filter;
    int choice = readInt("choose", 1, 5);
    try{
        if(choice == 1){
            string ISBN = readISBN();
            filter = [ISBN](Book* b) -> bool { return b->GetISBN() == ISBN; };
        }else if(choice == 2){
            string title = read("book title");
            filter = [title](Book* b) -> bool { return b->GetTitle() == title; };
        }else if(choice == 3){
            string author = read("author");
            filter = [author](Book* b) -> bool { return b->GetAuthors() == author; };
        }else if(choice == 4){
            string publ = read("publisher");
            filter = [publ](Book* b) -> bool { return b->GetPublisher() == publ; };
        }else if(choice == 5){
            int year = readInt("year", -5000, 3000);
            filter = [year](Book* b) -> bool { return b->GetYear() == year; };
        }else{
            throw runtime_error("Invalid choice.");
        }
        List<Book*>* result = sys->Books(filter);
        if(requireOne && result->Count() == 0){
            cout << "Could not find any entries. Try again." << endl;
            return readBooks(sys, requireOne);
        }
        return result;
    }catch(EscapeException& ex){
        cout << ex.what() << endl << endl;
        return readBooks(sys);
    }
}

Student* IO::readStudent(LMS* sys){
    List<Student*>* students = readStudents(sys, true);
    if(students->Count() == 1){
        return students->First();
    }else{
        cout << "Multiple students found. Choose one:" << endl;
        students->ForEach([](Student* s, int i) -> void {
            cout << i + 1 << ": " << s->GetStudentId() << ": " << s->GetName() << " (" << s->GetDepartment() << ")" << endl;
        });
        try{
            int choice = readInt("choose", 1, students->Count());
            return students->At(choice - 1);
        }catch(EscapeException& ex){
            cout << ex.what() << endl << endl;
            return readStudent(sys);
        }
    }
}

List<Student *> *IO::readStudents(LMS *sys) {
    return readStudents(sys, false);
}
List<Student *> *IO::readStudents(LMS *sys, bool requireOne) {
    cout << "Search for student(s) by:" << endl;
    cout << "1: student ID" << endl;
    cout << "2: student name" << endl;
    cout << "3: e-mail" << endl;
    cout << "4: department" << endl;

    std::function<bool(Student *s)> filter;
    int choice = readInt("choose", 1, 4);
    try {
        if (choice == 1) {
            string stuId = readStudentID();
            filter = [stuId](Student *s) -> bool { return s->GetStudentId() == stuId; };
        } else if (choice == 2) {
            string name = read("student name");
            filter = [name](Student *s) -> bool { return s->GetName() == name; };
        } else if (choice == 3) {
            string email = read("e-mail");
            filter = [email](Student *s) -> bool { return s->GetEmail() == email; };
        } else if (choice == 4) {
            string dept = read("department");
            filter = [dept](Student *s) -> bool { return s->GetDepartment() == dept; };
        } else {
            throw runtime_error("Invalid choice.");
        }
        List<Student *> *result = sys->Students(filter);
        if (requireOne && result->Count() == 0) {
            cout << "Could not find any entries. Try again." << endl;
            return readStudents(sys, requireOne);
        }
        return result;
    } catch (EscapeException &ex) {
        cout << ex.what() << endl << endl;
        return readStudents(sys);
    }
}
