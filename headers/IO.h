#ifndef LMS_IO_h
#define LMS_IO_h

#include <functional>
#include <string>
#include "Book.h"
#include "LMS.h"

class IO{
    
public:
    string read(std::string text);
    string read(std::string text, bool hasDefault, string defaultValue);
    int readInt(std::string text);
    int readInt(std::string text, bool hasDefault, int defaultValue);
    int readInt(std::string text, int min, int max);
    int readInt(std::string text, int min, int max, bool hasDefault, int defaultValue);
    double readDouble(std::string text);
    double readDouble(std::string text, bool hasDefault, double defaultValue);
    double readDouble(std::string text, double min, double max);
    double readDouble(std::string text, double min, double max, bool hasDefault, double defaultValue);
    double readISBN();
    double readISBN(bool hasDefault, double defaultValue);
    int readStudentID();
    int readStudentID(bool hasDefault, int defaultValue);
    
    Book* readBook(LMS* sys);
    List<Book*>* readBooks(LMS* sys);
    List<Book*>* readBooks(LMS* sys, bool requireOne);
    Student* readStudent(LMS* sys);
    List<Student*>* readStudents(LMS* sys);
    List<Student*>* readStudents(LMS* sys, bool requireOne);
};


#endif
