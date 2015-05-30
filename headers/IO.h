#ifndef LMS_IO_h
#define LMS_IO_h

#include <functional>
#include <string>
#include "Book.h"
#include "LMS.h"

class IO{
    
public:
    string read(std::string text);
    int readInt(std::string text);
    int readInt(std::string text, int min, int max);
    double readDouble(std::string text);
    double readDouble(std::string text, double min, double max);
    double readISBN();
    int readStudentID();
    
    Book* readBook(LMS* sys);
    Student* readStudent(LMS* sys);
};


#endif
