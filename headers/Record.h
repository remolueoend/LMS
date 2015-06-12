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

    string ISBN(){
        return pISBN;
    }

    string BookTitle(){
        return pTitle;
    }

    string StudentID(){
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
    string pISBN;
    string pTitle;
    string pStudentID;
    string pStudentName;
    RecordType pType;
    time_t pTimestamp;
};


#endif //LMS_RECORD_H
