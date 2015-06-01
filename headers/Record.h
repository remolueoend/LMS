//
// Created by Remo Zumsteg on 01/06/15.
//

#ifndef LMS_RECORD_H
#define LMS_RECORD_H

#include "Book.h"
#include "Student.h"
#include <ctime>
#include <string>

enum RecordType{
    BORROW, RETURN
};

class Record {
public:
    Record(RecordType type, Book* book, Student* student);

    double ISBN(){
        return pISBN;
    }

    string BookTitle(){
        return pTitle;
    }

    int StudentID(){
        return pStudentID;
    }

    string StudentName(){
        return pStudentName;
    }

    RecordType GetType(){
        return pType;
    }

    string GetDateTimeStr();

    tm* GetDateTime();

private:
    double pISBN;
    string pTitle;
    int pStudentID;
    string pStudentName;
    RecordType pType;
    time_t pTimestamp;
};


#endif //LMS_RECORD_H
