#ifndef LMS_IO_h
#define LMS_IO_h

#include <functional>
#include <string>
#include "Book.h"
#include "LMS.h"

class IO{
    
public:
    void read(std::string text, std::function<void (std::string input)> callback);
    void readInt(std::string text, std::function<void (int input)> callback);
    void readInt(std::string text, std::function<void (int input)> callback, int min, int max);
    void readDouble(std::string text, std::function<void (double input)> callback);
    void readDouble(std::string text, std::function<void (double input)> callback, double min, double max);
    void readISBN(std::function<void (double input)> callback);
    void readStudentID(std::function<void (int input)> callback);
    
    void readBook(LMS* sys, std::function<void (Book* book)> callback);
    void readStudent(LMS* sys, std::function<void (Student* student)> callback);
};


#endif
